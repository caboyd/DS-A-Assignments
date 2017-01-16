#pragma once

//TreeNode class that is used in BinaryTree.h BinarySearchTree.h and AVLTree.h

class TreeNode {
private:
	int key;
	TreeNode* left;
	TreeNode* right;
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
	int getHeight() { return height; }

	TreeNode* getLeft() { return left; }
	TreeNode* getRight() { return right; }
	//Returns Address of pointer which is required for AVL rotations
	TreeNode*& getLeftA() { return left; }
	TreeNode*& getRightA() { return right; }
	
	void setKey(int k) { key = k; }
	void setLeft(TreeNode *left) { this->left = left; }
	void setRight(TreeNode *right) { this->right = right; }
	void setHeight(int height) { this->height = height; }

	//Destructor
	~TreeNode() {}
};