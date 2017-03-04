/*	Name: Chris Boyd
	Date: Jan 19,2017
*/

#pragma once
#include "SetNode.h"

//AVLTree Data Structure
class AVLTree
{
private:
	SetNode* root;

	//Total Depth of all nodes in the tree. Value is
	//updated when nodes are inserted
	int totalDepth;

public:
	//Default Constructor to initialize emprty AVL tree
	AVLTree();

	//Destructor to free all allocated node memory
	~AVLTree();

	//Returns total depth of tree nodes
	int getTotalDepth() const;

	//Insert into tree using vertex and balance tree
	//Returns false if item not inserted
	bool insert(int vertex);



	//Delete every node in the tree
	void deleteTree();

	//Delete every node in the tree with output
	void verboseDeleteTree();

	//Prints items in a tree
	//Far left item is the root
	void printPostOrder() const;



private:
	//Helper fucntions
	//Recurvsive insert into AVL tree, updates tree total depth
	bool insert(int vertex, SetNode* &tree, int depth);

	//AVL rotations
	void llRotation(SetNode *&tree);
	void rrRotation(SetNode *&tree);
	void lrRotation(SetNode *&tree);
	void rlRotation(SetNode *&tree);

	//Recursive print tree in post order
	void postOrder(SetNode* tree, int indent) const;

	//recursive delete tree memory
	void verboseDeleteTree(SetNode* tree);
	void deleteTree(SetNode* tree);

	//update the nodes height
	void fixHeight(SetNode* tree);

	//calculate height difference between two sides of tree
	//NULL tree has a height of -1
	int getHeightDifference(SetNode* left, SetNode* right) const;

	//Returns max between to ints
	int max(int a, int b) const;
};

