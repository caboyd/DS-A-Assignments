#pragma once

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
	Edge* q;
	int edgeCount;
public:
	//Constructor to initialize Binary Heap size to 128
	BinaryHeap();
	//Constructor to initialize Binary Heap size
	explicit BinaryHeap(int numOfEdges = 128);

	//Destructor to delete q
	~BinaryHeap();

	//Insert Edge
	void insert(int vertex1, int vertex2, int distance);

	//get and delete smallest Edge
	Edge deleteMin();
	
};

