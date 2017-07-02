/*	Chris Boyd
 *	March 5, 2017
 */
#pragma once

const int MAX_NODES = 255;

struct PCTreeNode
{
	char character;
	int frequency;
	PCTreeNode* left;
	PCTreeNode* right;
};

/**
 *	Binary Heap Data Structure for Huffmans Prefix Code priority queue
 *	Each PCTreeNode in the binary heap is the root of a Binary Search Tree
 */

class BinaryHeap
{
private:
	//Array for priority queue size
	PCTreeNode q[MAX_NODES];
	int nodeCount;
public:
	//Constructor to initialize Binary Heap size
	BinaryHeap();

	//Insert PCTreeNode
	void insert(PCTreeNode node);

	//get and delete smallest PCTreeNode
	PCTreeNode deleteMin();
	
};

