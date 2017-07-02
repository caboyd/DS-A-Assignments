/*	Name: Chris Boyd
	Date: Jan 19,2017
*/

#pragma once

/*	TreeNode Data Structure that can be used with AVL Trees and Binary Trees
	This file contains Definition and Implementation
	TreeNode memory must be managed and child nodes must be deleted properly
	by the programmer
*/
class TreeNode {
private:
	int key;
	TreeNode* left;
	TreeNode* right;

	//Height is used for AVL Trees
	int height;

public:

	//Constructor to initalize TreeNode to 0
	TreeNode() :key(-1), right(0), left(0), height(0) {}

	//Constructor to Initialize TreeNode with a key
	TreeNode(int k) :left(0), right(0), height (0)
	{
		key = k;
	}

	//Constructor to Initialize Treen with a key and set left and right nodes
	TreeNode(int k, TreeNode *left, TreeNode *right): height (0)
	{
		key = k;
		this->left = left;
		this->right = right;
	}

	//Getters and Setters
	int getKey()const { return key; }
	void setKey(int k) { key = k; }

	int getHeight() { return height; }
	void setHeight(int height) { this->height = height; }

	TreeNode* getLeft() { return left; }
	TreeNode* getRight() { return right; }
	//Returns Address of pointer which is required for AVL rotations
	TreeNode*& getLeftA() { return left; }
	TreeNode*& getRightA() { return right; }

	void setLeft(TreeNode *left) { this->left = left; }
	void setRight(TreeNode *right) { this->right = right; }


	//Destructor
	~TreeNode() {}
};