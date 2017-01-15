#pragma once

class TreeNode {
private:
	int key;
	TreeNode* left;
	TreeNode* right;
public:
	//Constructor to initalize TreeNode to 0
	TreeNode() :key(-1), right(0), left(0) {}

	//Constructor to Initialize TreeNode with a key
	TreeNode(int k) :left(0), right(0)
	{
		key = k;
	}

	//Constructor to Initialize Treen with a key and set left and right nodes
	TreeNode(int k, TreeNode *left, TreeNode *right)
	{
		key = k;
		this->left = left;
		this->right = right;
	}

	int getKey()const { return key; }
	TreeNode* getLeft() { return left; }
	TreeNode* getRight() { return right; }

	void setKey(int k) { key = k; }
	void setLeft(TreeNode *left) { this->left = left; }
	void setRight(TreeNode *right) { this->right = right; }

	//Destructor
	~TreeNode() {}
};