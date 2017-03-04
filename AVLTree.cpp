#include "AVLTree.h"
#include <iostream>
#include <iomanip>
#include <cassert>

AVLTree::AVLTree() :root(0)
{}

AVLTree::~AVLTree()
{
	deleteTree();
}

bool AVLTree::insert(int vertex)
{
	//create root if tree is empty
	if (root == 0)
	{
		root = new SetNode(vertex);
		return true;
	}
	//recursive insert
	return insert(vertex, root);

}

void AVLTree::deleteTree()
{
	if (root)
	{
		//recursive delete
		deleteTree(root);
		delete root;
		root = 0;
	}
}


void AVLTree::printPostOrder() const
{
	if (root == 0)
		std::cout << "AVL Tree is empty.\n\n";
	else
		//recursive print
		postOrder(root, 0);
}


bool AVLTree::insert(int vertex, SetNode * &tree) const
{
	bool inserted = false;

	//If vertex is smaller than current node, insert on left side
	if (vertex < tree->getKey())
	{
		//add to left child if empty
		if (tree->getLeft() == 0)
		{
			tree->setLeft(new SetNode(vertex));
			inserted = true;
		} else
		{
			//try to insert to this nodes left child
			inserted = insert(vertex, tree->getLeftA());
		}

		if (inserted)
		{
			assert(tree->getLeft());

			//Calculate height difference
			//Rotate if left is deeper than right
			if (getHeightDifference(tree->getLeft(), tree->getRight()) == 2)
			{
				if (vertex < tree->getLeft()->getKey())
					llRotation(tree);
				else
					lrRotation(tree);
			}
		}

	} else if (vertex > tree->getKey())
	{
		//add to right child if empty
		if (tree->getRight() == 0)
		{
			tree->setRight(new SetNode(vertex));
			inserted = true;
		} else
		{
			//try to insert to this nodes right child
			inserted = insert(vertex, tree->getRightA());
		}
		if (inserted)
		{
			assert(tree->getRight());
			//Calculate height difference
			//Rotate if right is deeper than left
			if (getHeightDifference(tree->getLeft(), tree->getRight()) == -2)
			{
				if (vertex > tree->getRight()->getKey())
					rrRotation(tree);
				else
					rlRotation(tree);
			}
		}

	} else
	{
		//Duplicate vertex exists in tree
		inserted = false;
	}
	//Recalculate this nodes height
	if (inserted)
		fixHeight(tree);

	return inserted;

}

//Hilderman's standard AVL rotation algorithm
//http://www2.cs.uregina.ca/~hilder/cs210/Algorithms/avlLL.txt
void AVLTree::llRotation(SetNode * &tree)
{
	SetNode *leftSubTree = tree->getLeft();
	tree->setLeft(leftSubTree->getRight());
	leftSubTree->setRight(tree);

	fixHeight(tree);
	fixHeight(leftSubTree);
	tree = leftSubTree;
}

//Hilderman's standard AVL rotation algorithm
//http://www2.cs.uregina.ca/~hilder/cs210/Algorithms/avlRR.txt
void AVLTree::rrRotation(SetNode * &tree)
{
	SetNode *rightSubTree = tree->getRight();
	tree->setRight(rightSubTree->getLeft());
	rightSubTree->setLeft(tree);

	fixHeight(tree);
	fixHeight(rightSubTree);
	tree = rightSubTree;
}

//Hilderman's standard AVL rotation algorithm
//http://www2.cs.uregina.ca/~hilder/cs210/Algorithms/avlLR.txt
void AVLTree::lrRotation(SetNode * &tree)
{
	rrRotation(tree->getLeftA());
	llRotation(tree);
}

//Hilderman's standard AVL rotation algorithm
//http://www2.cs.uregina.ca/~hilder/cs210/Algorithms/avlRL.txt
void AVLTree::rlRotation(SetNode * &tree)
{
	llRotation(tree->getRightA());
	rrRotation(tree);
}



void AVLTree::postOrder(SetNode * tree, int indent)
{
	if (tree)
	{
		//prints right of tree at the top of output
		//farthest right child node printed first
		//and is most indented
		if (tree->getRight())
			postOrder(tree->getRight(), indent + 4);

		if (indent)
			std::cout << std::setw(indent) << ' ';

		//Prints tree lines
		if (tree->getRight()) 
			std::cout << " /\n" << std::setw(indent) << ' ';

		//prints this node
		std::cout << tree->getKey() << "\n ";

		//prints down the left side of the tree
		//farthest left child is printed last
		if (tree->getLeft())
		{
			std::cout << std::setw(indent) << ' ' << " \\\n";
			postOrder(tree->getLeft(), indent + 4);
		}
	}
}

void AVLTree::deleteTree(SetNode * tree)
{
	assert(tree);
	if (tree->getLeft())
	{
		deleteTree(tree->getLeft());
		delete tree->getLeft();
		//Set deleted subtrees back to NULL
		tree->setLeft(0);
	}
	if (tree->getRight())
	{
		deleteTree(tree->getRight());
		delete tree->getRight();
		//Set deleted subtrees back to NULL
		tree->setRight(0);
	}
}

void AVLTree::fixHeight(SetNode* tree)
{
	//Ternary to get height of child nodes if not NULL. NULL has -1 height
	int leftTreeHeight = tree->getLeft() ? tree->getLeft()->getHeight() : -1;
	int rightTreeHeight = tree->getRight() ? tree->getRight()->getHeight() : -1;

	//Get max height of left and right sub trees
	int maxHeight = max(leftTreeHeight, rightTreeHeight);
	//Add 1 to height because current node has 1 more height
	//then it's tallest child
	maxHeight += 1;
	tree->setHeight(maxHeight);
}

int AVLTree::getHeightDifference(SetNode * left, SetNode * right)
{
	//Ternary to get SetNode height, NULL SetNode has -1 height
	int leftHeight = left ? left->getHeight() : -1;
	int rightHeight = right ? right->getHeight() : -1;
	return leftHeight - rightHeight;
}


inline int AVLTree::max(int a, int b)
{
	return (a > b ? a : b);
}