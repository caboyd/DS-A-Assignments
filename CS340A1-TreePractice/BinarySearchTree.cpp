#pragma once

#include "BinarySearchTree.h"
#include <iostream>
#include <iomanip>
#include <cassert>


BinarySearchTree::BinarySearchTree():root(0),totalDepth(0)
{}


BinarySearchTree::~BinarySearchTree()
{
	deleteTree();
}

void BinarySearchTree::deleteTree()
{
	if (root)
	{
		deleteTree(root);
		delete root;
		root = 0;
	}
}

int BinarySearchTree::getTotalDepth() const
{
	return totalDepth;
}

void BinarySearchTree::verboseDeleteTree()
{
	if (root)
	{
		//recursive delete tree
		verboseDeleteTree(root);
		std::cout << "\nRoot node with key " << root->getKey();
		std::cout << " has been deleted.\n\n";
		delete root;
		root = 0;
		printPostOrder();
		std::cout << "This Binary Search Tree has deleted every node.\n";
	}
}

bool BinarySearchTree::insert(int key)
{
	if (root == 0)
	{
		root = new TreeNode(key);
		return true;
	}
	else
	{
		//recursive insert
		return insert(key, root, 0);
	}

}

//Recursive insert
bool BinarySearchTree::insert(int key, TreeNode *tree, int depth)
{
	//increment depth because depth increases for every
	//recursive leaf node
	depth++;

	//If a Node with this key exists
	if (key == tree->getKey())
	{
		return false;
	}
	//If key is smaller than current node, insert on left side
	else if (key < tree->getKey())
	{
		//add to left child if empty
		if (tree->getLeft() == 0)
		{
			tree->setLeft(new TreeNode(key));
			totalDepth += depth;
			return true;
		}
		else
		{	//try to insert into left subtree
			return insert(key, tree->getLeft(), depth);
		}
	}	
	//If key is larger than current node, insert on right side
	else if (key > tree->getKey())
	{
		//add to right child if empty
		if (tree->getRight() == 0)
		{
			tree->setRight(new TreeNode(key));
			totalDepth += depth;
			return true;
		}
		else
		{	//try to insert into right subtree
			return insert(key, tree->getRight(), depth);
		}
	}

	return false;
}

void BinarySearchTree::printPostOrder() const
{
	if (root == 0)
	{
		std::cout << "Binary Search Tree is empty.\n\n";
	}
	else
	{
		//recursive print post order
		postOrder(root, 0);
	}
}

void BinarySearchTree::postOrder(TreeNode *tree, int indent = 0) const
{
	if (tree)
	{
		if (tree->getRight())
		{
			//prints right of tree at the top of output
			//farthest right child node printed first
			//and farthest indented
			postOrder(tree->getRight(), indent + 4);
		}
		if (indent)
		{
			std::cout << std::setw(indent) << ' ';
		}
		if (tree->getRight()) std::cout << " /\n" << std::setw(indent) << ' ';
		//prints this node
		std::cout << tree->getKey() << "\n ";
		if (tree->getLeft())
		{
			//prints down the left side of the tree
			//farthest left child is printed last
			std::cout << std::setw(indent) << ' ' << " \\\n";
			postOrder(tree->getLeft(), indent + 4);
		}
	}
}

void BinarySearchTree::deleteTree(TreeNode* tree)
{
	assert(tree);
	if (tree->getLeft())
	{
		//recursive delete left side of tree
		deleteTree(tree->getLeft());
		delete tree->getLeft();
		tree->setLeft(0);
	}
	if (tree->getRight())
	{
		//recursive delete right side of tree
		deleteTree(tree->getRight());
		delete tree->getRight();
		tree->setRight(0);
	}
}

void BinarySearchTree::verboseDeleteTree(TreeNode* tree)
{
	assert(tree);
	if (tree->getLeft())
	{
		//recursive delete left side of tree
		verboseDeleteTree(tree->getLeft());
		std::cout << "\nNode with key " << tree->getLeft()->getKey();
		std::cout << " has been deleted.\n\n";
		delete tree->getLeft();
		tree->setLeft(0);
		printPostOrder();
	}
	if (tree->getRight())
	{
		//recursive delete right side of tree
		verboseDeleteTree(tree->getRight());
		std::cout << "\nNode with key " << tree->getRight()->getKey();
		std::cout << " has been deleted.\n\n";
		delete tree->getRight();
		tree->setRight(0);
		printPostOrder();
	}
}