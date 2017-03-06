/*	Name: Chris Boyd
Date: March 4,2017
*/
#include "BinaryHeap.h"

BinaryHeap::BinaryHeap()
	:nodeCount(0)
{
	for (int i = 0; i < MAX_NODES; i++)
		q[i] = PCTreeNode{};
}

void BinaryHeap::insert(PCTreeNode node)
{
	nodeCount++;
	int i = nodeCount;
	while (i > 1 && node.frequency < q[i / 2].frequency)
	{
		q[i] = q[i / 2];
		i = i / 2;
	}
	q[i] = node;
}

PCTreeNode BinaryHeap::deleteMin()
{
	// root of q is the edge with the shortest distance
	PCTreeNode node = q[1];
	// move the last edge in the tree to the root
	q[1] = q[nodeCount];
	nodeCount--;

	PCTreeNode temp = q[1];

	int i = 1;
	//percolate down
	while (i * 2 <= nodeCount)
	{
		//left child
		int child = i * 2;
		//check if right child is smaller than left child
		if (child != nodeCount && q[child + 1].frequency < q[child].frequency)
			child++;
		//swap child with parent if smaller
		if (q[child].frequency < temp.frequency)
			q[i] = q[child];
		else
			break;
		i = child;
	}
	q[i] = temp;

	return node;
}
