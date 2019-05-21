#include "Node.h"



Node::Node() {
	path = nullptr;
}

Node::Node(int size, bool new_array) {
	vanish = 0; 
	bound = 0;
	level = 0; 
	this->size = size;
	if (new_array) {
		path = new int[size + 1];
		for (int i = 0; i < size + 1; i++)
			path[i] = 0;
	}
}

Node::~Node() {
	if (vanish == true && path != nullptr) {
		delete[] path;
		path = nullptr;
	}
}

void Node::CopyPaths(Node &v) {
	this->vanish = false;
	this->path = new int[size + 1];
	for (int i = 0; i < size + 1; i++)
		this->path[i] = v.path[i];
}
