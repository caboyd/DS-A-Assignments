/*	Name: Chris Boyd
	Date: Jan 19,2017
	CS340 Winter 2017 
	Assignment 1

	Description: Calculates the average depth of a Binary Tree,
	Binary Search Tree, and AVL Tree using multiple predefined test cases.
	Uses custom implementations of the Data structures created by me. Values
	are placed randomly in the trees for the tests.
*/

#include "BinaryTree.h"
#include "BinarySearchTree.h"
#include "AVLTree.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;


/*	Creates a Binary Tree with 8 nodes. Then deletes one node and outputs the
*	tree each time until the whole tree is deleted.
*/
void testBinaryTree();


/*	Creates a Binary Search Tree with 8 nodes. Uses rand function to insert a
*	node with a random key value.Then deletes one node and outputs the tree
*	each time until the whole tree is deleted.
*/
void testBinarySearchTree();


/*	Creates an AVL Tree with 10 nodes. Uses rand function to insert a node
*	with a random key value. Then deletes one node and outputs the tree
*	each time until the whole tree is deleted.
*/
void testAVLTree();


/*	Generates binary trees with treeCount number of trees and
*	with nodeCount number of nodes. Calculates the sum of the trees total
*	depth and average depth. Outputs necessary display information with
*	printRunPreInfo, printDots, printRunPostInfo functions.
*	log2ofNodeCount is a value printed out in printRunPostInfo
*/
void runBinaryTree(int nodeCount, int treeCount,
	int printFrequency, int log2OfNodeCount);


/*	Generates Binary Search Trees with treeCount number of trees and
*	with nodeCount number of nodes. Calculates the sum of the trees total
*	depth and average depth. Outputs necessary display information with
*	printRunPreInfo, printDots, printRunPostInfo functions.
*	log2ofNodeCount is a value printed out in printRunPostInfo
*/
void runBinarySearchTree(int nodeCount, int treeCount,
	int printFrequency, int log2OfNodeCount);


/*	Generates AVL Search Trees with treeCount number of trees and
*	with nodeCount number of nodes. Calculates the sum of the trees total
*	depth and average depth. Outputs necessary display information with
*	printRunPreInfo, printDots, printRunPostInfo functions.
*	log2ofNodeCount is a value printed out in printRunPostInfo
*/
void runAVLTree(int nodeCount, int treeCount,
	int printFrequency, int log2OfNodeCount);

/*	Outputs information regarding the current run of the tree run tests.
*	Numbers of nodes per tree, number of trees, and number of tress per dot.
*/
void printRunPreInfo(int nodeCount, int treeCount, int printFrequency);

/*	Prints a dot based on current Tree and print frequency
*/
void printDots(int currentTreeCount,  int printFrequency);

/*	Outputs information regarding the current run of the tree run tests.
*	Total accumulated depth, total number of nodes, average calculated depth,
*	and the log2 of the nodes per tree.
*/
void printRunPostInfo(int totalDepth, int nodeCount, 
	int totalNodes, float averageDepth, int log2OfNodeCount);

int main()
{
	//Seed the rand function
	srand(time(0));

	testBinaryTree();
	testBinarySearchTree();
	testAVLTree();

	cout << "BINARY TREES:\n\n";
	runBinaryTree(8, 16, 1, 3);
	runBinaryTree(64, 128, 4, 6);
	runBinaryTree(512, 1024, 16, 9);
	runBinaryTree(4096, 8192, 64, 12);
	cout << endl;
	cout << "BINARY SEARCH TREES:\n\n";
	runBinarySearchTree(8, 16, 1, 3);
	runBinarySearchTree(64, 128, 4, 6);
	runBinarySearchTree(512, 1024, 16, 9);
	runBinarySearchTree(4096, 8192, 64, 12);
	cout << endl;
	cout << "AVL TREES:\n\n";
	runAVLTree(8, 16, 1, 3);
	runAVLTree(64, 128, 4, 6);
	runAVLTree(512, 1024, 16, 9);
	runAVLTree(4096, 8192, 64, 12);
	return 0;

}

