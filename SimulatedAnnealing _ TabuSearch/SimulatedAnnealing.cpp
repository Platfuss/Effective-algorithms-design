#include "SimulatedAnnealing.h"



SimulatedAnnealing::SimulatedAnnealing() {
	best_solution = NULL;
	cost_table = NULL;
}


SimulatedAnnealing::~SimulatedAnnealing() {
	if (best_solution != NULL) {
		delete[] best_solution;
		best_solution = NULL;
	}

	if (cost_table != NULL) {
		for (int i = 0; i < size; i++) {
			delete[] cost_table[i];
		}
		delete[] cost_table;
		cost_table = NULL;
	}
}

Results SimulatedAnnealing::StartSimulatedAnnealing(std::string file_name, float alpha, int time_left) {
	int time_to_end = time_left + clock() / CLOCKS_PER_SEC;
	int time_at_begin = clock() / CLOCKS_PER_SEC;
	if (FillCostTable(file_name) && time_left > 0 && (alpha > 0 && alpha < 1)) {
		int* curr_solution = new int[1]; // aktualnie rozwazane rozwiazanie
		int cost_of_curr_solution = 0; // koszt aktualnego rozwiazania
		int* neighbour = new int[size]; // sasiad aktualnego rozwiazania (sasiedztwo typu swap)
		int neighbour_cost; // koszt sasiada

		curr_solution = CreateGreedySolution(curr_solution);
		cost_of_curr_solution = CostOfSolution(curr_solution);

		CopyArrays(curr_solution, best_solution);
		cost_of_best_solution = cost_of_curr_solution;

		float temperature = MeasureTemperature(curr_solution); // temperatura poczatkowa

		std::vector<std::pair<int, int>> time_table;
		std::pair<int, int> cost_and_time;

		while (clock() / CLOCKS_PER_SEC < time_to_end) {
				for (int i = 0; i < size * 100; i++) {
					if (clock() / CLOCKS_PER_SEC > time_to_end)
						break;

					CopyArrays(curr_solution, neighbour);
					SwapCities(neighbour); // znalezienie sasiada
					neighbour_cost = CostOfSolution(neighbour);
					if (neighbour_cost < cost_of_curr_solution) { // jesli koszt sasiada jest lepszy niz koszt aktualnego rozwiazania
						CopyArrays(neighbour, curr_solution);
						cost_of_curr_solution = neighbour_cost;

						if (cost_of_best_solution > neighbour_cost) { // jesli koszt tego sasiada jest lepszy niz najlepszego znanego dotad rozwiazania
							CopyArrays(curr_solution, best_solution);
							cost_of_best_solution = neighbour_cost;
						}
					}
					else // obliczanie prawdopodobienstwa przyjecia gorszego rozwiazania 
					{
						float x = float(rand() % 101) / 100.0f;
						float y = CountProbability(neighbour_cost - cost_of_curr_solution, temperature);
						if (x < y) {
							CopyArrays(neighbour, curr_solution);
							cost_of_curr_solution = neighbour_cost;
						}
					}

					cost_and_time.first = cost_of_best_solution;
					cost_and_time.second = clock() / CLOCKS_PER_SEC - time_at_begin;

					if (time_table.size() == 0)
						time_table.push_back(cost_and_time);
					else {
						if (time_table.back().second / 3 != cost_and_time.second / 3) {
							time_table.push_back(cost_and_time);
						}
					}
				}
			temperature *= alpha;
		}

		Results results(size);
		results.error = false;
		results.temperature = temperature;
		for (int i = 0; i < size; i++) {
			results.best_solution.push_back(best_solution[i]);
		}
		results.time_table = time_table;


		delete[] curr_solution;
		delete[] neighbour;
		return results;
	}
	else {
		Results results;
		results.size = 0;
		results.error = true;
		return results;
	}
}

bool SimulatedAnnealing::FillCostTable(std::string file_name) {
	std::ifstream file;
	file.open(file_name.c_str());
	if (!file.is_open())
		return false;
	else {
		std::string dimension("DIMENSION: ");
		std::string edge_weight_section("EDGE_WEIGHT_SECTION");

		while (!file.eof()) {
			std::string line;
			std::string substring_dim, substring_wieght;

			getline(file, line);

			substring_dim = line.substr(0, dimension.length());
			substring_wieght = line.substr(0, edge_weight_section.length());
			if (dimension.compare(substring_dim) == 0) {
				size = atoi(line.substr(11).c_str());
				continue;
			}
			else if (!edge_weight_section.compare(substring_wieght) == 0)
				continue;

			best_solution = new int[size];
			cost_table = new int*[size];
			for (int i = 0; i < size; i++) {
				cost_table[i] = new int[size];
			}

			for (int i = 0; i < size; i++) {
				for (int j = 0; j < size; j++) {
					file >> cost_table[i][j];
				}
			}

			file.close();
			return true;
		}
		file.close();
		return false;
	}
}

void SimulatedAnnealing::PrintResults() {
	std::cout << std::endl << std::endl << "Wynik to: " << cost_of_best_solution << std::endl;
	for (int i = 0; i < size; i++) {
		if (i % 20 == 0)
			std::cout << std::endl;
		printf("%3d ", best_solution[i]);
	}


	std::cout << std::endl << std::endl;
}

float SimulatedAnnealing::CountProbability(int delta, float temperature) {
	return exp(-1 * delta / temperature);
}

int * SimulatedAnnealing::CreateRandomSolution(int* solution) {
	delete[] solution;
	solution = new int[size];
	for (int i = 0; i < size; i++) {
		solution[i] = i;
	}
	std::random_shuffle(solution, &solution[size]);
	return solution;
}

int * SimulatedAnnealing::CreateGreedySolution(int * solution) {
	delete[] solution;
	solution = new int[size];
	bool* present = new bool[size];
	for (int i = 0; i < size; i++)
		present[i] = false;

	int number = rand() % size;
	int second = 0;

	present[number] = true;
	solution[0] = number;

	for (int i = 1; i < size; i++) {
		int minimum = std::numeric_limits<int>::max();
		int j_saved = 0;
		for (int j = 0; j < size; j++) {
			if (cost_table[number][j] < minimum && present[j] == false) {
				minimum = cost_table[number][j];
				j_saved = j;
			}
		}
		present[j_saved] = true;
		solution[i] = j_saved;
		number = j_saved;
	}


	delete[] present;
	return solution;
}

int SimulatedAnnealing::CostOfSolution(int* solution)
{
	int cost = 0;
	for (int i = 0; i < size - 1; i++) {
		cost += cost_table[solution[i]][solution[i + 1]];
	}
	cost += cost_table[solution[size - 1]][solution[0]];
	return cost;
}

void SimulatedAnnealing::SwapCities(int * neighbour) {

	int from = rand() % size;
	int to = 0;
	do {
		to = rand() % size;
	} while (to == from);

	int buffor = 0;
	buffor = neighbour[from];
	neighbour[from] = neighbour[to];
	neighbour[to] = buffor;

	return;
}

void SimulatedAnnealing::CopyArrays(int * from, int * to){
	for (int i = 0; i < size; i++) {
		to[i] = from[i];
	}
}

float SimulatedAnnealing::MeasureTemperature(int * solution) {
	int* temp_table = new int[size];
	for (int i = 0; i < size; i++)
		temp_table[i] = -1;

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (i != j) {
				if (cost_table[i][j] > temp_table[i]) {
					temp_table[i] = cost_table[i][j];
				}
			}
		}
	}

	float temperature = 0.0;
	for (int i = 0; i < size; i++)
		temperature += static_cast<float>(temp_table[i]);

	return temperature;
}
