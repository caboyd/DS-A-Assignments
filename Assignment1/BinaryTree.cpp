#include "BinaryTree.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cassert>

BinaryTree::BinaryTree():root(0), totalDepth(0)
{};

BinaryTree::~BinaryTree()
{
	deleteTree();
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
		std::cout << "\nRoot node with key " << root->getKey();
		std::cout << " has been deleted.\n\n";
		delete root;
		root = 0;
		printPostOrder();
		std::cout << "This binary Tree has deleted every node.\n\n";
	}
}

void BinaryTree::insert(int key)
{
	if (!root)
	{
		root = new TreeNode(key);
	}
	else
	{
		//recursive insert
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
		std::cout << "Binary Tree is empty.\n\n";
	}
	else
	{
		//recursive print post order
		postOrder(root, 0);
	}
}


//Helper fucntions
void BinaryTree::insert(int key, TreeNode *tree, int depth)
{
	//increment depth because depth increases for every
	//recursive leaf node
	depth++;

	//Randomly choose which side of the tree to place the new node
	if (getRandomBool()) //Left side
	{
		//Add to left child if empty
		if (tree->getLeft() == 0)
		{
			tree->setLeft(new TreeNode(key));
			totalDepth += depth;
		}
		else
		{
			//recursive insert into left tree
			insert(key, tree->getLeft(), depth);
		}
	}
	else //Right side
	{
		//Add to right child if empty
		if (tree->getRight() == 0)
		{
			tree->setRight(new TreeNode(key));
			totalDepth += depth;
		}
		else
		{
			//recursive insert into right tree
			insert(key, tree->getRight(), depth);
		}
	}
}


void BinaryTree::postOrder(TreeNode* tree, int indent = 0) const
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




void BinaryTree::deleteTree(TreeNode* tree)
{
	assert(tree);
	if (tree->getLeft())
	{
		//recursive delete down left subtree
		deleteTree(tree->getLeft());
		delete tree->getLeft();
		tree->setLeft(0);
		//set deleted subtrees back to NULL
	}
	if (tree->getRight())
	{
		//recursive delete down right subtree
		deleteTree(tree->getRight());
		delete tree->getRight();
		//set deleted subtrees back to NULL
		tree->setRight(0);
	}
}

void BinaryTree::verboseDeleteTree(TreeNode* tree)
{
	assert(tree);

	if (tree->getLeft())
	{
		//recursive delete down left subtree
		verboseDeleteTree(tree->getLeft());
		std::cout << "\nNode with key " << tree->getLeft()->getKey();
		std::cout << " has been deleted.\n\n";
		delete tree->getLeft();
		//set deleted subtrees back to NULL
		tree->setLeft(0);
		printPostOrder();
	}
	if (tree->getRight())
	{
		//recursive delete down right subtree
		verboseDeleteTree(tree->getRight());
		std::cout << "\nNode with key " << tree->getRight()->getKey();
		std::cout << " has been deleted.\n\n";
		delete tree->getRight();
		//set deleted subtrees back to NULL
		tree->setRight(0);
		printPostOrder();
	}
}

bool BinaryTree::getRandomBool() const
{
	//Returns true if odd rand and 0 if even rand number
	return rand() & 1;
}