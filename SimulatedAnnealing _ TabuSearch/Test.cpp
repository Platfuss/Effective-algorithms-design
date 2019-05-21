#include "Test.h"



Test::Test()
{
}


Test::~Test()
{
}

void Test::Start_Testing() {


	ofstream tabu_ftv47, tabu_ftv170, tabu_rbg403, simulated_ftv47, simulated_ftv170, simulated_rbg403;


	//tabu_ftv47.open("tabu_ftv47.txt");
	//if (tabu_ftv47.is_open()) {
	//	for (int i = 0; i < 10; i++) {
	//		TabuSearch ts;
	//		cout << "tabu_ftv47 " << i << endl;

	//		Results results = ts.StartTabuSearch("ftv47.atsp", 40);
	//		size = results.size;
	//		for (int j = 0; j < results.time_table.size(); j++)
	//			tabu_ftv47 << results.time_table[j].first << " ";

	//		tabu_ftv47 << "   ";
	//		for (int j = 0; j < size; j++) {
	//			tabu_ftv47 << results.best_solution[j] << " ";
	//		}
	//		tabu_ftv47 << endl;
	//	}

	//	tabu_ftv47.close();
	//}
	//else
	//	cout << "Blad otwierania pliku do zapisu wynikow testu tabu_ftv47" << endl;


	////----------------------------------------------------------------------------------------------------------


	//tabu_ftv170.open("tabu_ftv170.txt");
	//if (tabu_ftv170.is_open()) {
	//	for (int i = 0; i < 10; i++) {
	//		TabuSearch ts;
	//		cout << "tabu_ftv170 " << i << endl;

	//		Results results = ts.StartTabuSearch("ftv170.atsp", 40);
	//		size = results.size;
	//		for (int j = 0; j < results.time_table.size(); j++)
	//			tabu_ftv170 << results.time_table[j].first << " ";

	//		tabu_ftv170 << "   ";
	//		for (int j = 0; j < size; j++) {
	//			tabu_ftv170 << results.best_solution[j] << " ";
	//		}
	//		tabu_ftv170 << endl;
	//	}

	//	tabu_ftv170.close();
	//}
	//else
	//	cout << "Blad otwierania pliku do zapisu wynikow testu tabu_ftv170" << endl;


	////----------------------------------------------------------------------------------------------------------


	//tabu_rbg403.open("tabu_rbg403.txt");
	//if (tabu_rbg403.is_open()) {
	//	for (int i = 0; i < 10; i++) {
	//		TabuSearch ts;
	//		cout << "tabu_rbg403 " << i << endl;

	//		Results results = ts.StartTabuSearch("rbg403.atsp", 40);
	//		size = results.size;
	//		for (int j = 0; j < results.time_table.size(); j++)
	//			tabu_rbg403 << results.time_table[j].first << " ";

	//		tabu_rbg403 << "   ";
	//		for (int j = 0; j < size; j++) {
	//			tabu_rbg403 << results.best_solution[j] << " ";
	//		}
	//		tabu_rbg403 << endl;
	//	}

	//	tabu_rbg403.close();
	//}
	//else
	//	cout << "Blad otwierania pliku do zapisu wynikow testu tabu_rbg403" << endl;



	//----------------------------------------------------------------------------------------------------------


	simulated_ftv47.open("simulated_ftv47.txt");
	if (simulated_ftv47.is_open()) {
		for (int i = 0; i < 10; i++) {
			SimulatedAnnealing sa;
			cout << "simulated_ftv47 " << i << endl;

			Results results = sa.StartSimulatedAnnealing("ftv47.atsp", 0.95f, 40);
			size = results.size;
			for (int j = 0; j < results.time_table.size(); j++)
				simulated_ftv47 << results.time_table[j].first << " ";

			simulated_ftv47 << "   " << results.temperature << "   ";
			for (int j = 0; j < size; j++) {
				simulated_ftv47 << results.best_solution[j] << " ";
			}
			simulated_ftv47 << endl;
		}

		simulated_ftv47.close();
	}
	else
		cout << "Blad otwierania pliku do zapisu wynikow testu simulated_ftv47" << endl;


	//----------------------------------------------------------------------------------------------------------


	simulated_ftv170.open("simulated_ftv170.txt");
	if (simulated_ftv170.is_open()) {
		for (int i = 0; i < 10; i++) {
			SimulatedAnnealing sa;
			cout << "simulated_ftv170 " << i << endl;

			Results results = sa.StartSimulatedAnnealing("ftv170.atsp", 0.99f, 40);
			size = results.size;
			for (int j = 0; j < results.time_table.size(); j++)
				simulated_ftv170 << results.time_table[j].first << " ";

			simulated_ftv170 << "   " << results.temperature << "   ";
			for (int j = 0; j < size; j++) {
				simulated_ftv170 << results.best_solution[j] << " ";
			}
			simulated_ftv170 << endl;
		}

		simulated_ftv170.close();
	}
	else
		cout << "Blad otwierania pliku do zapisu wynikow testu simulated_ftv170" << endl;


	//----------------------------------------------------------------------------------------------------------


	simulated_rbg403.open("simulated_rbg403.txt");
	if (simulated_rbg403.is_open()) {
		for (int i = 0; i < 10; i++) {
			SimulatedAnnealing sa;
			cout << "simulated_rbg403 " << i << endl;

			Results results = sa.StartSimulatedAnnealing("rbg403.atsp", 0.95f, 40);
			size = results.size;
			for (int j = 0; j < results.time_table.size(); j++)
				simulated_rbg403 << results.time_table[j].first << " ";

			simulated_rbg403 << "   " << results.temperature << "   ";
			for (int j = 0; j < size; j++) {
				simulated_rbg403 << results.best_solution[j] << " ";
			}
			simulated_rbg403 << endl;
		}

		simulated_rbg403.close();
	}
	else
		cout << "Blad otwierania pliku do zapisu wynikow testu simulated_rbg403" << endl;



}




