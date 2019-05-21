#pragma once
#include <string>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <vector>
#include <math.h>
#include <ctime>
#include "Results.h"

class GeneticAlgorithm {

	struct Subject { // struktura do przechowywaniu informacji o rozwiazaniu
		std::vector<int> path; 
		int cost;
	};

	struct Comparator {
		bool operator() (const Subject &first, const Subject &second) {
			return (first.cost < second.cost);
		}
	} comparator;

	std::vector<Subject> population;

	int cost_of_best_solution; // koszt najlepszego znalezionego rozwiazania
	int size; // ilosc wierzcholkow
	std::vector<int> best_solution; // kolejnosc wierzcholkow w najlepszym rozwiazaniu
	int** cost_table = NULL; // tablica kosztow
	void CreateRandomSolution(std::vector<int>&); // funkcja do generowania losowego rozwiazania
	int CostOfSolution(std::vector<int>); // funkcja do obliczania kosztu rozwiazania
	void SwapCities(std::vector<int>&); // funkcja do zamiany dwoch losowych miast
	bool FillCostTable(std::string); // funkcja do uzupelnienia cost_table oraz innych zmiennych po wczytaniu pliku
	bool IsUnique(Subject &); // funkcja do sprawdzania czy identyczne rozwiazanie nie znajduje sie juz w populacji
	void PmxAndMutate(std::vector<Subject>&, int, float, float); // funkcja krzyzujaca i mutujaca (nowe pokolenie)
	void CrossParentsGetChild(Subject&, Subject &, Subject &, int, int); // funkcja do tworzenia nowych rozwiazan na podstawie juz istniejacych
	void Mutate(Subject&, float); // funkcja mutujaca wywolywana z PmxAndMutate

public:
	GeneticAlgorithm();
	~GeneticAlgorithm();

	Results StartGeneticAlgorithm(std::string,int, float, float, int);

	void PrintResults();

};

