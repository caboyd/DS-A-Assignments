/*	Name: Chris Boyd
Date: Feb 4,2017
*/

#pragma once
#include <string>
#include <fstream>

struct Leader;
struct Follower;

class TopologicalSort
{
private:
	Leader* head;
	Leader* tail;
	int vertexCount;
		
public:
	//Default Constructor
	//Calls initialize, findStartVertex, partialOrder
	TopologicalSort(std::string fileName);

	//Calls initialize, print
	TopologicalSort(std::string fileName, bool initOnly);



private:
	//Initializes the topological sort adjacency list using a input stream
	//that contains a series of edges (Ex. 1 2) separated by a new line
	//Calls buildList
	void initialize(std::ifstream& input);

	//Reorders the adjacency list and sets the start vertex head
	//as a leader with inDegree 0
	void findStartVertex();

	//Reorders the adjacency list into a partial order solution
	void partialOrder();

	//Adds an edge and or vertex to the adjacency list
	Leader* buildList(std::string vertex);

	//Prints all the leaders and information about followers
	void print();
};