#pragma once
#include <string>

const int MAX_NODES = 20;

//Data structure to perform EdmondsCarp Max Flow Algorithm
//on directed graph with source and sink given.
//Edges are read from input file.
class EdmondsCarpMaxFlow
{
private:
	int residualCapacity[MAX_NODES][MAX_NODES];
	//current flow path from breadthFirstSearch
	int currentPath[MAX_NODES];
	//Tracks visited vertices in search method
	bool visitedVertices[MAX_NODES];

	//Used to ensure breadth first order
	int q[MAX_NODES];
	//number of nodes in graph
	int numOfNodes;
	//max flow for netowrk from source to sink
	int maxFlow;
public:

	//Reads an input file and sends ifstream to initialization
	//Initializes variables to 0
	EdmondsCarpMaxFlow(std::string fileName);

	//Finds all flow paths and calcualtes maxflow
	void search(int source, int sink);

	//Finds a flow path that has residual capicity
	//  from source to sink
	bool breadthFirstSearch(int source, int sink);

	//Prints flow path edges and capacities
	void paths();

	//Prints residualCapicity in a formatted 2d matrix
	void printResidualCapacity();

private:
	//read ifstream and adds edges to residualCapacity
	//calculates numOfNodes from input edges
	void initialization(std::ifstream & input);

	//calculates min of two ints
	static int min(int a, int b);

	//Prings formated 2d matrix of size numOfNodes
	void printMatrix(int m[][MAX_NODES]) const;

};