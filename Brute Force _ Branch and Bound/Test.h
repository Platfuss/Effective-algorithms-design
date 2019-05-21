#pragma once
#include <stdlib.h>
#include <windows.h>
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

#include "TSP.h"

class Test {
	int* matrix;
	int size;
	long long int read_QPC();
public:
	Test();
	~Test();
	void GenMatrix(int size);
	void BFtest();
	void BBtest();
};

