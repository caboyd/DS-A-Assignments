#pragma once
#include "TreeNode.h"

class BinarySearchTree
{
private:
	TreeNode* root;
	int totalDepth;
public:
	//Default Constructor
	BinarySearchTree();

	//Destructor
	~BinarySearchTree();

	//Returns total depth of tree nodes
	int getTotalDepth();

	//Insert into tree using key
	//Returns false if item not inserted
	bool insert(int key);

	//Delete every node in the tree
	void deleteTree();

	//Delete every node in the tree with output
	void verboseDeleteTree();
	//Prints items in a tree
	//Far left item is the root
	void printPostOrder();


	//Helper fucntions
private:
	bool insert(int key, TreeNode* tree, int depth);
	void postOrder(TreeNode* tree, int indent);
	void verboseDeleteTree(TreeNode* tree);
	void deleteTree(TreeNode* tree);
};

