#include "Test.h"



long long int Test::read_QPC() {
	LARGE_INTEGER count;
	DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
	QueryPerformanceCounter(&count);
	SetThreadAffinityMask(GetCurrentThread(), oldmask);
	return((long long int)count.QuadPart);
}

Test::Test() {
	matrix = NULL;
}


Test::~Test() {
	if (matrix != NULL) {
		delete[] matrix;
		matrix = NULL;
	}
}

void Test::GenMatrix(int size) {
	this->size = size;
	matrix = new int[size * size];
	for (int i = 0; i < size * size; i++) {
		matrix[i] = rand() % 99 + 1;
	}
}

void Test::BFtest() {
	ofstream file;
	long long int frequency = 0, start = 0, elapsed = 0;
	long long int time_array[10];
	bool visible = false;
	QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);

	file.open("BF_test_results.txt");
	if (file.is_open()) {
		cout << "Brute Force: " << endl;
		for (int i = 3; i < 13; i++) {
			elapsed = 0;
			for (int j = 0; j < 100; j++) {
				cout << "Licze BF dla i = " << i << ", j = " << j << endl;
				this->GenMatrix(i);
				TSP *tsp = new TSP(this->matrix, size, visible);
				start = read_QPC();
				tsp->BruteForce();
				elapsed += read_QPC() - start;
			}
			elapsed /= 100;
			time_array[i - 3] = elapsed;
		}

		for (int i = 0; i < 10; i++) {
			file << i + 3 << "  " << setprecision(0) << (1000.0 * time_array[i]) / frequency << endl;
		}
	}
	else
		cout << "Blad otwierania pliku do zapisu wynikow testu BF" << endl;
}

void Test::BBtest() {
	ofstream file;
	long long int frequency = 0, start = 0, elapsed = 0;
	long long int time_array[18];
	bool visible = false;
	QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);

	file.open("BB_test_results.txt");
	if (file.is_open()) {
		cout << "Branch and Bound: " << endl;
		for (int i = 3; i < 21; i++) {
			elapsed = 0;
			for (int j = 0; j < 100; j++) {
				cout << "Licze BB dla i = " << i << ", j = " << j << endl;
				this->GenMatrix(i);
				TSP *tsp = new TSP(this->matrix, size, visible);
				start = read_QPC();
				tsp->BranchBound();
				elapsed += read_QPC() - start;
			}
			elapsed /= 100;
			time_array[i - 3] = elapsed;
		}

		for (int i = 0; i < 18; i++) {
			file << i + 3 << "  " << setprecision(0) << (1000.0 * time_array[i]) / frequency << endl;
		}
	}
	else
		cout << "Blad otwierania pliku do zapisu wynikow testu BB" << endl;
}
