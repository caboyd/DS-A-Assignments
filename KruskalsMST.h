#pragma once
#include "AVLTree.h"
#include <fstream>
#include <string>
#include "BinaryHeap.h"

const int MST_SIZE = 20;

class KruskalsMST
{
private:
	BinaryHeap minQueue;
	AVLTree setNodeTree;
	Edge minSpanningTree[MST_SIZE];
	int vertexCount;

public:
	explicit KruskalsMST(std::string fileName);

	~KruskalsMST();

	void initialization(std::ifstream & input);
	void search();
	void tree();
private:
	//number of current edges in the minimum spanning tree
	int length() const;

	//e is added to the edges in the minimum spanning tree
	void insertUnsorted(Edge e);
};
