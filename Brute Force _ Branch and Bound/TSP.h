#pragma once
#include <iostream>
#include <queue>
#include "Node.h"
using namespace std;

class TSP {
	int size; // ilosc wierzcholkow
	bool visible = 0; // czy wyswietlac rozwiazania i tablice kosztow (do sprawdzania algorytmow - tak; do seryjnego testowania - nie)

	//do BF
	int best_solution; // wartosc najlepszego znalezionego rozwiazania
	bool* visited; // wskaznik do tablicy zawierajacej "flagi" odwiedzenia wiecholka w danym rozwiazaniu
	int** cost_table; // wskaznik do tablicy kosztow dla przejscia z miasta do miasta
	std::vector <int*> vector_p_int; // wektor ze znalezionymi najlepszymi drogami o tej samej wartosci

	void BFexe(int level, int point, int curr_solution, int* path); // funkcja rekurencyjna dzialajaca wedlug algorytmu Brute Force
	void VectorClear_int(std::vector <int*> &); // funkcja do czyszczenia wektora i bezpiecznego usuwania jego zawartosci

	//do B&B
	int Bound(Node &v); // funkcja do obliczania granicy wierzcholka
	bool CheckVertical(Node &v, int i); // funkcja do sprawdzania czy mozna bedzie dolaczyc wierzcholek do rozwiazania
	bool SearchForNode(Node &v, int j); // funkcja do sprawdzania czy mozna bedzie dolaczyc wierzcholek do rozwiazania
	int Length(Node &v); // funkcja obliczajaca koszt dojscia od wierzcholka 0 do tego
	void ClearVector_Node(std::vector<Node> &v); // funkcja do czyszczenia wektora i bezpiecznego usuwania jego zawartosci

public:
	TSP();
	TSP(int* data, int size, bool visible);

	~TSP();

	void BruteForce();
	void BranchBound();
};

