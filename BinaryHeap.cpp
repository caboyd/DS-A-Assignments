#include "BinaryHeap.h"


BinaryHeap::BinaryHeap(int numOfEdges)
	:q(new Edge[numOfEdges]),
	edgeCount(0)
{}

BinaryHeap::~BinaryHeap()
{
	delete q;
	q = 0;
}

void BinaryHeap::insert(int vertex1, int vertex2, int distance)
{
	Edge e;
	e.distance = distance;
	e.vertex1 = vertex1;
	e.vertex2 = vertex2;

	edgeCount++;
	int i = edgeCount;
	while (i > 1 && e.distance < q[i / 2].distance)
	{
		q[i] = q[1 / 2];
		i = i / 2;
	}
	q[i] = e;
}

Edge BinaryHeap::deleteMin()
{
	// root of q is the edge with the shortest distance
	Edge e = q[1];
	// move the last edge in the tree to the root
	q[1] = q[edgeCount];
	edgeCount--;

	Edge temp = q[1];

	int i = 1;
	//percolate down
	while (i * 2 <= edgeCount)
	{
		//left child
		int child = i * 2;
		//check if right child is smaller than left child
		if (child != edgeCount && q[child + 1].distance < q[child].distance)
			child++;
		//swap child with parent if smaller
		if (q[child].distance < temp.distance)
			q[i] = q[child];
		else
			break;
		i = child;
	}
	q[i] = temp;

	return e;
}