void testBinaryTree()
{

	//Test Showing Binary Tree deleting all nodes properly
	{
		cout << "Test Binary Tree:\n\n";
		BinaryTree *b = new BinaryTree;
		for (int i = 0; i < 8; i++)
		{
			//inserts node which is placed randomly in tree
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
		for (int i = 0; i < 8; i++)
		{
			bool inserted = false;
			//Tries to inserts until succesful
			while (inserted == false)
			{
				//inserts a node with a random key
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
	AVLTree *avlTree = new AVLTree;
	for (int i = 0; i < 10; i++)
	{
		bool inserted = false;
		//Tries to inserts until succesful
		while (inserted == false)
		{
			//inserts a node with a random key
			inserted = avlTree->insert(rand());
		}
	}
	avlTree->printPostOrder();
	cout << "\nTotal depth is " << avlTree->getTotalDepth() << "\n\n";
	cout << "Deleting AVL Tree:";
	avlTree->verboseDeleteTree();
	delete avlTree;
}


void runBinaryTree(int nodeCount, int treeCount, int printFrequency,
	int log2OfNodeCount)
{
	int totalDepth = 0;
	int totalNodes = nodeCount * treeCount;
	float averageDepth;

	printRunPreInfo(nodeCount, treeCount, printFrequency);

	for (int i = 0; i < treeCount; i++)
	{
		BinaryTree *b = new BinaryTree;
		for (int j = 0; j < nodeCount; j++)
		{
			//inserts node which is placed randomly in tree
			b->insert(0);
		}

		totalDepth += b->getTotalDepth();
		b->deleteTree();
		delete b;
		printDots(i, printFrequency);
	}

	cout << endl;
	averageDepth = (float)totalDepth / (float)totalNodes;
	printRunPostInfo(totalDepth, nodeCount, totalNodes, averageDepth,
		log2OfNodeCount);

}

void runBinarySearchTree(int nodeCount, int treeCount, int printFrequency,
	int log2OfNodeCount)
{
	int totalDepth = 0;
	int totalNodes = nodeCount * treeCount;
	float averageDepth;

	printRunPreInfo(nodeCount, treeCount, printFrequency);
	for (int i = 0; i < treeCount; i++)
	{
		BinarySearchTree *b = new BinarySearchTree;
		for (int j = 0; j < nodeCount; j++)
		{
			bool inserted = false;
			//Tries to inserts until succesful
			while (inserted == false)
			{
				//inserts a node with a random key
				inserted = b->insert(rand());
			}
		}
		totalDepth += b->getTotalDepth();
		b->deleteTree();
		delete b;
		printDots(i, printFrequency);

	}
	cout << endl;
	averageDepth = (float)totalDepth / (float)totalNodes;
	printRunPostInfo(totalDepth, nodeCount, totalNodes, averageDepth,
		log2OfNodeCount);

}


void runAVLTree(int nodeCount, int treeCount, int printFrequency,
	int log2OfNodeCount)
{
	int totalDepth = 0;
	int totalNodes = nodeCount * treeCount;
	float averageDepth;

	printRunPreInfo(nodeCount, treeCount, printFrequency);
	for (int i = 0; i < treeCount; i++)
	{
		AVLTree *avlTree = new AVLTree;
		for (int j = 0; j < nodeCount; j++)
		{
			//Tries to inserts a random number until succesful
			bool inserted = false;
			while (inserted == false)
			{
				//inserts a node with a random key
				inserted = avlTree->insert(rand());
			}
		}
		totalDepth += avlTree->getTotalDepth();
		avlTree->deleteTree();
		delete avlTree;
		printDots(i, printFrequency);

	}
	cout << endl;
	averageDepth = (float)totalDepth / (float)totalNodes;
	printRunPostInfo(totalDepth, nodeCount, totalNodes, averageDepth,
		log2OfNodeCount);

}


void printRunPreInfo(int nodeCount, int treeCount, int printFrequency)
{
	cout << "Enter number of nodes: " << nodeCount << endl;
	cout << "Enter number of trees: " << treeCount << endl;
	cout << "Print progress frequency: " << printFrequency << endl;
}

void printDots(int currentTreeCount, int printFrequency)
{
	//output new line after 16 dots have been printed
	if (currentTreeCount > 0 && (currentTreeCount / printFrequency) % 16 == 0 
		&& currentTreeCount % printFrequency == 0)
	{
		cout << endl;
	}
	if (currentTreeCount % printFrequency == 0)
	{
		cout << ".";
	}
}


void printRunPostInfo(int totalDepth, int nodeCount, int totalNodes,
	float averageDepth, int log2OfNodeCount)
{
	cout << "Total depth accumulator: " << totalDepth << endl;
	cout << "Total number of nodes: " << totalNodes << endl;
	cout << "Average depth: " << averageDepth << endl;
	cout << "Log " << nodeCount << ": " << log2OfNodeCount << endl << endl;
}
