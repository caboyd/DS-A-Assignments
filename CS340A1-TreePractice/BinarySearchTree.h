#pragma once
#include "TreeNode.h"

//Binary Search Tree Data Structure

class BinarySearchTree
{
private:
	TreeNode* root;

	//Total Depth of all nodes in the tree. Value is
	//updated when nodes are inserted
	int totalDepth;
public:
	//Default Constructor
	BinarySearchTree();

	//Destructor
	~BinarySearchTree();

	//Returns total depth of tree nodes
	int getTotalDepth() const;

	//Insert into tree using key
	//Returns false if item not inserted
	bool insert(int key);

	//Delete every node in the tree
	void deleteTree();

	//Delete every node in the tree with output
	void verboseDeleteTree();
	//Prints items in a tree
	//Far left item is the root
	void printPostOrder() const;

private:
	//Helper fucntions
	//recursive insert into tree, updates tree total depth
	bool insert(int key, TreeNode* tree, int depth);

	//Recursive print tree in post order
	void postOrder(TreeNode* tree, int indent) const;

	//recursive delete tree memory
	void verboseDeleteTree(TreeNode* tree);
	void deleteTree(TreeNode* tree);
};

