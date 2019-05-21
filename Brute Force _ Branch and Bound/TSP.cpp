#include "TSP.h"


TSP::TSP() {
	visited = NULL;
	cost_table = NULL;
}

TSP::TSP(int* data, int size, bool visible){
	this->size = size;
	this->visible = visible;

	visited = NULL;
	cost_table = NULL;

	best_solution = 0;

	if (size > 0) { // tworzenie tablicy kosztow i uzupelnianie jej
		cost_table = new int*[size];
		for (int i = 0; i < size; i++) {
			cost_table[i] = new int[size];
		}
		int count = 0;
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				cost_table[i][j] = data[count];
				count++;
			}
		}
		if (visible == true) { // jesli tablica ma byc wyswietlona
			printf("Size = %d\n\n", size);
			printf("     ");
			for (int i = 0; i < size; i++) {
				printf("%4d", i);
			}
			printf("\n");
			printf("     ");
			for (int i = 0; i < size; i++) {
				printf("----");
			}
			printf("\n");
			for (int i = 0; i < size; i++) {
				printf("%4d|", i);
				for (int j = 0; j < size; j++) {
					printf("%4d",cost_table[i][j]);
				}
				printf("\n\n");
			}
		}
	}
}


TSP::~TSP() {
	if (visited != NULL) {
		delete[] visited;
		visited = NULL;
	}
	if (cost_table != NULL) {
		for (int i = 0; i < size; i++) {
			delete[] cost_table[i];
		}
		delete[] cost_table;
		cost_table = NULL;
	}
}

//*********************************************************************
//**** BF
//*********************************************************************

void TSP::BruteForce() {
	int* first_path = new int[size - 1]; // wskaznik na tablice ktora sluzy jedynie do rozpoczecia rekurencji
	visited = new bool[size]; // wskaznik do tablicy zawierajacej "flagi" odwiedzenia wiecholka w danym rozwiazaniu
	
	for (int i = 0; i < size; i++)
		visited[i] = false;

	best_solution = -1;
	BFexe(0, 0, 0, first_path); // wywolanie funkcji dla wierzcholka poczatkowego, ktory jest na poziomie 0, sam w sobie ma wartosc 0 i by sie do niego dostac trzeba przejsc trase zero

	if (visible == true) { 
		cout << endl;
		cout << "Solution: " << best_solution << endl;
		cout << "-----------------------------" << endl;
		cout << "Paths: " << endl << endl;
		for (int i = 0; i < vector_p_int.size(); i++) {
			cout << "0  - ";
			for (int j = 0; j < size - 1; j++) {
				printf("%2d  - ", vector_p_int[i][j]);
			}
			cout << " 0" << endl;
		}
		cout << endl;
	}
	VectorClear_int(vector_p_int);
}


