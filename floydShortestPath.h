/*	Name: Chris Boyd
Date: Feb 4,2017
*/

#pragma once
#include <fstream>
#include <string>

class FloydShortestPath
{
private:

	//Distance Matrix from vertex i to j
	int distance[20][20];
	//Matrix of predecessor to the vertex j in the path from i to j
	int vertex[20][20];
	int numOfVertices = 20;

public:
	
	//Initializes Distance and vertex matrix
	//Reads edges from a file (Ex. 1 2 100). 
	//Calls initialize function to update matrices
	FloydShortestPath(std::string fileName);
	
	//Calls print function to print initialized matrices.
	//Updates distance and vertex arrays with shortest paths.
	//Calls paths function to print all paths.
	void searchAndPrint();


	//******************************************
	//This function is used for algorithm timing
	//******************************************
	//Updates distance and vertex matrices with shortest paths.
	void search();


private:
	//Initializes Distance and vertex matrices with edges with 
	//distance read from an input stream (Ex. 1 2 100). 
	void initialize(std::ifstream& input);
	
	//Prints the shortest path for each vertex	
	void paths(int startVertex, int goalVertex);

	//prints distance and vertex matrices
	void print();

	void printMatrix(int m[][20]);
};