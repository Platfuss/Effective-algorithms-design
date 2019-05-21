#pragma once
#include <string>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <vector>
#include <math.h>
#include <ctime>
#include "Results.h"

class SimulatedAnnealing
{
	int cost_of_best_solution; // koszt najlepszego znalezionego rozwiazania
	int size; // ilosc wierzcholkow
	int* best_solution; // kolejnosc wierzcholkow w najlepszym rozwiazaniu
	int** cost_table = NULL; // tablica kosztow
	int* CreateRandomSolution(int*); // funkcja do generowania losowego rozwiazania
	int* CreateGreedySolution(int*); // fukcja do generowania rozwiazania metoda zachlanna
	int CostOfSolution(int*); // funkcja do obliczania kosztu rozwiazania
	void SwapCities(int*); // funkcja do zamiany dwoch losowych miast
	void CopyArrays(int* from, int* to); // funkcja do kopiowania zawartosci tablic 
	float MeasureTemperature(int*); // funkcja do obliczenia temperatury poczatkowej
	float CountProbability(int, float); // funkcja do obliczenia wartosci, ktora zdecyduje o rozwazeniu gorszego od akutalnego rozwiazania
	bool FillCostTable(std::string); // funkcja do uzupelnienia cost_table oraz innych zmiennych po wczytaniu pliku

public:
	SimulatedAnnealing();
	~SimulatedAnnealing();

	Results StartSimulatedAnnealing(std::string, float, int);

	void PrintResults();

};

