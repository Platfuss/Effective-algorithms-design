#pragma once
#include <vector>
class Node
{
public:
	bool vanish; // czy destruktor ma byc wykonywane 0 - nie, 1 - tak
	int size; // ilosc wierzcholkow
	int bound;  // granica danego wezla
	int* path; // wskaznik na tablice zawierajacy droge od wierzcholka 0 do tego
	int level; // poziom na ktorym znajduje sie wezel, 0

	Node();
	Node(int size, bool new_array);
	~Node();

	void CopyPaths(Node &v); // funkcja do kopiowania wierzcholkow


	struct QueCompare { // struktura wykorzystywana w kolejce prioretytowej
		bool operator()(Node &v, Node &u) {
			return v.bound > u.bound;
		}
	};
};

