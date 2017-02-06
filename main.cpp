/*	Name: Chris Boyd
Date: Feb 4, 2017
CS340 Winter 2017
Assignment 2 Part 2 - Dijkstra's Algorithm
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

	cout << "Dijsktra's Algorithm Test using class example" << endl;
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


