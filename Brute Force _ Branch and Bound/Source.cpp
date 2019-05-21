#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <math.h>
#include <conio.h>

#include "Test.h"
#include "TSP.h"

using namespace std;

void main() {
	srand(time(NULL));

	int* data = NULL;
	int size = 0;
	bool good_data = false; //czy wskaznik data zawiera adres do tablicy z poprawnym danymi

	while (true) {
		system("cls");
		cout << "Wybierz opcje\n"
			<< "1. Wczytac dane z pliku" << endl
			<< "2. Brute Force" << endl
			<< "3. Branch and Bound" << endl
			<< endl
			<< "T. Przeprowadz testy" << endl
			<< endl
			<< "Esc Zakoncz program" << endl
			<< endl;

		char key;
		//cin >> key;
		//cin.ignore(1000, '\n');
		key = _getch();

		switch (key) {
		case '1': {
			if (data != NULL) {
				delete[] data;
				data = NULL;
			}
			cout << "Podaj nazwe pliku txt (bez rozszerzenia): ";
			string line;
			getline(cin, line);
			line += ".txt";

			ifstream file;
			file.open(line.c_str());

			if (file.is_open()) {
				int single_number;

				file >> size;
				if (file.fail()) {
					cout << "File error - READ SIZE" << endl;
					good_data = false;
				}
				else {
					data = new int[pow(size, 2)];
					int level = 0;			//zmienna pomocnicza do sprawdzenia czy liczby < 1 beda znajdowac sie jedynie na przekatnej macierzy
					for (int i = 0; i < pow(size, 2); i++) {
						file >> single_number;
						if (file.fail()) {
							good_data = false;
							cout << "File error - READ DATA" << endl;
							break;
						}
						else {
							if (level*size + level != i && single_number < 1) {
								cout << "W pliku znajduja sie zle dane!" << endl;
								good_data = false;
								break;
							}
							if (i%size == 0 && i != 0)
								level++;
							data[i] = single_number;
							good_data = true;
						}
					}
				}
				file.close();
			}
			else {
				good_data = false;
				cout << "File error - OPEN" << endl;
			}
			break;
		} // koniec case 1
		case '2': {
			bool visible = true;
			if (good_data == true) {
				TSP *tsp = new TSP(data, size, visible);
				tsp->BruteForce();
			}
			else
				cout << "Podane sa zle dane" << endl;
			break;
		}
		case '3': {
			bool visible = true;
			if (good_data == true) {
				TSP *tsp = new TSP(data, size, visible);
				tsp->BranchBound();
			}
			else
				cout << "Podane sa zle dane" << endl;
			break;
		}
		case 'T': {
			Test test;
			test.BFtest();

			//test.BBtest();

			break;
		}
		case 27: {
			exit(0);
		}
		} // koniec switch
		cout << "Wcisnij dowolny klawisz by kontynuowac" << endl;
		_getch();
	} // koniec while
}