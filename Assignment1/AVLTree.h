#pragma once
#include "TreeNode.h"

class AVLTree
{
private:
	TreeNode* root;
	int totalDepth;
public:
	//Default Constructor
	AVLTree();

	//Destructor
	~AVLTree();

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
	void llRotation(TreeNode *tree);
	void rrRotation(TreeNode *tree);
	void lrRotation(TreeNode *tree);
	void rlRotation(TreeNode *tree);
	void postOrder(TreeNode* tree, int indent);
	void verboseDeleteTree(TreeNode* tree);
	void deleteTree(TreeNode* tree);
	void fixHeight(TreeNode* tree);
};

