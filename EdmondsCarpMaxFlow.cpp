#include "EdmondsCarpMaxFlow.h"
#include <iostream>
#include <iomanip>
#include <fstream>

static const int HIGH_VALUE = 0x7FFFFFFF; //MAX INT

using namespace std;

EdmondsCarpMaxFlow::EdmondsCarpMaxFlow(std::string fileName)
	:residualCapacity{0},
	currentPath{0},
	visitedVertices{false},
	q{0},
	numOfNodes(0),
	maxFlow(0)
{
	//Open file and initialize
	ifstream input(fileName.c_str());
	initialization(input);
	input.close();
}

void EdmondsCarpMaxFlow::initialization(std::ifstream& input)
{
	int i;
	int j;
	int capacity;
	int newNumOfNodes = 0;

	for(i = 0; i < MAX_NODES; i++)
	{
		for (j = 0; j < MAX_NODES;j++)
			residualCapacity[i][j] = -1;
	}

	while(input >> i >> j >> capacity)
	{
		residualCapacity[i][j] = capacity;
		residualCapacity[j][i] = 0;
		
		if (i > newNumOfNodes)
			newNumOfNodes = i;
		if (j > newNumOfNodes)
			newNumOfNodes = j;
	}
	numOfNodes = newNumOfNodes;
}

void EdmondsCarpMaxFlow::search(int source, int sink)
{
	bool pathFound;
	int i, j;

	pathFound = breadthFirstSearch(source, sink);
	while (pathFound)
	{
		int pathFlow = HIGH_VALUE;
		j = sink;
		while(j != source)
		{
			i = currentPath[j];
			pathFlow = min(pathFlow, residualCapacity[i][j]);
			j = i;
		}
		j = sink;
		while (j != source)
		{
			i = currentPath[j];
			residualCapacity[i][j] -= pathFlow;
			residualCapacity[j][i] += pathFlow;
			j = i;
		}
		maxFlow += pathFlow;
		pathFound = breadthFirstSearch(source, sink);
		cout << "Residual Capacity Matrix after path found\n\n";
		printResidualCapacity();
		cout << endl;
	}
}

bool EdmondsCarpMaxFlow::breadthFirstSearch(int source, int sink)
{
	int head, tail;
	int i, j;
	for (i = 0; i <= numOfNodes; i++)
	{
		visitedVertices[i] = false;
	}
	head = 1;
	tail = 1;
	q[tail] = source;
	tail++;
	visitedVertices[source] = true;

	while (head != tail)
	{
		i = q[head];
		head++;
		for(j = 0; j <= numOfNodes; j++)
		{
			if(visitedVertices[j] == false && residualCapacity[i][j] > 0)
			{
				q[tail] = j;
				tail++;
				currentPath[j] = i;
				visitedVertices[j] = true;
			}
		}
	}
	return visitedVertices[sink];
}

void EdmondsCarpMaxFlow::paths()
{
	for(int i = 0; i <= numOfNodes; i++)
	{
		for(int j = 0; j <= numOfNodes; j++)
		{
			if(residualCapacity[i][j] != -1)
			{
				cout << i;
				cout << "-(";
				cout << residualCapacity[i][j];
				cout << ")-";
				cout << j;
				cout << endl;
			}
		}
	}
	cout << "MAXFLOW=";
	cout << maxFlow;
	cout << endl;
}

void EdmondsCarpMaxFlow::printResidualCapacity()
{

	printMatrix(residualCapacity);
}

int EdmondsCarpMaxFlow::min(int a, int b)
{
	return (a < b ? a : b);
}

void EdmondsCarpMaxFlow::printMatrix(int m[][MAX_NODES]) const
{
	//Prints nice 2D array
	for (int i = 0; i <= numOfNodes; i++)
	{
		//Print horizontal line under column numbers
		if (i == 1)
		{
			for (int k = 0; k <= numOfNodes; k++)
			{
				cout << "---";
			}
			cout << endl;
		}

		//Print Row Numbers
		if (i == 0)
			cout << setw(2) << internal << " ";
		else
			cout << setw(2) << internal << i;
		cout << "|";

		for (int j = 1; j <= numOfNodes; j++)
		{
			//Print Columns Numbers
			if (i == 0)
				cout << setw(3) << j;
			else
			{
				//Print values
				if (m[i][j] != -1)
					cout << setw(3) << m[i][j];
				else
					cout << setw(3) << ".";
			}
		}
		cout << endl;
	}
	cout << endl;
}
