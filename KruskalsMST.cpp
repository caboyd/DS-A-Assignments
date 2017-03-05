#include "KruskalsMST.h"
#include <iostream>
#include <iomanip>

using namespace std;

KruskalsMST::KruskalsMST(string fileName) 
	:minQueue(),
	setNodeTree(),
	minSpanningTree{0},
	vertexCount(20)
{
	//Open file and initialize
	ifstream input(fileName.c_str());
	initialization(input);
	input.close();
}

KruskalsMST::~KruskalsMST()
{
}

void KruskalsMST::initialization(std::ifstream & input)
{
	int vertex1 = 0;
	int vertex2 = 0;
	int distance = 0;

	while (input >> vertex1 >> vertex2 >> distance)
	{
		minQueue.insert(vertex1, vertex2, distance);
		bool result = setNodeTree.insert(vertex1, vertexCount);
		if(result)
		{
			SetNode* v = setNodeTree.find(vertex1);
			v->makeSet();
		}
		result = setNodeTree.insert(vertex2, vertexCount);
		if (result)
		{
			SetNode* v = setNodeTree.find(vertex2);
			v->makeSet();
		}
	}
}
void KruskalsMST::search()
{
	while (length() < vertexCount - 1)
	{
		Edge e = minQueue.deleteMin();

		SetNode* v1 = setNodeTree.find(e.vertex1);
		SetNode* v2 = setNodeTree.find(e.vertex2);

		if(v1->getSubSet() != v2->getSubSet())
		{
			// e is added to the edges in the minimum spanning tree
			insertUnsorted(e);

			// merge the two subsets in the avl tree
			// always move the smaller subset to the larger subset
			if(v1->getSubSet()->size >= v2->getSubSet()->size)
				setNodeTree.unionize(v1, v2);
			else
				setNodeTree.unionize(v2, v1);
		}
	}
}

void KruskalsMST::tree()
{
	for (int i = 0; i < length() - 1; i++)
	{
		cout << minSpanningTree[i].vertex1;
		cout << "--";
		cout << minSpanningTree[i].vertex2;
		cout << " (LENGTH=";
		cout << minSpanningTree[i].distance;
		cout << ")";
		cout << endl;
	}
}

int KruskalsMST::length() const
{
	int count = 0;
	for(int i = 0; i < MST_SIZE; i++)
	{
		//if vertex1 is 0 then there is no edge
		if (minSpanningTree[i].vertex1 == 0)
			return count;
		count++;
	}
	return count;
}

void KruskalsMST::insertUnsorted(Edge e)
{
	for(int i = 0; i < MST_SIZE; i++)
	{
		//if vertex1 is 0 then there is no edge
		if(minSpanningTree[i].vertex1 == 0)
		{
			minSpanningTree[i] = e;
		}
	}
}
