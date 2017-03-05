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

	void search();
	void tree() const;
	void print() const;

private:
	void initialization(std::ifstream & input);

	//number of current edges in the minimum spanning tree
	int length() const;

	//e is added to the edges in the minimum spanning tree
	void insertUnsorted(Edge e);
};
