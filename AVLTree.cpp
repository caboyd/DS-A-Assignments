/*	Name: Chris Boyd
Date: March 4,2017
*/
#include "AVLTree.h"
#include <iostream>
#include <iomanip>
#include <cassert>

AVLTree::AVLTree() : root(0)
{
}

AVLTree::~AVLTree()
{
	deleteTree();
}

bool AVLTree::insert(int vertex, int& vertexCount)
{
	//create root if tree is empty
	if (root == 0)
	{
		root = new SetNode(vertex);
		vertexCount++;
		return true;
	}
	//recursive insert
	return insert(vertex, vertexCount, root);
}

SetNode* AVLTree::find(int vertex) const
{
	return find(root, vertex);
}

void AVLTree::unionize(SetNode* vertexTo, SetNode* vertexFrom) const
{
	vertexTo->getSubSet()->size += vertexFrom->getSubSet()->size;
	VertexNode* v = vertexTo->getSubSet()->firstVertex;
	//Append vertexFrom's vertexNodes to vertexTo's last vertexNode
	while(v->next)
		v = v->next;
	v->next = vertexFrom->getSubSet()->firstVertex;
	delete vertexFrom->getSubSet();
	v = v->next;
	//Set all vertexFrom's vertexNode's SetNode's subsets to vertexTo's subset
	while (v)
	{
		vertexFrom = find(v->vertex);
		vertexFrom->setSubSet(vertexTo->getSubSet());
		v = v->next;
	}
}

void AVLTree::makeSet(int vertex) const
{	//Creates the subset Node and vertexNode
	SetNode* v = find(vertex);
	SubSetNode* temp = new SubSetNode{};
	temp->size = 1;
	temp->firstVertex = new VertexNode{};
	temp->firstVertex->vertex = v->getVertex();
	temp->firstVertex->next = 0;
	v->setSubSet(temp);
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


bool AVLTree::insert(int vertex, int& vertexCount, SetNode* & tree) const
{
	bool inserted = false;

	//Insert here
	if(tree == 0)
	{
		tree = new SetNode(vertex);
		vertexCount++;
		inserted = true;
	} else if (vertex < tree->getVertex())
	{
		//try to insert to this nodes left child
		inserted = insert(vertex, vertexCount, tree->getLeftA());
		
		if (inserted)
		{
			assert(tree->getLeft());
			//Calculate height difference
			//Rotate if left is deeper than right
			if (getHeightDifference(tree->getLeft(), tree->getRight()) == 2)
			{
				if (vertex < tree->getLeft()->getVertex())
					llRotation(tree);
				else
					lrRotation(tree);
			}
		}
	} else if (vertex > tree->getVertex())
	{
		//try to insert to this nodes right child
		inserted = insert(vertex, vertexCount, tree->getRightA());

		if (inserted)
		{
			assert(tree->getRight());
			//Calculate height difference
			//Rotate if right is deeper than left
			if (getHeightDifference(tree->getLeft(), tree->getRight()) == -2)
			{
				if (vertex > tree->getRight()->getVertex())
					rrRotation(tree);
				else
					rlRotation(tree);
			}
		}
	}
	else
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
void AVLTree::llRotation(SetNode* & tree)
{
	SetNode* leftSubTree = tree->getLeft();
	tree->setLeft(leftSubTree->getRight());
	leftSubTree->setRight(tree);

	fixHeight(tree);
	fixHeight(leftSubTree);
	tree = leftSubTree;
}

//Hilderman's standard AVL rotation algorithm
//http://www2.cs.uregina.ca/~hilder/cs210/Algorithms/avlRR.txt
void AVLTree::rrRotation(SetNode* & tree)
{
	SetNode* rightSubTree = tree->getRight();
	tree->setRight(rightSubTree->getLeft());
	rightSubTree->setLeft(tree);

	fixHeight(tree);
	fixHeight(rightSubTree);
	tree = rightSubTree;
}

//Hilderman's standard AVL rotation algorithm
//http://www2.cs.uregina.ca/~hilder/cs210/Algorithms/avlLR.txt
void AVLTree::lrRotation(SetNode* & tree)
{
	rrRotation(tree->getLeftA());
	llRotation(tree);
}

//Hilderman's standard AVL rotation algorithm
//http://www2.cs.uregina.ca/~hilder/cs210/Algorithms/avlRL.txt
void AVLTree::rlRotation(SetNode* & tree)
{
	llRotation(tree->getRightA());
	rrRotation(tree);
}

SetNode* AVLTree::find(SetNode* tree, int vertex) const
{
	assert(tree);
	//Vertex is smaller check left sub tree
	if (tree->getVertex() > vertex)
	{
		if (tree->getLeft())
			return find(tree->getLeft(), vertex);
			return 0; //Not Found
	}
	//Vertex is larger check right sub tree
	if (tree->getVertex() < vertex)
	{
		if (tree->getRight())
			return find(tree->getRight(), vertex);
			return 0; //Not Found
	}
	if (tree->getVertex() == vertex)
	{
		//Found Vertex
		return tree;
	}

	//Not Found
	return 0;
}


void AVLTree::postOrder(SetNode* tree, int indent)
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
		std::cout << tree->getVertex();
		//Print this nodes subset
		VertexNode* v = tree->getSubSet()->firstVertex;
		while(v)
		{
			std::cout << "->" << v->vertex;
			v = v->next;
		}
		std::cout << std::endl;


		//prints down the left side of the tree
		//farthest left child is printed last
		if (tree->getLeft())
		{
			std::cout << std::setw(indent) << ' ' << " \\\n";
			postOrder(tree->getLeft(), indent + 4);
		}
	}
}

void AVLTree::deleteTree(SetNode* tree)
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

int AVLTree::getHeightDifference(SetNode* left, SetNode* right)
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
