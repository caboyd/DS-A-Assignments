/*	Name: Chris Boyd
	Date: Marcg 4,2017
*/

#pragma once
#include "SetNode.cpp"

//AVLTree Data Structure
class AVLTree
{
private:
	SetNode* root;

public:
	//Default Constructor to initialize emprty AVL tree
	AVLTree();

	//Destructor to free all allocated node memory
	~AVLTree();

	//Insert into tree using vertex and balance tree
	//Returns false if item not inserted
	bool insert(int vertex, int& vertexCount);

	//Returns SetNode that contains vertex value.
	//Returns 0 if not found.
	SetNode* find(int vertex) const;
	
	//Combines the VertexNodes of two vertexes into the larger
	//  of the vertexes. Updates the SubSetNode sizes of each.
	void unionize(SetNode* vertexTo, SetNode* vertexFrom) const;

	void makeSet(int vertex) const;

	//Delete every node in the tree
	void deleteTree();

	//Print the AVL tree
	void printPostOrder() const;
private:
	//Helper fucntions
	//Recurvsive insert into AVL tree, updates tree total depth
	bool insert(int vertex, int& vertexCount,SetNode* &tree) const;



	//AVL rotations
	static void llRotation(SetNode *&tree);
	static void rrRotation(SetNode *&tree);
	static void lrRotation(SetNode *&tree);
	static void rlRotation(SetNode *&tree);

	//recursive find node
	SetNode* find(SetNode* tree, int vertex) const;

	static void postOrder(SetNode * tree, int indent);

	//recursive delete tree memory
	static void deleteTree(SetNode* tree);

	//update the nodes height
	static void fixHeight(SetNode* tree);

	//calculate height difference between two sides of tree
	//NULL tree has a height of -1
	static int getHeightDifference(SetNode* left, SetNode* right);

	//Returns max between to ints
	static int max(int a, int b) ;
};

