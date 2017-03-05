#pragma once

const int NUM_OF_EDGES = 128;

struct Edge
{
	int vertex1;
	int vertex2;
	int distance;
};

/**
 *	Binary Heap Data Structure for Kruskalls MST priority queue
 */

class BinaryHeap
{
private:
	//Dynamic array for priority queue size
	Edge q[NUM_OF_EDGES];
	int edgeCount;
public:
	//Constructor to initialize Binary Heap size
	explicit BinaryHeap();

	//Insert Edge
	void insert(int vertex1, int vertex2, int distance);

	//get and delete smallest Edge
	Edge deleteMin();
	
};

