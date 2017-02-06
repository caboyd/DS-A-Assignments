#include "floydShortestPath.h"
#include <iostream>
#include <iomanip>

using namespace std;
static const int HIGH_VALUE = 0x7FFFFFFF; //MAX INT


FloydShortestPath::FloydShortestPath(string fileName):numOfVertices(19)
{
	ifstream input(fileName.c_str());
	initialize(input);
	input.close();
}

void FloydShortestPath::searchAndPrint()
{
	print();
	cout << "Searching for paths" << endl;
	search();
	for (int i = 1; i <= numOfVertices; i++)
	{
		//Prints all paths for every start vertex
		cout << "Listing paths for start vertex " << i << endl;
		for (int j = 1; j <= numOfVertices; j++)
		{
			if (i != j && distance[i][j] != HIGH_VALUE)
				paths(i, j);
		}
	}
}

//http://www2.cs.uregina.ca/~hilder/cs340/Algorithms/dynprogFloydsSearch.txt
//Implements Hilderman's algorithm for Floyd's search
void FloydShortestPath::search()
{
	for (int k = 1; k <= numOfVertices; k++)
	{
		for (int i = 1; i <= numOfVertices; i++)
		{
			if (i == k || distance[i][k] == HIGH_VALUE)
			{
				continue;
			}else{
				for (int j = 1; j <= numOfVertices; j++)
				{
					if (i == j || j == k || distance[k][j] == HIGH_VALUE)
						continue;
					//Update distance and previous vertext if distance shorter
					if (distance[i][k] + distance[k][j] < distance[i][j])
					{
						distance[i][j] = distance[i][k] + distance[k][j];
						vertex[i][j] = vertex[k][j];
					}
				}
			}
		}
	}
}
//http://www2.cs.uregina.ca/~hilder/cs340/Algorithms/dynprogFloydsInitialization.txt
//Implements Hilderman's algorithm for Floyd's initialization
void FloydShortestPath::initialize(ifstream & input)
{
	//Initialize to defaults
	for (int i = 1; i <= numOfVertices; i++)
	{
		for (int j = 1; j <= numOfVertices; j++)
		{
			distance[i][j] = HIGH_VALUE;
			vertex[i][j] = i;
			if (i == j)
				distance[i][j] = 0;
		}
	}

	int i = 0, j = 0, inputDistance = 0, newNumOfVertices = 0;

	//Reads edges from input stream
	while (input >> i >> j >> inputDistance)
	{
		//Updates High values to shorter distances
		if (inputDistance < distance[i][j])
			distance[i][j] = inputDistance;
		
		//Reduce numOfVertices to the number this input file has.
		if (i > newNumOfVertices)
			newNumOfVertices = i;
		if (j > newNumOfVertices)
			newNumOfVertices = j;
	}

	numOfVertices = newNumOfVertices;
}

//http://www2.cs.uregina.ca/~hilder/cs340/Algorithms/dynprogFloydsPaths.txt
//Implements Hilderman's algorithms for Floyd's paths function
void FloydShortestPath::paths(int startVertex, int goalVertex)
{
	int i = startVertex;
	int j = goalVertex;
	int length = distance[i][j];
	cout << j;
	while(i != vertex[i][j])
	{
		cout << " <- " << vertex[i][j];
		j = vertex[i][j];
	}
	cout << " <- " << i << " (LENGTH = " << length << ")";
	cout << endl << endl;
}

void FloydShortestPath::print()
{
	cout << endl << "Initialized" << endl << endl;
	cout << "Distance Matrix" << endl << endl;
	printMatrix(distance);
	cout << "Vertex Matrix" << endl << endl;
	printMatrix(vertex);
}

void FloydShortestPath::printMatrix(int m[][20])
{
	//Prints nice 2D array
	for (int i = 0; i <= numOfVertices; i++)
	{
		//Print horizontal line under column numbers
		if (i == 1)
		{
			for (int k = 0; k <= numOfVertices; k++)
			{
				cout << "----";
			}
			cout << endl;
		}

		//Print Row Numbers
		if (i == 0)
			cout << setw(2) << internal << " ";
		else
			cout << setw(2) << internal << i;
		cout << "|";

		for (int j = 1; j <= numOfVertices; j++)
		{
			//Print Columns Numbers
			if (i == 0)
				cout << setw(4) << j;
			else
			{
				//Print values
				if (m[i][j] != HIGH_VALUE)
					cout << setw(4) << m[i][j];
				else
					cout << setw(4) << "HV";
			}
		}
		cout << endl;
	}
	cout << endl << endl;
}
