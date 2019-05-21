#include <cstdlib>
#include <fstream>
#include <ctime>
#include <conio.h>
#include <string>
#include <iostream>
#include "GeneticAlgorithm.h"
#include "Results.h"
#include "Test.h"
using namespace std;

void main() {
	string line;
	int time_left = 0;
	int population_size = 0;
	float crossing_probability = 0.0f;
	float mutation_probability = 0.0f;
	srand(static_cast<int> (time(NULL)));

	while (true) {
		system("cls");
		cout << "Wybierz opcje\n" << endl
			<< "1. Podaj nazwe pliku zrodlowego" << endl
			<< "2. Podaj maksymalny czas trwania obliczen" << endl
			<< "3. Ustaw rozmiar populacji poczatkowej" << endl
			<< "4. Podaj wspolczynnik krzyzowania" << endl
			<< "5. Podaj wspolczynnik mutacji" << endl
			<< "6. GeneticAlgorithm" << endl
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
			cout << "Podaj rozmiar populacji: ";
			cin >> population_size;
			cin.ignore(1000, '\n');
			break;
		}

		case '4': {
			cout << "Podaj wspolczynnik krzyzowania: ";
			cin >> crossing_probability;
			cin.ignore(1000, '\n');
			break;
		}

		case '5': {
			cout << "Podaj wspolczynnik mutacji: ";
			cin >> mutation_probability;
			cin.ignore(1000, '\n');
			break;
		}
		case '6': {
			GeneticAlgorithm genetic_algorithm;
			cout << "Licze..." << endl;
			Results results = genetic_algorithm.StartGeneticAlgorithm(line, population_size, crossing_probability, mutation_probability, time_left);
			if (results.error == false) {
				system("cls");
				cout << "Wybierz opcje\n" << endl
					<< "1. Podaj nazwe pliku zrodlowego" << endl
					<< "2. Podaj kryterium koncowe" << endl
					<< "3. GeneticAlgorithm" << endl
					<< endl
					<< "9. Testuj" << endl
					<< endl << "Esc Zakoncz program" << endl << endl;
				genetic_algorithm.PrintResults();
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