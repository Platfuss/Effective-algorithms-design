#pragma once
#include <iostream>
#include <vector>
// klasa do zwracania wartosci obliczone przez algorytmy
class Results
{
public:
	Results();
	~Results();

	bool error; // informacja o bledach w algorytmie
	std::vector<std::pair<int, int>> time_table; // vektor par o wartosci najlepszego rozwiazania w danej chwili czasu
};