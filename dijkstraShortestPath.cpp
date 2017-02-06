#include "dijkstraShortestPath.h"
#include <iostream>
#include <iomanip>

using namespace std;
static const int HIGH_VALUE = 0x7FFFFFFF; //MAX INT
static const int NO_VERTEX_FOUND = -1;





DijkstraShortestPath::DijkstraShortestPath(std::string fileName):numOfVertices(20)
{
	ifstream input(fileName);
	initialize(input);
	input.close();
}

void DijkstraShortestPath::print()
{
	for (int i = 1; i <= numOfVertices; i++)
	{
		cout << "Leader " << i << endl;
		cout << "|" << a[i].vertex << "|";
		if(a[i].known == false)
			cout << "|F|";
		else
			cout << "|T|";

		if (a[i].distance == HIGH_VALUE)
			cout << "|HV|";
		else
			cout << "|" << a[i].distance << "|";

		if (a[i].firstFollower != NULL)
		{
			Follower *p = a[i].firstFollower;
			do
			{
				cout << " -> |";
				cout << p->vertex << "|" << p->distance << "|";
			} while (p = p->nextFollower);
		}
		cout << endl << endl;
	}
}

void DijkstraShortestPath::searchAll()
{
	for (int i = 1; i <= numOfVertices; i++)
	{
		resetLeaderValues();
		search(i);
	}
}

void DijkstraShortestPath::searchAllAndPrint()
{
	for (int i = 1; i <= numOfVertices; i++)
	{
		resetLeaderValues();
		cout << "Searching paths for starting vertex " << i << endl;
		search(i);
		cout << "Starting vertex " << i << " paths" << endl;
		paths();
	}
}

void DijkstraShortestPath::search(int startVertex)
{
	//Holds current vertex index
	int i;
	Follower *p;

	a[startVertex].vertex = startVertex;
	a[startVertex].distance = 0;

	while (1)
	{
		i = findNextVertex();
		if (i == NO_VERTEX_FOUND)
			break;
		a[i].known = true;
		p = a[i].firstFollower;
		while (p != NULL)
		{
			if (a[p->vertex].known == false)
			{
				if (a[i].distance + p->distance < a[p->vertex].distance)
				{
					a[p->vertex].distance = a[i].distance + p->distance;
					a[p->vertex].vertex = i;
				}
			}
			p = p->nextFollower;
		}
	}
}

void DijkstraShortestPath::initialize(std::ifstream & input)
{
	for (int i = 1; i <= numOfVertices; i++)
	{
		a[i].vertex = 0;
		a[i].known = false;
		a[i].distance = HIGH_VALUE;
		a[i].firstFollower = NULL;
	}

	int x = 0, y = 0, z = 0;
	Follower *p;
	int newNumOfVertices = 0;

	while (input >> x >> y >> z)
	{
		p = new Follower;
		p->vertex = y;
		p->distance = z;
		p->nextFollower = a[x].firstFollower;
		a[x].firstFollower = p;

		//Reduce numOfVertices to the number this input file has.
		if (x > newNumOfVertices)
			newNumOfVertices = x;
		if (y > newNumOfVertices)
			newNumOfVertices = y;
	}
	numOfVertices = newNumOfVertices;
}

void DijkstraShortestPath::paths()
{
	for (int i = 1; i <= numOfVertices; i++)
	{

		int j = i;
		while (j != a[j].vertex && a[j].vertex != 0)
		{
			cout << j << " <- ";
			j = a[j].vertex;
		}
		if(a[j].vertex != 0)
			cout << j << endl << endl;
	}
}

int DijkstraShortestPath::findNextVertex()
{
	int nextVertex = NO_VERTEX_FOUND;
	int shortestDistance = HIGH_VALUE;
	for (int i = 1; i <= numOfVertices; i++)
	{
		if (a[i].distance < shortestDistance and a[i].known == false)
		{
			nextVertex = i;
			shortestDistance = a[i].distance;
		}
	}
	return nextVertex;
}

void DijkstraShortestPath::resetLeaderValues()
{
	for (int i = 1; i <= numOfVertices; i++)
	{
		a[i].vertex = 0;
		a[i].known = false;
		a[i].distance = HIGH_VALUE;
	}
}