void TSP::BFexe(int level, int point, int curr_solution, int* path) {
	int* curr_path = new int[size - 1];
	for (int i = 0; i < size - 1; i++) { // kopiowanie trasy ktora doprowadzila do tego wierzcholka
		curr_path[i] = path[i];
	}

	visited[point] = true; // punkt w ktory wlasnie rozpatrujemy uznajemy za odwiedzony


	for (int i = 0; i < size; i++) { // szukanie nastepnego nieodwiedzonego wiecholka
		if (visited[i] == false) {
			curr_path[level] = i;  // wpisanie wierzcholka do sciezki
			curr_solution += cost_table[point][i]; // zwiekszenie kosztu trasy o wartosc przejscia do wiecholka i
			BFexe(level + 1, i, curr_solution, curr_path); // jesli znaleziono nieodwiedzony wierzcholek zachodzi wywolanie samej siebie z wyzszym poziomem o jeden (dziecko wiecholka), o numerze tego wiecholka, z kosztem dojscia do niego i sciezka od 0 do niego
			curr_solution -= cost_table[point][i];
		}
	}

	bool leaf = true; // sprawdzanie czy dany wiecholek jest lisciem
	for (int i = 0; i < size; i++) {
		if (visited[i] == false)
			leaf = false;
	}
	if (leaf == true) { // jesli jest lisciem
		curr_solution += cost_table[point][0]; // dolaczenie do niego kosztu powrotu do pierwszego miasta
		if (best_solution == -1 || best_solution > curr_solution) { // jesli nie bylo rozwiazania lub rozwiazanie jest lepsze od poprzedniego
			VectorClear_int(vector_p_int); // czyszczenie zapisanych "najlepszych sciezek" (juz nimi nie sa)
			best_solution = curr_solution; 
			int* best_path = new int[size];
			for (int i = 0; i < size; i++) {
				best_path[i] = curr_path[i];
			}
			vector_p_int.push_back(best_path); //zapisanie do wektora najlepszej sciezki
		}
		else
			if (best_solution == curr_solution) { // jesli znaleziono kolejna sciezke o takim samym koszcie
				int* best_path = new int[size];
				for (int i = 0; i < size; i++) {
					best_path[i] = curr_path[i];
				}
				vector_p_int.push_back(best_path); //zapisanie do wektora kolejnej najlepszej sciezki
			}
	}

	visited[point] = false;
	delete [] curr_path;
}

void TSP::VectorClear_int(std::vector <int*> &vector_p_int) {
	for (int i = 0; i < vector_p_int.size(); i++) {
		delete[] vector_p_int[i];
	}
	vector_p_int.clear();
}


//*********************************************************************
//**** B&B
//*********************************************************************

void TSP::BranchBound() {
	std::priority_queue<Node, vector<Node>, Node::QueCompare> queue; // kolejka prioretytowa dla wiecholkow
	Node v(size, true), u(size,false);
	int best = -1; // najlepsze rozwiazanie
	vector <Node> vector_node; // wektor do zapisania najlepszej sciezki

	v.bound = Bound(v); // obliczenie granicy korzenia

	queue.push(v); // uznanie korzenia z wierzcholek obiecujacy
	while (!queue.empty()) { // dopoki kolejka nie jest pusta
		v = queue.top(); // skopiuj pierwszy element kolejki (najmniejsza granica ze wszystkich sie tam znajdujacych)
		queue.pop(); // usun pobrany element

		if (v.bound < best || best == -1) { // jesli nie ma rozwiazania lub granica rozpatrywanego wierzcholka jest lepsza od innej znanej
			u.level = v.level + 1; //zwiekszenie poziomu dla wiecholka pomocniczego u
			for (int i = 1; i < size; i++) { // dla kazdego wiersza tabeli kosztow procz 1.
				if (SearchForNode(v, i) == false) { // sprawdzenie czy nie polaczymy przypadkiem wierzcholka z uzytym wczesniej
					u.CopyPaths(v); // u - wierzcholek pomocniczy
					u.path[u.level] = i; // wpisanie do trasy wiecholka kolejny nieuzyty wiecholek

					if (u.level == size - 2) { // jezeli wierzcholek jest przedostatnim ze wszystkich mozliwych i zostal juz tylko 1 do dodania
						for (int j = 0; j < size; j++) {
							if (SearchForNode(u, j) == false) { //dolozenie ostatniego nieznanego wezla
								u.path[size - 1] = j;
								break;
							}
						}
						u.path[size] = 0; // dolozenie poczatku (zamkniecie cyklu)
						if (best == Length(u)) { // jezeli cykl ma taka sama wage jak wczesniejszy obliczony
							vector_node.push_back(u); // zapamietaj cykl
						}
						if (best > Length(u) || best == -1) { // jesli cykl jest lepszy niz wczesniejszy obliczony lub jest 1. obliczonym
							ClearVector_Node(vector_node); // wymiarz wczesniejsze trasy
							best = Length(u); 
							vector_node.push_back(u);
						}
					}
					else { // jesli wierzcholek nie jest "prawie lisciem"
						u.bound = Bound(u); // policzenie dla niego granicy
						if (best > u.bound || best == -1) { // jesli granica jest lepsza od tej dotad obliczonej
							queue.push(u); // dodaj do kolejki
						}
						else { // jestli wierzcholek nie jest obiecujacy to go usun
							u.vanish = true; 
							u.~Node();
						}
					}
				}
			}
		}
		v.vanish = true; // usun wierzcholek v
		v.~Node();
	}

	if (visible == true) {
		cout << endl;
		cout << "Solution: " << best << endl;
		cout << "-----------------------------" << endl;
		cout << "Paths: " << endl << endl;
		if (vector_node.size() > 0) {
			for (int i = 0; i < vector_node.size(); i++) {
				cout << "0  -  ";
				for (int j = 1; j < size; j++) {
					printf("%2d  - ", vector_node[i].path[j]);
				}
				cout << " 0";
				cout << endl;
			}
			cout << endl;
		}
	}

	ClearVector_Node(vector_node);
}


