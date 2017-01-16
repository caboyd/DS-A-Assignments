/*		Name: Chris Boyd
Date: Dec 1, 2015

Description: Binary search tree implementation
*/

#include "BinaryTree.h"
#include "BinarySearchTree.h"
#include "AVLTree.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;


void testBinaryTree();
void testBinarySearchTree();
void testAVLTree();

int main()
{
	//Seed the rand function
	srand(time(0));

	testBinaryTree();
	testBinarySearchTree();
	testAVLTree();

	

	
	
	return 0;

}

void testBinaryTree()
{

	//Test Showing Binary Tree deleting all nodes properly
	{
		cout << "Test Binary Tree:\n\n";
		BinaryTree *b = new BinaryTree;
		for (int i = 0; i < 6; i++)
		{
			b->insert(i);
		}
		b->printPostOrder();
		cout << "\nTotal depth is " << b->getTotalDepth() << "\n\n";
		cout << "Deleting Binary Tree:";
		b->verboseDeleteTree();
		delete b;
	}

}
void testBinarySearchTree()
{
	//Test Showing Binary Search Tree deleting all nodes properly
	{
		cout << "Test Binary Search Tree:\n\n";
		BinarySearchTree *b = new BinarySearchTree;
		for (int i = 0; i < 6; i++)
		{
			bool inserted = false;
			while (inserted == false)
			{
				inserted = b->insert(rand());
			}
		}
		b->printPostOrder();
		cout << "\nTotal depth is " << b->getTotalDepth() << "\n\n";
		cout << "Deleting Search Binary Tree:";
		b->verboseDeleteTree();
		delete b;
	}
}
void testAVLTree()
{
	//Test Showing Binary Search Tree deleting all nodes properly

	cout << "Test AVL Tree:\n\n";
	AVLTree *b = new AVLTree;
	for (int i = 0; i < 10; i++)
	{
		bool inserted = false;
		while (inserted == false)
		{
			inserted = b->insert(rand());
		}
	}
	b->printPostOrder();
	cout << "\nTotal depth is " << b->getTotalDepth() << "\n\n";
	cout << "Deleting AVL Tree:";
	b->verboseDeleteTree();
	delete b;
}