/*	Name: Chris Boyd
Date: Feb 4,2017
*/

#include <iostream>
#include "TopologicalSort.h"

using namespace std;

struct Leader
{
	string vertex;
	int inDegree;
	int depth;
	Leader *nextLeader;
	Follower *firstFollower;
};

struct Follower
{
	Leader *adjacentLeader;
	Follower* nextFollower;
};


TopologicalSort::TopologicalSort(string fileName) : head(0), tail(0), vertexCount(0)
{
	ifstream input(fileName);

	initialize(input);
	findStartVertex();
	partialOrder();
	if (vertexCount != 0)
		cout << "Not a partial Order" << endl;

	input.close();
}

TopologicalSort::TopologicalSort(string fileName, bool initOnly)
{
	ifstream input(fileName);

	initialize(input);
	print();

	input.close();
	
}

//http://www2.cs.uregina.ca/~hilder/cs340/Algorithms/graphTSInitialization.txt 
//Implements Hilderman's algorithm
void TopologicalSort::initialize(ifstream& input)
{
	string x, y;
	Leader *p, *q;
	Follower *f;

	head = new Leader;
	tail = head;

	while (input >> x >> y)
	{
		p = buildList(x);
		q = buildList(y);
		f = new Follower;
		f->adjacentLeader = q;
		f->nextFollower = p->firstFollower;
		p->firstFollower = f;
		q->inDegree++;
	}
}

//http://www2.cs.uregina.ca/~hilder/cs340/Algorithms/graphTSFindStartVertex.txt
//Implements Hilderman's algorithm
void TopologicalSort::findStartVertex()
{
	Leader *p, *q, *r;
	p = head;
	head = NULL;
	r = tail;
	tail = NULL;

	while (p != r)
	{
		q = p;
		p = p->nextLeader;
		if (q->inDegree == 0)
		{
			q->nextLeader = head;
			head = q;
			if (tail == NULL)
			{
				tail = q;
			}
		}
	}
}


//http://www2.cs.uregina.ca/~hilder/cs340/Algorithms/graphTSPartialOrder.txt
//Implements Hilderman's algorithm
void TopologicalSort::partialOrder()
{
	Follower *f;
	Leader *p = 0;
	Leader *prevHead = 0;
	int depthTracker = 0;

	while (head != NULL)
	{
		//Print new line when Leader depth increases
		//Leaders with same depth will print on same line
		if (head->depth > depthTracker)
		{
			cout << endl;
			depthTracker++;
		}
		cout << head->vertex << " ";

		vertexCount--;
		f = head->firstFollower;
		prevHead = head;
		head = head->nextLeader;
	
		while (f != NULL)
		{
			p = f->adjacentLeader;
			p->inDegree--;

			//Adjacent Leaders depth will be depth of
			//previous Leader that points to it plus 1;
			p->depth = prevHead->depth + 1;

			if (p->inDegree <= 0)
			{
				p->nextLeader = NULL;
				tail->nextLeader = p;
				tail = p;
				if (head == NULL)
				{
					head = tail;
				}
			}
			f = f->nextFollower;
		}
	}
	cout << endl;
}

//http://www2.cs.uregina.ca/~hilder/cs340/Algorithms/graphTSBuildList.txt
//Implements Hilderman's algorithm
Leader* TopologicalSort::buildList(string vertex)
{
	Leader* h = head;
	tail->vertex = vertex;
	while (h->vertex != vertex)
	{
		h = h->nextLeader;
	}
	if (h == tail)
	{
		tail = new Leader;
		vertexCount++;
		h->depth = 0;
		h->inDegree = 0;
		h->firstFollower = NULL;
		h->nextLeader = tail;
	}
	return h;
}


void TopologicalSort::print()
{
	int leaderCounter = 1;
	int followerCounter = 1;
	Leader* leaderPtr = head;
	Follower* followerPtr = 0;

	if (!leaderPtr) return;
	//Loops and prints all leaders
	do
	{
		//Don't print tail, it has garbage values
		if (leaderPtr == tail)
			break;

		cout << "Leader " << leaderCounter << endl;
		cout << "\t" << "vertex = ";
		cout << leaderPtr->vertex << endl;
		cout << "\t" << "inDegree = ";
		cout << leaderPtr->inDegree << endl;
		
		cout << "\t" << "nextLeader = ";
		if (leaderPtr->nextLeader && leaderPtr->nextLeader != tail)
			cout << leaderPtr->nextLeader->vertex;
		else
			cout << "N/A";
		cout << endl;

		//Loops and prints all followers for this leader
		if (followerPtr = leaderPtr->firstFollower)
		{
			followerCounter = 1;
			do
			{
				cout << "\t" << "Follower " << followerCounter << " = ";
				cout << followerPtr->adjacentLeader->vertex << endl;
				followerCounter++;
			} while (followerPtr = followerPtr->nextFollower);
		}
		cout << endl;
		leaderCounter++;
	} while (leaderPtr = leaderPtr->nextLeader);
	
}
