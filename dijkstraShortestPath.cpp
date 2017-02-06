#include "dijkstraShortestPath.h"
#include <iostream>
#include <iomanip>

using namespace std;

struct Leader
{
	int vertex;
	bool known;
	int distance;
	Follower *firstFollower;
};

struct Follower
{
	int vertex;
	int distance;
	Follower* nextFollower;
};



DijkstraShortestPath::DijkstraShortestPath(std::string fileName):numOfVertices(20)
{
	ifstream input(fileName);
	initialize(input);
	input.close();
}

void DijkstraShortestPath::print()
{}

void DijkstraShortestPath::search(int startVertex)
{}

void DijkstraShortestPath::initialize(std::ifstream & input)
{
	for (int i = 1; i <= numOfVertices; i++)
	{
		a[i].vertex = 
	}
}

void DijkstraShortestPath::paths(int startVertex, int goalVertex)
{}

int DijkstraShortestPath::findNextVertex()
{
	return 0;
}
