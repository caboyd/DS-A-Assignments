#pragma once

#include <string>

const int MAX_NODES = 20;

class EdmondsCarpMaxFlow
{
private:
	int residualCapacity[MAX_NODES][MAX_NODES];
	int currentPath[MAX_NODES];
	bool visitedVertices[MAX_NODES];
	int q[MAX_NODES];
	int numOfNodes;
	int maxFlow;
public:
	EdmondsCarpMaxFlow(std::string fileName);

	void search(int source, int sink);

	bool breadthFirstSearch(int source, int sink);

	void paths();

	void printResidualCapacity();

private:
	void initialization(std::ifstream & input);

	static int min(int a, int b);

	void printMatrix(int m[][MAX_NODES]) const;

};