int TSP::Bound(Node &v) { // liczenie granicy
	int bound = Length(v); // granica = koszt dojscia do rozpatrywanego wierzcholka

	for (int i = 0; i < size; i++) { // szukanie minimum w kazdym rzedzie
		if (SearchForNode(v, i) == true) // sprawdzenie czy w trasie wierzcholka nie ma juz uzytego wierzcholka i
			continue;
			
		int mini_row = -1;
		for (int j = 0; j < size; j++) {
			if (i == j) // jesli sprawdzana jest przekatna
				continue;

			if (i == v.path[v.level] && j == 0) // jestli nastepuje proba polaczenia konca trasy z pierwszym korzeniem
				continue; 

			if (CheckVertical(v, j) == true) // sprawdzanie czy w trasie wierzcholka nie ma uzytego wierzcholka j
				continue;
			
			if (mini_row == -1 || cost_table[i][j] < mini_row) { // jesli w rzedzie nie znaleziono wczesniej minimum lub znaleziona liczba jest mniejsza od wczesniejszego min
				mini_row = cost_table[i][j];
			}
		}	
		bound += mini_row; // po rozpatrzeniu calego rzedu, dodaj znalezione w nim minimum
	}
	return bound;
}


bool TSP::CheckVertical(Node &v, int j) { // funkcja sprawdzajaca czy na trasie wierzcholka nie znajduje sie juz wierzcholek j
	for (int  i = 1; i < v.level; i++) { // jesli sprawdzany jest po kolumnach to v.path[0] = 0, a wierzcholek 0 jest zawsze uzyty bo jest korzeniem jednak zwykle powinien byc brany pod uwage
		if (j == v.path[i]) 
			return true;
	}
	return false;
}

bool TSP::SearchForNode(Node &v, int j) { // funkcja przeszukujaca cala sciezke
	for (int i = 0; i < size; i++) {
		if (v.path[i] == j) {
			return true;
		}
	}
	return false;
}

int TSP::Length(Node &v) { // funkcja liczaca dlugosc trasy od korzenia do rozpatrywanego wierzcholka
	int length = 0;
	for (int i = 0; i < v.size && v.path[i + 1] > 0; i++) { 
		length += cost_table[v.path[i]][v.path[i + 1]];
	}

	if (v.path[size - 1] > 0) { // jestli wierzcholek jest lisciem (ma cos podane na przedostatniej pozycji) to dodaj koszt polaczenia z wierzcholkiem
		length += cost_table[v.path[size - 1]][0];
	}
	return length;
}


void TSP::ClearVector_Node(std::vector<Node> &vector_node) {
	for (int i = 0; i < vector_node.size(); i++) {
		vector_node[i].vanish = true; // pozwol wierzcholkom wywolac destruktor 
		vector_node[i].~Node();
	}
	vector_node.clear();
}