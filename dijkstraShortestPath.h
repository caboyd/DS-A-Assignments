/*	Name: Chris Boyd
Date: Feb 4,2017
*/

#pragma once
#include <fstream>
#include <string>


struct Follower;
struct Follower
{
	int vertex;
	int distance;
	Follower* nextFollower;
};

struct Leader
{
	int vertex;
	bool known;
	int distance;
	Follower* firstFollower;
};

class DijkstraShortestPath
{
private:
	Leader a[20];
	//Will hold number of vertices after reading file
	int numOfVertices;

public:

	//Initializes Distance and vertex matrix
	//Reads edges from a file (Ex. 1 2 100). 
	//Calls initialize function to update array
	DijkstraShortestPath(std::string fileName);

	//Destructor
	//Clean up all followers
	~DijkstraShortestPath();

	//Prints Leaders and followers
	void print();

	//******************************************
	//This function is used for algorithm timing
	//******************************************
	//Call search for each vertex in the array.
	//Calls resetLeaderValues before each search
	void searchAll();

	//Call search for each vertex in the array.
	//Prints paths after every search
	void searchAllAndPrint();

private:
	//Initializes Distance and vertex matrices with edges with 
	//distance read from an input stream (Ex. 1 2 100). 
	void initialize(std::ifstream& input);

	//Updates distances of Leaders given distinguished startVertex
	//Calls findNextVertex to iterate through array
	void search(int startVertex);

	//Prints the shortest path from one vertex to all the others
	void paths();

	//Returns next Leader in array that has known==false
	//and has shortest distance.
	int findNextVertex();

	//Resets the Leader values so searches can be run again.
	void resetLeaderValues();
};