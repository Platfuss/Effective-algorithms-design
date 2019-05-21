#pragma once
#include <iostream>
#include <vector>
// klasa do zwracania wartosci obliczone przez algorytmy
class Results
{
public:
	Results();
	Results(int);
	~Results();

	bool error; // informacja o bledach w algorytmie
	int size;
	float temperature;

	std::vector<int> best_solution;

	std::vector<std::pair<int, int>> time_table;
};

