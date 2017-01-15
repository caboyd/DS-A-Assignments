/*		Name: Chris Boyd
Date: Dec 1, 2015

Description: Binary search tree implementation
*/

#include "BinaryTree.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main()
{
	//Seed the rand function
	srand(time(0));

	//Test Showing Binary Tree deleting all nodes properly
	BinaryTree b;
	for (int i = 0; i < 8; i++)
	{
		b.insert(i);
	}
	b.printPostOrder();

	b.verboseDeleteTree();

	cout << "BINARY TREES:\n\n";



	return 0;

}