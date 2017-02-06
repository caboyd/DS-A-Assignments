/*	Name: Chris Boyd
Date: Feb 4, 2017
CS340 Winter 2017
Assignment 2 Part 2 - Dijkstra's Algorithm
*/

#include "floydShortestPath.h"
#include <iostream>

using namespace std;

int main()
{

	cout << "Floyd's Algorithm Test using class example" << endl;
	FloydShortestPath a("input.txt");
	a.printAndSearch();

	cout << "Floyd's Algorithm Test using graph.txt" << endl;
	FloydShortestPath b("graph.txt");
	b.printAndSearch();

	return 0;
}


