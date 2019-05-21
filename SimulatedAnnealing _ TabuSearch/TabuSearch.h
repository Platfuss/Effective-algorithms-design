#pragma once
#include <string>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <vector>
#include <ctime>

#include "Results.h"

class TabuSearch
{
	struct InTabu { // struktura pomocnicza dla listy tabu oraz zamiany miast(wtedy zmienna time jest nieuzywana)
		int from;
		int to;
		int time;
	};

	std::vector<InTabu> tabu_list; // tablica tabu

	int** extra_punishment; // tablica dodatkowych kar dla czesto wybieranych zmian wierzcholkow
	int** cost_table = NULL; // tablica kosztow
	int* best_solution; // najlepsze znalezione rozwiazanie
	int size; // ilosc wierzcholkow
	int cost_of_best_solution; // koszt najlepszego rozwiazania
	int min, max, plus; // liczby okreslajaca minimalna oraz maksymalna ilosc iteracji w celu znalezienia sasiada

	void CopyArrays(int*, int*); // funkcja do kopiowania zawartosci tablic
	int* CreateRandomSolution(int*); // funkcja generujaca losowe rozwiazanie
	int* CreateGreedySolution(int*); // funkcja generujace zachlanne rozwiazanie
	int CostOfSolution(int*); // koszt rozwiazania
	InTabu SwapCities(int*); // funkcja losujaca sasiada aktualnego rozwiazania
	void AddToTabuList(InTabu); // funkcja dodajaca przeksztalcenie do listy tabu
	bool CheckTabu(InTabu); // funckja sprawdzajaca czy dane przeksztalcenie nie jest zakazane
	bool IsItVeryGoodSwap(int, int); // funkcja sprawdzajaca czy mozna zignorowac liste tabu poniewaz sasiad rozwiazania ma lepsza droge
	bool FillCostTable(std::string); // funkcja uzupelniajaca cost_table i inne zmienne po wczytaniu plik

public:
	void PrintResults();
	Results StartTabuSearch(std::string, int);

	TabuSearch();
	~TabuSearch();



};

