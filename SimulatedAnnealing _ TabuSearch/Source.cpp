#include <cstdlib>
#include <fstream>
#include <ctime>
#include <conio.h>
#include <string>
#include <iostream>
#include "TabuSearch.h"
#include "SimulatedAnnealing.h"
#include "Results.h"
#include "Test.h"
using namespace std;

void main() {
	string line;
	int time_left = 0;
	float temperature = 0;
	TabuSearch tabu_search;
	SimulatedAnnealing simulated_annealing;
	srand(static_cast<int> (time(NULL)));

	while (true) {
		system("cls");
		cout << "Wybierz opcje\n" << endl
			<< "1. Podaj nazwe pliku zrodlowego" << endl
			<< "2. Podaj kryterium koncowe" << endl
			<< "3. Tabu Search" << endl
			<< "4. Ustaw wspolczynnik temperatury dla SA" << endl
			<< "5. Simulated Annealing" << endl
			<< endl
			<< "9. Testuj" << endl
			<< endl << "Esc Zakoncz program" << endl << endl;

		char key;

		key = _getch();

		switch (key) {
		case '1': {
			cout << "Podaj nazwe pliku atsp (bez rozszerzenia): ";

			getline(cin, line);
			line += ".atsp";
			break;
		}
		case '2': {
			cout << "Podaj czas zakonczenia algorytmow w sekundach: ";
			cin >> time_left;
			cin.ignore(1000, '\n');
			break;
		}

		case '3': {
			cout << "Licze..." << endl;
			Results results = tabu_search.StartTabuSearch(line, time_left);
			if (results.error == false) {
				system("cls");
				cout << "Wybierz opcje\n" << endl
					<< "1. Podaj nazwe pliku zrodlowego" << endl
					<< "2. Podaj kryterium koncowe" << endl
					<< "3. Tabu Search" << endl
					<< "4. Ustaw wspolczynnik temperatury dla SA" << endl
					<< "5. Simulated Annealing" << endl
					<< endl
					<< "9. Testuj" << endl
					<< endl << "Esc Zakoncz program" << endl << endl;
				tabu_search.PrintResults();
			}
			else
				cout << "Cos poszlo nie tak " << endl;
			break;
		}

		case '4': {
			cout << "Podaj temperature: ";
			cin >> temperature;
			cin.ignore(1000, '\n');
			break;
		}

		case '5': {
			cout << "Licze..." << endl;
			Results results = simulated_annealing.StartSimulatedAnnealing(line, temperature, time_left);
			if (results.error == false) {
				system("cls");
				cout << "Wybierz opcje\n" << endl
					<< "1. Podaj nazwe pliku zrodlowego" << endl
					<< "2. Podaj kryterium koncowe" << endl
					<< "3. Tabu Search" << endl
					<< "4. Ustaw wspolczynnik temperatury dla SA" << endl
					<< "5. Simulated Annealing" << endl
					<< endl
					<< "9. Testuj" << endl
					<< endl << "Esc Zakoncz program" << endl << endl;
				simulated_annealing.PrintResults();
			}
			else
				cout << "Cos poszlo nie tak " << endl;
			break;
		}
		case '9': {
			Test test;
			test.Start_Testing();
			break;
		}
		case 27:
			exit(0);
		}

		cout << endl << "Wcisnij dowolny klawisz by kontynuowac" << endl;
		_getch();
	}
	
}