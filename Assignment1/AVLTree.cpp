#include "AVLTree.h"

AVLTree::AVLTree():root(0),totalDepth(0)
{}

AVLTree::~AVLTree()
{
	deleteTree(root);
}

int AVLTree::getTotalDepth()
{
	return totalDepth;
}

bool AVLTree::insert(int key)
{
	if (root == 0)
	{
		root = new TreeNode(key);
		return true;
	}
	else
	{
		return insert(key, root, 0);
	}
}

void AVLTree::deleteTree()
{}

void AVLTree::verboseDeleteTree()
{}

void AVLTree::printPostOrder()
{}

bool AVLTree::insert(int key, TreeNode * tree, int depth)
{
	depth++;
	bool inserted = false;
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
			inserted = true;
		}
		else
		{
			inserted = insert(key, tree->getLeft(), depth);
		}
		if (inserted)
		{
			//Calculate height difference
			if ((tree->getLeft()->getHeight() 
				- tree->getRight()->getHeight()) == 2)
			{
				if (key < tree->getLeft()->getKey())
				{
					llRotation(tree);
				}
				else
				{
					lrRotation(tree);
				}
			}
		}

	}
	else if (key > tree->getKey())
	{
		//add to right child if empty
		if (tree->getRight() == 0)
		{
			tree->setRight(new TreeNode(key));
			totalDepth += depth;
			inserted = true;
		}
		else
		{
			inserted = insert(key, tree->getRight(), depth);
		}
		if (inserted)
		{
			//Calculate height difference
			if ((tree->getRight()->getHeight()
				- tree->getLeft()->getHeight()) == 2)
			{
				if (key > tree->getLeft()->getKey())
				{
					rrRotation(tree);
				}
				else
				{
					rlRotation(tree);
				}
			}
		}

	}
	else
	{
		//Duplicate key
		inserted = false;
	}
	//Set this nodes height
	if (inserted)
	{
		fixHeight(tree);
	}
	return inserted;

}

void AVLTree::llRotation(TreeNode * tree)
{
	TreeNode *leftSubTree = tree->getLeft();
	tree->setLeft(leftSubTree->getRight());
	leftSubTree->setRight(tree);

	fixHeight(tree);
	fixHeight(leftSubTree);
	tree = leftSubTree;
}

void AVLTree::rrRotation(TreeNode * tree)
{
	TreeNode *rightSubTree = tree->getRight();
	tree->setRight(rightSubTree->getLeft());
	rightSubTree->setLeft(tree);

	fixHeight(tree);
	fixHeight(rightSubTree);
	tree = rightSubTree;
}

void AVLTree::lrRotation(TreeNode * tree)
{
	rrRotation(tree->getLeft());

}

void AVLTree::rlRotation(TreeNode * tree)
{}

void AVLTree::postOrder(TreeNode * tree, int indent)
{}

void AVLTree::verboseDeleteTree(TreeNode * tree)
{}

void AVLTree::deleteTree(TreeNode * tree)
{}

void AVLTree::fixHeight(TreeNode* tree)
{
	int leftTreeHeight = tree->getLeft()->getHeight();
	int rightTreeHeight = tree->getRight()->getHeight();
	int tempMaxHeight = leftTreeHeight >= rightTreeHeight ?
		leftTreeHeight : rightTreeHeight;
	tempMaxHeight += 1;
	tree->setHeight = tempMaxHeight;
}
