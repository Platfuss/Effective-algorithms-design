#include "GeneticAlgorithm.h"



GeneticAlgorithm::GeneticAlgorithm() {
	cost_table = NULL;
}


GeneticAlgorithm::~GeneticAlgorithm() {
	if (cost_table != NULL) {
		for (int i = 0; i < size; i++) {
			delete[] cost_table[i];
		}
		delete[] cost_table;
		cost_table = NULL;
	}
}

Results GeneticAlgorithm::StartGeneticAlgorithm(std::string file_name, int max_population_size, float crossing_probability, float mutation_probability, int time_left) {
	int time_to_end = time_left + clock() / CLOCKS_PER_SEC;
	int time_at_begin = clock() / CLOCKS_PER_SEC;
	if (FillCostTable(file_name) && time_left > 0 && max_population_size > 0 && crossing_probability > 0 && mutation_probability > 0 && crossing_probability < 1 && mutation_probability < 1) {
		population.reserve((3/2 * max_population_size + 1) * sizeof(Subject));
		Subject subject;

		for (int i = 0; i < max_population_size; ) { // losowanie populacji poczatkowej
			CreateRandomSolution(subject.path); 
			subject.cost = CostOfSolution(subject.path);
			if (IsUnique(subject)) {
				population.push_back(subject);
				i++;
			}
		}

		std::sort(population.begin(), population.end(), comparator); // sortowanie po kosztach ( najlepszy wynik na poczatku vektora)

		std::vector<std::pair<int, int>> time_table; 
		std::pair<int, int> cost_and_time;

		while (clock() / CLOCKS_PER_SEC < time_to_end) {
			std::vector<Subject> new_generation; // nowe pokolenie
			new_generation.reserve(sizeof(Subject) * (max_population_size / 2 + 1));

			PmxAndMutate( new_generation, max_population_size, crossing_probability, mutation_probability); // wyznaczanie nowego poklenia

			population.insert(population.end(), new_generation.begin(), new_generation.end()); // wprowadzanie nowego pokolenia do populacji

			std::sort(population.begin(), population.end(), comparator); // sortowanie po "sile" osobnikow

			population.resize(max_population_size); // wyrzucanie nasjlabszych osobnikow z populacji

			cost_and_time.first = population[0].cost;
			cost_and_time.second = clock() / CLOCKS_PER_SEC - time_at_begin;

			if (time_table.size() == 0)
				time_table.push_back(cost_and_time);
			else {
				if (time_table.back().second / 10 != cost_and_time.second / 10) {
					time_table.push_back(cost_and_time);
				}
			}
		}

		Results results;
		results.error = false;
		results.time_table = time_table;

		best_solution = population[0].path;
		cost_of_best_solution = population[0].cost;

		return results;
	}
	else {
		Results results;
		results.error = true;
		return results;
	}
}

bool GeneticAlgorithm::FillCostTable(std::string file_name) {
	std::ifstream file;
	file.open(file_name.c_str());
	if (!file.is_open()) {
		size = 0;
		return false;
	}
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
		size = 0;
		return false;
	}
}

bool GeneticAlgorithm::IsUnique(Subject & subject) {

	for (int i = 0; i < population.size(); i++) {
		if (subject.cost == population[i].cost) {
			int starting_position = 0;

			while (subject.path[0] != population[i].path[starting_position])
				starting_position++;

			int subject_iterator = 1, population_subj_iterator = 1;


			for (; subject_iterator < size; subject_iterator++, population_subj_iterator++) {
				if (starting_position + population_subj_iterator == size) {
					starting_position = 0;
					population_subj_iterator = 0;
				}
				if (subject.path[subject_iterator] == population[i].path[starting_position + population_subj_iterator]) { // przeglad wszystkich od paczatku cyklu
					continue; // jesli sie powtarzaja, przegladaj dalej bo moze beda sie roznic na dalszej sciezce
				}
				else {
					return false; // jesli znaleziono roznice to sa rozne
				}
			}
			return true;
		}
	}
	return true;
}

