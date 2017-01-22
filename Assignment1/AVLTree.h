/*	Name: Chris Boyd
	Date: Jan 19,2017
*/

#pragma once
#include "TreeNode.h"

//AVLTree Data Structure
class AVLTree
{
private:
	TreeNode* root;

	//Total Depth of all nodes in the tree. Value is
	//updated when nodes are inserted
	int totalDepth;

public:
	//Default Constructor
	AVLTree();

	//Destructor
	~AVLTree();

	//Returns total depth of tree nodes
	int getTotalDepth();

	//Insert into tree using key and balace tree
	//Returns false if item not inserted
	bool insert(int key);

	//Delete every node in the tree
	void deleteTree();

	//Delete every node in the tree with output
	void verboseDeleteTree();

	//Prints items in a tree
	//Far left item is the root
	void printPostOrder();



private:
	//Helper fucntions
	//Recurvsive insert into AVL tree, updates tree total depth
	bool insert(int key, TreeNode* &tree, int depth);

	//AVL rotations
	void llRotation(TreeNode *&tree);
	void rrRotation(TreeNode *&tree);
	void lrRotation(TreeNode *&tree);
	void rlRotation(TreeNode *&tree);

	//Recursive print tree in post order
	void postOrder(TreeNode* tree, int indent);

	//recursive delete tree memory
	void verboseDeleteTree(TreeNode* tree);
	void deleteTree(TreeNode* tree);

	//update the nodes height
	void fixHeight(TreeNode* tree);

	//calculate height difference between two sides of tree
	//NULL tree has a height of -1
	int getHeightDifference(TreeNode* left, TreeNode* right);

	//Returns max between to ints
	int max(int a, int b);
};

