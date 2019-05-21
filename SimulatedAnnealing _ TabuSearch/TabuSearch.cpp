#include "TabuSearch.h"



TabuSearch::TabuSearch() {
	size = 0;
	best_solution = NULL;
	cost_table = NULL;
	extra_punishment = NULL;
}


TabuSearch::~TabuSearch()
{
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

	if (extra_punishment != NULL) {
		for (int i = 0; i < size; i++) {
			delete[] extra_punishment[i];
		}
		delete[] extra_punishment;
		extra_punishment = NULL;
	}
}

bool TabuSearch::FillCostTable(std::string file_name){
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
			else if (! edge_weight_section.compare(substring_wieght) == 0)
				continue;
				
			best_solution = new int[size];
			cost_table = new int*[size];
			extra_punishment = new int*[size];
			for (int i = 0; i < size; i++) {
				cost_table[i] = new int[size];
				extra_punishment[i] = new int[size];
			}

			for (int i = 0; i < size; i++) {
				for (int j = 0; j < size; j++) {
					file >> cost_table[i][j];
					extra_punishment[i][j] = 0;
				}
			}

			max = size * 10;
			min = size * 4;
			plus = size * 2;

			file.close();
			return true;
		}
		file.close();
		return false;
	}
}

Results TabuSearch::StartTabuSearch(std::string file_name, int time_left) {
	if (FillCostTable(file_name) && time_left > 0) {
		int* curr_solution = new int[1];
		int cost_of_curr_solution = 0;

		curr_solution = CreateGreedySolution(curr_solution);
		cost_of_curr_solution = CostOfSolution(curr_solution);

		CopyArrays(curr_solution, best_solution);
		cost_of_best_solution = cost_of_curr_solution;

		InTabu swapped_cities; // zamienione miasta
		InTabu good_swap; // zamienione miasta w najlepszym znalezionym sasiedzie

		int* best_neighbour = new int[size];
		int* neighbour = new int[size];

		int neighbour_cost;
		int best_neighbour_cost;
		int steps_without_change = 0;
		
		int time_at_begin = clock() / CLOCKS_PER_SEC;

		int time_to_end = time_left + clock() / CLOCKS_PER_SEC;

		std::vector<std::pair<int, int>> time_table;
		std::pair<int, int> cost_and_time;

		while ( clock() / CLOCKS_PER_SEC < time_to_end) {
			bool insert = false; // jezeli zaszla zmiana sasiada to bedzie dodawane przeksztalcenie do listy tabu
			bool aspir_plus_on = false; 

			best_neighbour_cost = std::numeric_limits<int>::max();
			int plus = this->plus;

			for (int i = 0; i < max; i++) {
				if (clock() / CLOCKS_PER_SEC > time_to_end) {
					break;
				}

				if (aspir_plus_on == true) {
					if (plus <= 0 && i >= min)
						break;
					plus--;
				}

				CopyArrays(curr_solution, neighbour);
				swapped_cities = SwapCities(neighbour);
				neighbour_cost = CostOfSolution(neighbour);

				if ( (neighbour_cost < best_neighbour_cost && CheckTabu(swapped_cities))  ||  IsItVeryGoodSwap(best_neighbour_cost, neighbour_cost)) { //szukanie najlepszego sasiada
					best_neighbour_cost = neighbour_cost;
					CopyArrays(neighbour, best_neighbour);
					good_swap = swapped_cities;
					insert = true;
					aspir_plus_on = true;
				}
			}

			CopyArrays(best_neighbour, curr_solution); // ustawienie najlepszego sasiada jako nastepne rozwiazanie
			cost_of_curr_solution = best_neighbour_cost;

			steps_without_change++;

			if (cost_of_best_solution > cost_of_curr_solution) { // jestli znaleziony sasiad jest lepszy od rozwiazania globalnego
				CopyArrays(curr_solution, best_solution);
				cost_of_best_solution = cost_of_curr_solution;
				steps_without_change = 0;
			}

			for (int i = 0; i < tabu_list.size(); i++) { // zmniejsz kadencje kazdemu przeksztalceniu na liscie tabu
				if (tabu_list[i].time > 0)
					tabu_list[i].time -= 1;
			}

			if (insert) // jesli zaszla zmiana sasiada, dodaj przeksztalcenie do listy tabu
				AddToTabuList(good_swap);
			

			if (steps_without_change > 100) { // jesli nie bylo zmian od jakiegos czasu, zacznij szukac w calkiem innym miejscu
				curr_solution = CreateRandomSolution(curr_solution);
				cost_of_curr_solution = CostOfSolution(curr_solution);
				steps_without_change = 0;
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

		Results results(size);
		results.error = false;
		for (int i = 0; i < size; i++) {
			results.best_solution.push_back(best_solution[i]);
		}
		results.time_table = time_table;

		delete[] best_neighbour;
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

void TabuSearch::CopyArrays(int* from, int* to){
	for (int i = 0; i < size; i++) {
		to[i] = from[i];
	}
}

int * TabuSearch::CreateRandomSolution(int* solution) {
	delete[] solution;
	solution = new int[size];
	for (int i = 0; i < size; i++) {
		solution[i] = i;
	}
	std::random_shuffle(solution, &solution[size]);
	return solution;
}

int * TabuSearch::CreateGreedySolution(int * solution) {
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

int TabuSearch::CostOfSolution(int* solution)
{
	int cost = 0;
	for (int i = 0; i < size - 1; i++) {
		cost += cost_table[solution[i]][solution[i + 1]];
	}
	cost += cost_table[solution[size - 1]][solution[0]];
	return cost;
}

TabuSearch::InTabu TabuSearch::SwapCities(int* neighbour) {
	InTabu swapped_cities;

	swapped_cities.from = rand() % size;

	do {
		swapped_cities.to = rand() % size;
	} while (swapped_cities.to == swapped_cities.from);

	int buffor = 0;
	buffor = neighbour[swapped_cities.from];
	neighbour[swapped_cities.from] = neighbour[swapped_cities.to];
	neighbour[swapped_cities.to] = buffor;

	return swapped_cities;
}

void TabuSearch::AddToTabuList(InTabu add_wannabe) {
	for (int i = 0; i < tabu_list.size(); i++) {
		if (tabu_list[i].from == add_wannabe.from) { // sprawdzenie czy takie polaczenie juz wczesniej bylo
			if (tabu_list[i].to == add_wannabe.to) {
				tabu_list[i].time = 7; // ustawienie czasu trwania kadencji
				extra_punishment[add_wannabe.from][add_wannabe.to] += 2; // zwiekszenie kary do kadencji
				tabu_list[i].time += extra_punishment[add_wannabe.from][add_wannabe.to]; // dodanie kary do kadencji
				return;
			}
		}
	}

	add_wannabe.time = 7; // ustawienie czasu trwania kadencji
	tabu_list.push_back(add_wannabe); // dodanie nowego polaczenia do listy tabu
}

bool TabuSearch::CheckTabu(InTabu to_be_checked) {
	for (int i = 0; i < tabu_list.size(); i++) {
		if (tabu_list[i].from == to_be_checked.from) {
			if (tabu_list[i].to == to_be_checked.to) {
				if (tabu_list[i].time == 0)
					return true;
				else
					return false;
			}
		}
	}
	return true;
}

bool TabuSearch::IsItVeryGoodSwap(int current_cost, int neighbour_cost) {
	//if (current_cost - neighbour_cost >= 0)
	if (current_cost * 0.95f > neighbour_cost)
		return true;
	else
		return false;
}

void TabuSearch::PrintResults() {
	std::cout << std::endl << std::endl << "Wynik to: " << cost_of_best_solution << std::endl;
	for (int i = 0; i < size; i++) {
		if (i % 20 == 0)
			std::cout << std::endl;
		printf("%3d ", best_solution[i]);
	}
	std::cout << std::endl << std::endl;
}