void GeneticAlgorithm::PmxAndMutate(std::vector<Subject> & new_generation, int max_population_size, float crossing_probability, float mutation_probability) {
	int first_crossing_point, second_crossing_point;

	while (new_generation.size() < max_population_size / 2) {
		Subject first_parent, second_parent, first_child, second_child;

		if ( (rand() % 101) / 100.0f <= crossing_probability) {
			int rand_i = rand() % population.size(), rand_j = rand() % population.size();
			first_parent.path = population[rand_i].path; // losowanie rodzicow
			second_parent.path = population[rand_j].path;

			first_parent.cost = population[rand_i].cost;
			second_parent.cost = population[rand_j].cost;

			for (int i = 0; i < size; i++) {
				first_child.path.push_back(-1);
				second_child.path.push_back(-1);
			}

			first_crossing_point = rand() % size; // wyznaczanie punktow miedzy ktorymi zostana wyciete geny
			do {
				second_crossing_point = rand() % size;
			} while (first_crossing_point == second_crossing_point);

			if (first_crossing_point > second_crossing_point) { // ewentualna zamiana kolejnosci jestli pierwszy > drugi
				int buffor = first_crossing_point;
				first_crossing_point = second_crossing_point;
				second_crossing_point = buffor;
			}

			
			CrossParentsGetChild(first_child, first_parent, second_parent, first_crossing_point, second_crossing_point); // wyznaczanie pierwszego dziecka
			CrossParentsGetChild(second_child, second_parent, first_parent, first_crossing_point, second_crossing_point); // wyznaczanie drugiego dziecka

			Mutate( first_child, mutation_probability); // mutacja
			Mutate( second_child, mutation_probability);

			first_child.cost = CostOfSolution(first_child.path);
			second_child.cost = CostOfSolution(second_child.path);

			if (IsUnique(first_child)) // sprawdzanie czy po dodaniu do populacji dzieci nie beda powtarzac sie osobnicy
				new_generation.push_back(first_child);

			if (IsUnique(second_child))
				new_generation.push_back(second_child);
		}
	}
}

void GeneticAlgorithm::CrossParentsGetChild(Subject & child, Subject & fir_parent, Subject & sec_parent, int first_crossing_point, int second_crossing_point) {
	int* imitate_table = new int[size]; // tablica odwzorowan
	for (int i = 0; i < size; i++)
		imitate_table[i] = -1;

	for (int i = first_crossing_point; i <= second_crossing_point; i++) {
		child.path[i] = sec_parent.path[i];  // kopiowanie genow 

		imitate_table[sec_parent.path[i]] = fir_parent.path[i]; // uzupelnianie tablicy odwzorowan
	}


	for (int i = 0; i < size; i++) { // pierwsza proba przepisania genow od pierwszego rodzica w wolnych miejscach
		if (i == first_crossing_point) {
			i = second_crossing_point;
			continue;
		}

		bool conflict = false; // sprawdzenie czy ewentualne przepisanie nie spowoduje powtorzenia sie miasta w sciezce
		for (int j = 0; j < size; j++) {
			if (fir_parent.path[i] == child.path[j]) {
				conflict = true;
				break;
			}
		}

		if (conflict == false) {
			child.path[i] = fir_parent.path[i];
		}
	}

	for (int i = 0; i < size; i++) { // druga proba, z wykorzystaniem tablicy odwzorowan
		if (i == first_crossing_point) {
			i = second_crossing_point;
			continue;
		}

		if (child.path[i] != -1)
			continue;
		
		bool conflict = false;
		for (int j = 0; j < size; j++) {
			if (imitate_table[fir_parent.path[i]] == child.path[j]) {
				conflict = true;
				break;
			}
		}

		if (conflict == false) { // jesli bez problemu da sie przepisac to co jest w tablicy odwzorowan
			child.path[i] = imitate_table[fir_parent.path[i]];
		}
		else { // skakanie po tablicy odwzorowan az do znalezienia odpowiedniego miasta
			conflict = true;
			int position_in_imitate = imitate_table[fir_parent.path[i]];
			while (conflict == true) {
				int position_of_first_negative_one = -1;
				for (int j = 0; j < size; j++) {
					if (position_of_first_negative_one == -1 && child.path[j] == -1)
						position_of_first_negative_one = j;

					if (imitate_table[position_in_imitate] == child.path[j]) {
						position_in_imitate = imitate_table[position_in_imitate];
						break;
					}

					if (j == size - 1) {
						conflict = false;
						child.path[position_of_first_negative_one] = imitate_table[position_in_imitate];
					}
				}
			}
		}
	}

	delete[] imitate_table;
}

void GeneticAlgorithm::Mutate(Subject & subject, float mutation_probability) {
	if ((rand() % 101) / 100.0f < mutation_probability) { // transpozycja
		SwapCities(subject.path);
	}
}

void GeneticAlgorithm::PrintResults() {
	std::cout << std::endl << std::endl << "Wynik to: " << cost_of_best_solution << std::endl;
	for (int i = 0; i < size; i++) {
		if (i % 20 == 0)
			std::cout << std::endl;
		printf("%3d ", best_solution[i]);
	}

	std::cout << std::endl << std::endl;
}


void GeneticAlgorithm::CreateRandomSolution(std::vector<int>& solution) {
	std::vector<int> new_vector;
	for (int i = 0; i < size; i++) {
		new_vector.push_back(i);
	}
	std::random_shuffle(new_vector.begin(), new_vector.end());

	solution = new_vector;
}



int GeneticAlgorithm::CostOfSolution(std::vector<int> solution) {
	int cost = 0;
	for (int i = 0; i < size - 1; i++) {
		cost += cost_table[solution[i]][solution[i + 1]];
	}
	cost += cost_table[solution[size - 1]][solution[0]];
	return cost;
}

void GeneticAlgorithm::SwapCities(std::vector<int>& neighbour) {

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