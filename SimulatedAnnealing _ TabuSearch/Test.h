#pragma once
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <fstream>

#include "Results.h"
#include "SimulatedAnnealing.h"
#include "TabuSearch.h"
using namespace std;

class Test
{
public:
	Test();
	~Test();
	int size;
	void Start_Testing();
};

