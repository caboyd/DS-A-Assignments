#include "dijkstraShortestPath.h"
#include <iostream>
#include <iomanip>

using namespace std;
static const int HIGH_VALUE = 0x7FFFFFFF; //MAX INT
static const int NO_VERTEX_FOUND = -1;

DijkstraShortestPath::DijkstraShortestPath(string fileName):numOfVertices(19)
{
	//Open file and initialize
	ifstream input(fileName.c_str());
	initialize(input);
	input.close();
}

DijkstraShortestPath::~DijkstraShortestPath()
{
	//Clean up all Followers
	Follower *p, *prev;
	for (int i = 1; i <= numOfVertices; i++)
	{
		p = a[i].firstFollower;
		while (p)
		{
			prev = p;
			p = p->nextFollower;
			delete prev;
		}	
	}
}

void DijkstraShortestPath::print()
{
	for (int i = 1; i <= numOfVertices; i++)
	{
		//Print each Leader
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

		//Print each follower for this leader
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
	//Calls search once per vertex
	for (int i = 1; i <= numOfVertices; i++)
	{
		resetLeaderValues();
		search(i);
	}
}

void DijkstraShortestPath::searchAllAndPrint()
{
	//Calls search once per vertex
	for (int i = 1; i <= numOfVertices; i++)
	{
		//Reset leader values so search works properly
		resetLeaderValues();
		cout << "Searching paths for starting vertex " << i << endl;
		search(i);
		cout << "Starting vertex " << i << " paths" << endl;
		//print out paths for this vertex
		paths();
	}
}

//http://www2.cs.uregina.ca/~hilder/cs340/Algorithms/graphDijkstrasSearch.txt
//Implements Hilderman's Algorithm for Dijkstra's Search
void DijkstraShortestPath::search(int startVertex)
{
	//Holds current vertex index
	int i;
	Follower *p;

	a[startVertex].vertex = startVertex;
	a[startVertex].distance = 0;

	while (1)
	{
		//Iterate through all vertex until all known or no next vertex
		i = findNextVertex();

		if (i == NO_VERTEX_FOUND)
			break;

		a[i].known = true;
		
		//Iterate through all followers and 
		p = a[i].firstFollower;
		while (p != NULL)
		{
			if (a[p->vertex].known == false)
			{
				//update the vertex's distance if the distance is shorter
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

//http://www2.cs.uregina.ca/~hilder/cs340/Algorithms/graphDijkstrasInitialization.txt
//Implements Hilderman's Algorithm for Dijkstra's initialization
void DijkstraShortestPath::initialize(std::ifstream & input)
{
	//Initialize all Leaders
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

	//Read in all edges from input stream
	while (input >> x >> y >> z)
	{
		//Add each edge as a follower
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

//http://www2.cs.uregina.ca/~hilder/cs340/Algorithms/graphDijkstrasPaths.txt
//Implements Hilderman's Algorithm for printing paths
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

//http://www2.cs.uregina.ca/~hilder/cs340/Algorithms/graphDijkstrasFindNextVertex.txt
//Implements Hilderman's algorithm for finding next vertex
int DijkstraShortestPath::findNextVertex()
{
	int nextVertex = NO_VERTEX_FOUND;
	int shortestDistance = HIGH_VALUE;
	for (int i = 1; i <= numOfVertices; i++)
	{
		//Finds vertex with smallest distance that is unknown
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
