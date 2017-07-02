/*	Name: Chris Boyd
Date: Feb 4, 2017
CS340 Winter 2017
Assignment 2 Part 2 - Dijkstra's and Floyd's Shortest Path

This program contains the evidence that the algorithms
are working properly. Tests Dijkstra's Shortest Path algorithm
for every vertex as the start vertext. Tests Floyd's Shortest 
Path algorithm..
*/

#include "floydShortestPath.h"
#include "dijkstraShortestPath.h"
#include <iostream>

using namespace std;

int main()
{
	cout << "Dijsktra's Algorithm Test using class example" << endl;
	DijkstraShortestPath d("input.txt");
	d.print();
	d.searchAllAndPrint();

	cout << "Dijsktra's Algorithm Test using graph.txt" << endl;
	DijkstraShortestPath e("graph.txt");
	e.print();
	e.searchAllAndPrint();

	cout << "Floyd's Algorithm Test using class example" << endl;
	FloydShortestPath a("input.txt");
	a.searchAndPrint();

	cout << "Floyd's Algorithm Test using graph.txt" << endl;
	FloydShortestPath b("graph.txt");
	b.searchAndPrint();

	return 0;
}


