/*	Name: Chris Boyd
Date: Feb 4,2017
*/

#pragma once
#include <fstream>
#include <string>

static const int HIGH_VALUE = 0x7FFFFFFF;

struct Leader;
struct Follower;



class DijkstraShortestPath
{
private:
	Leader a[20];
	int numOfVertices = 20;

public:

	//Initializes Distance and vertex matrix
	//Reads edges from a file (Ex. 1 2 100). 
	//Calls initialize function to update array
	DijkstraShortestPath(std::string fileName);

	//Prints Leaders and followers
	void print();

	//Updates distances of Leaders given distinguished startVertex
	//Calls findNextVertex to iterate through array
	void search(int startVertex);


private:
	//Initializes Distance and vertex matrices with edges with 
	//distance read from an input stream (Ex. 1 2 100). 
	void initialize(std::ifstream& input);

	//Prints the shortest path for each vertex	
	void paths(int startVertex, int goalVertex);

	//Returns next Leader in array that has known==false
	//and has shortest distance.
	int findNextVertex();
};