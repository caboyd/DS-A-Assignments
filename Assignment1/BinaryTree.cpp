#include "BinaryTree.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>

class NoTreeExcpetion {};

BinaryTree::~BinaryTree()
{
	if (root)
	{
		deleteTree(root);
		delete root;
		root = 0;
	}
}

void BinaryTree::deleteTree()
{
	if (root)
	{
		deleteTree(root);
		delete root;
		root = 0;
	}
}

void BinaryTree::verboseDeleteTree()
{
	if (root)
	{
		verboseDeleteTree(root);
		std::cout << "\nRoot node with key " << root->getKey() << " has been deleted.\n\n";
		delete root;
		root = 0;
		printPostOrder();
		std::cout << "This binary Tree has deleted every node.\n";
	}
}

bool BinaryTree::isMember(int key) const
{
	return isMember(key, root);
}

void BinaryTree::insert(int key)
{
	if (!root)
	{
		root = new TreeNode(key);
	}
	else
	{
		insert(key, root, 0);
	}

}

int BinaryTree::getTotalDepth() const
{
	return totalDepth;
}

void BinaryTree::printPostOrder() const
{
	if (root == 0)
	{
		std::cout << "Binary Search Tree is empty.\n\n";
	}
	else
	{
		postorder(root, 0);
	}
}


//Helper fucntions

bool BinaryTree::isMember(int key, TreeNode *tree) const
{
	bool exists = false;
	if (tree->getKey() == key)
	{
		return true;
	}
	else if (tree->getLeft())
	{
		if (isMember(key, tree->getLeft()))
		{
			exists = true;
		}

	}
	else if (tree->getRight())
	{
		if (isMember(key, tree->getRight()))
		{
			exists = true;
		}
	}
	return exists;
}

void BinaryTree::insert(int key, TreeNode *tree, int depth)
{
	depth++;
	if (!tree)
	{
		throw NoTreeExcpetion();
	}
	if (getRandomBool())
	{
		if (tree->getLeft())
		{
			insert(key, tree->getLeft(),depth);
		}
		else
		{
			tree->setLeft(new TreeNode(key));
			totalDepth += depth;
		}
	}
	else
	{
		if (tree->getRight())
		{
			insert(key, tree->getRight(), depth);
		}
		else
		{
			tree->setRight(new TreeNode(key));
			totalDepth += depth;
		}
	}
}


void BinaryTree::postorder(TreeNode* tree, int indent = 0) const
{
	if (tree)
	{
		if (tree->getRight())
		{
			postorder(tree->getRight(), indent + 4);
		}
		if (indent)
		{
			std::cout << std::setw(indent) << ' ';
		}
		if (tree->getRight()) std::cout << " /\n" << std::setw(indent) << ' ';
		std::cout << tree->getKey() << "\n ";
		if (tree->getLeft())
		{
			std::cout << std::setw(indent) << ' ' << " \\\n";
			postorder(tree->getLeft(), indent + 4);
		}
	}
}


bool BinaryTree::getRandomBool() const
{
	return rand() & 1;
}

void BinaryTree::deleteTree(TreeNode* tree)
{
	if (!tree)
	{
		throw NoTreeExcpetion();
	}
	if (tree->getLeft())
	{
		deleteTree(tree->getLeft());
		delete tree->getLeft();
		tree->setLeft(0);
	}
	if (tree->getRight())
	{
		deleteTree(tree->getRight());
		delete tree->getRight();
		tree->setRight(0);
	}
}

void BinaryTree::verboseDeleteTree(TreeNode* tree)
{
	if (!tree)
	{
		throw NoTreeExcpetion();
	}
	if (tree->getLeft())
	{
		verboseDeleteTree(tree->getLeft());
		std::cout << "\nNode with key " << tree->getLeft()->getKey() << " has been deleted.\n\n";
		delete tree->getLeft();
		tree->setLeft(0);
		printPostOrder();
	}
	if (tree->getRight())
	{
		verboseDeleteTree(tree->getRight());
		std::cout << "\nNode with key " << tree->getRight()->getKey() << " has been deleted.\n\n";
		delete tree->getRight();
		tree->setRight(0);
		printPostOrder();
	}
}