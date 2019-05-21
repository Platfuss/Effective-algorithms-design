#include "Test.h"



Test::Test()
{
}


Test::~Test()
{
}

void Test::Start_Testing() {
	ofstream genetic_ftv47_50, genetic_ftv47_100, genetic_ftv47_150, genetic_ftv170_50, genetic_ftv170_100, genetic_ftv170_150, genetic_rbg403_50, genetic_rbg403_100, genetic_rbg403_150;


	genetic_ftv47_50.open("genetic_ftv47_50.txt");
	if (genetic_ftv47_50.is_open()) {
		for (int i = 0; i < 10; i++) {
			GeneticAlgorithm genetic_algorithm;
			cout << "genetic_ftv47_50 " << i << endl;

			Results results = genetic_algorithm.StartGeneticAlgorithm("ftv47.atsp", 50, 0.8f, 0.01f, 120);
			for (int j = 0; j < results.time_table.size(); j++)
				genetic_ftv47_50 << results.time_table[j].first << " ";
			genetic_ftv47_50 << endl;
		}
		genetic_ftv47_50.close();
	}
	else
		cout << "Blad otwierania pliku do zapisu wynikow testu genetic_ftv47_50" << endl;

	//----------------------------------------------------------------------------------------------------------

	genetic_ftv47_100.open("genetic_ftv47_100.txt");
	if (genetic_ftv47_100.is_open()) {
		for (int i = 0; i < 10; i++) {
			GeneticAlgorithm genetic_algorithm;
			cout << "genetic_ftv47_100 " << i << endl;

			Results results = genetic_algorithm.StartGeneticAlgorithm("ftv47.atsp", 100, 0.8f, 0.01f, 120);
			for (int j = 0; j < results.time_table.size(); j++)
				genetic_ftv47_100 << results.time_table[j].first << " ";
			genetic_ftv47_100 << endl;
		}
		genetic_ftv47_100.close();
	}
	else
		cout << "Blad otwierania pliku do zapisu wynikow testu genetic_ftv47_100" << endl;

	//----------------------------------------------------------------------------------------------------------

	genetic_ftv47_150.open("genetic_ftv47_150.txt");
	if (genetic_ftv47_150.is_open()) {
		for (int i = 0; i < 10; i++) {
			GeneticAlgorithm genetic_algorithm;
			cout << "genetic_ftv47_150 " << i << endl;

			Results results = genetic_algorithm.StartGeneticAlgorithm("ftv47.atsp", 150, 0.8f, 0.01f, 120);
			for (int j = 0; j < results.time_table.size(); j++)
				genetic_ftv47_150 << results.time_table[j].first << " ";
			genetic_ftv47_150 << endl;
		}
		genetic_ftv47_150.close();
	}
	else
		cout << "Blad otwierania pliku do zapisu wynikow testu genetic_ftv47_150" << endl;

	//----------------------------------------------------------------------------------------------------------

	genetic_ftv170_50.open("genetic_ftv170_50.txt");
	if (genetic_ftv170_50.is_open()) {
		for (int i = 0; i < 10; i++) {
			GeneticAlgorithm genetic_algorithm;
			cout << "genetic_ftv170_50 " << i << endl;

			Results results = genetic_algorithm.StartGeneticAlgorithm("ftv170.atsp", 50, 0.8f, 0.01f, 240);
			for (int j = 0; j < results.time_table.size(); j++)
				genetic_ftv170_50 << results.time_table[j].first << " ";
			genetic_ftv170_50 << endl;
		}
		genetic_ftv170_50.close();
	}
	else
		cout << "Blad otwierania pliku do zapisu wynikow testu genetic_ftv170_50" << endl;

	//----------------------------------------------------------------------------------------------------------

	genetic_ftv170_100.open("genetic_ftv170_100.txt");
	if (genetic_ftv170_100.is_open()) {
		for (int i = 0; i < 10; i++) {
			GeneticAlgorithm genetic_algorithm;
			cout << "genetic_ftv170_100 " << i << endl;

			Results results = genetic_algorithm.StartGeneticAlgorithm("ftv170.atsp", 100, 0.8f, 0.01f, 240);
			for (int j = 0; j < results.time_table.size(); j++)
				genetic_ftv170_100 << results.time_table[j].first << " ";
			genetic_ftv170_100 << endl;
		}
		genetic_ftv170_100.close();
	}
	else
		cout << "Blad otwierania pliku do zapisu wynikow testu genetic_ftv170_100" << endl;

	//----------------------------------------------------------------------------------------------------------

	genetic_ftv170_150.open("genetic_ftv170_150.txt");
	if (genetic_ftv170_150.is_open()) {
		for (int i = 0; i < 10; i++) {
			GeneticAlgorithm genetic_algorithm;
			cout << "genetic_ftv170_150 " << i << endl;

			Results results = genetic_algorithm.StartGeneticAlgorithm("ftv170.atsp", 150, 0.8f, 0.01f, 240);
			for (int j = 0; j < results.time_table.size(); j++)
				genetic_ftv170_150 << results.time_table[j].first << " ";
			genetic_ftv170_150 << endl;
		}
		genetic_ftv170_150.close();
	}
	else
		cout << "Blad otwierania pliku do zapisu wynikow testu genetic_ftv170_150" << endl;

	//----------------------------------------------------------------------------------------------------------

	genetic_rbg403_50.open("genetic_rbg403_50.txt");
	if (genetic_rbg403_50.is_open()) {
		for (int i = 0; i < 10; i++) {
			GeneticAlgorithm genetic_algorithm;
			cout << "genetic_rbg403_50 " << i << endl;

			Results results = genetic_algorithm.StartGeneticAlgorithm("rbg403.atsp", 50, 0.8f, 0.01f, 360);
			for (int j = 0; j < results.time_table.size(); j++)
				genetic_rbg403_50 << results.time_table[j].first << " ";
			genetic_rbg403_50 << endl;
		}
		genetic_rbg403_50.close();
	}
	else
		cout << "Blad otwierania pliku do zapisu wynikow testu genetic_rbg403_50" << endl;

	//----------------------------------------------------------------------------------------------------------

	genetic_rbg403_100.open("genetic_rbg403_100.txt");
	if (genetic_rbg403_100.is_open()) {
		for (int i = 0; i < 10; i++) {
			GeneticAlgorithm genetic_algorithm;
			cout << "genetic_rbg403_100 " << i << endl;

			Results results = genetic_algorithm.StartGeneticAlgorithm("rbg403.atsp", 100, 0.8f, 0.01f, 360);
			for (int j = 0; j < results.time_table.size(); j++)
				genetic_rbg403_100 << results.time_table[j].first << " ";
			genetic_rbg403_100 << endl;
		}
		genetic_rbg403_100.close();
	}
	else
		cout << "Blad otwierania pliku do zapisu wynikow testu genetic_rbg403_100" << endl;

	//----------------------------------------------------------------------------------------------------------

	genetic_rbg403_150.open("genetic_rbg403_150.txt");
	if (genetic_rbg403_150.is_open()) {
		for (int i = 0; i < 10; i++) {
			GeneticAlgorithm genetic_algorithm;
			cout << "genetic_rbg403_150 " << i << endl;

			Results results = genetic_algorithm.StartGeneticAlgorithm("rbg403.atsp", 150, 0.8f, 0.01f, 360);
			for (int j = 0; j < results.time_table.size(); j++)
				genetic_rbg403_150 << results.time_table[j].first << " ";
			genetic_rbg403_150 << endl;
		}
		genetic_rbg403_150.close();
	}
	else
		cout << "Blad otwierania pliku do zapisu wynikow testu genetic_rbg403_150" << endl;

	//----------------------------------------------------------------------------------------------------------



}




