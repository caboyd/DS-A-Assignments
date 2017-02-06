/*	Name: Chris Boyd
Date: Feb 4, 2017
CS340 Winter 2017
Assignment 2 Part 1 - Topological Sort
 
Description: Generates an adjacency list loaded from edges in an
external text file. Initializes and prints the example done in class
from input.txt.
Initializes, finds start vertex and performs partial order on the 
prerequisites.txt and prints all vertices on the same line that
can be done concurrently.
*/

#include <iostream>
#include <string>
#include "TopologicalSort.h"

using namespace std;

int main()
{
	cout << "Evidence program is working\n\n";
	//Calls constructor that prints after initialize phase
	cout << "In Class Example Initialization" << endl;
	TopologicalSort t1("input.txt",1);
	cout << "In Class Example Partial Order" << endl;
	TopologicalSort t2("input.txt");
	cout << endl;

	cout << "Prerequisites Initialization" << endl;
	TopologicalSort t4("prerequisites.txt",1);
	cout << "Prerequisites Topological Sort Partial Order" << endl;
	//Calls constructor that prints partial Order
	TopologicalSort t3("prerequisites.txt");

	cout << endl;
	return 0;
}


