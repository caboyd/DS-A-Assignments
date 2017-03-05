/*	Name: Chris Boyd
Date: March 4,2017
*/
#pragma once
#include "AVLTree.h"

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
	KruskalsMST(std::string fileName);
	~KruskalsMST();

	//builds the minimum spanning tree
	void search();
	//prints the edges for the minimum spanning tree
	void tree() const;
	//prints the setNodeTree with VertexNode Linked List
	void print() const;

private:
	//Initializes minQueue with edges
	//and setNodeTree with the SetNode of vertexes
	void initialization(std::ifstream & input);

	//number of current edges in the minimum spanning tree
	int length() const;

	//e is added to the edges in the minimum spanning tree
	void insertUnsorted(Edge e);
};
