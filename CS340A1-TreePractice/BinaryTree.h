/*	Name: Chris Boyd
Date: Jan 19,2017
*/

#pragma once
#include "TreeNode.h"

//Binary Tree Data Structure
class BinaryTree
{
private:
	TreeNode* root;

	//Total Depth of all nodes in the tree. Value is
	//updated when nodes are inserted
	int totalDepth;
public:

	//Constructor to initialize empty Binary Tree
	BinaryTree();
	
	//Destructor to free all allocated node memory
	~BinaryTree();

	//Returns total depth of tree nodes
	int getTotalDepth() const;

	//Insert into tree using key and balace tree
	//Returns false if item not inserted
	void insert(int key);

	//Delete every node in the tree
	void deleteTree();

	//Delete every node in the tree with output
	void verboseDeleteTree();

	//Prints items in a tree
	//Far left item is the root
	void printPostOrder() const;

	//Helper fucntions
private:

	//Recurvsive insert into binary tree, updates tree total depth
	void insert(int key, TreeNode *tree, int depth);

	//Recursive print tree in post order
	void postOrder(TreeNode* tree, int indent) const;

	//recursive delete tree memory
	void verboseDeleteTree(TreeNode* tree);
	void deleteTree(TreeNode* tree);

	//Returns random bool 0 or 1 using rand function
	bool getRandomBool() const;
};