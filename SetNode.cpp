/*	Name: Chris Boyd
	Date: Jan March 4,2017
*/

#pragma once

/*	SetNode Data Structure that can be used with AVL Trees for Kruskalls MST
	This file contains Definition and Implementation
	SetNode memory must be managed and child nodes must be deleted properly
	by the programmer
*/

struct VertexNode;
struct VertexNode
{
	int vertex;
	VertexNode* next;
};

struct SubSetNode
{
	int size;
	VertexNode* firstVertex;
};


class SetNode 
{
private:
	int vertex;
	SetNode* left;
	SetNode* right;
	SubSetNode* subset;
	int height;

public:

	//Constructor to initalize SetNode to 0
	SetNode() :vertex(-1), left(0),  right(0), subset(0), height(0) {}

	//Constructor to Initialize SetNode with a vertex
	explicit SetNode(int v) :vertex(v),left(0), right(0), subset(0), height(0) {}

		//Constructor to Initialize SetNode with a vertex and set left and right nodes
	SetNode(int k, SetNode *left, SetNode *right): subset(0), height(0)
	{
		vertex = k;
		this->left = left;
		this->right = right;
	}

	//Getters and Setters
	int getKey()const { return vertex; }
	void setKey(int k) { vertex = k; }

	int getHeight()const { return height; }
	void setHeight(int height) { this->height = height; }

	SetNode* getLeft()const { return left; }
	SetNode* getRight()const { return right; }

	//Returns Address of pointer which is required for AVL rotations
	SetNode*& getLeftA() { return left; }
	SetNode*& getRightA() { return right; }

	void setLeft(SetNode *left) { this->left = left; }
	void setRight(SetNode *right) { this->right = right; }

	//Creates the subset Node and vertexNode
	void makeSet()
	{
		subset = new SubSetNode;
		subset->size = 1;
		subset->firstVertex = new VertexNode;
		subset->firstVertex->vertex = vertex;
		subset->firstVertex->next = 0;
	};

	//Destructor will delete linked list, but not sub trees.
	//AVL tree class must delete sub trees.
	~SetNode()
	{
		SubSetNode* s = subset;
		VertexNode* v = subset->firstVertex;
		while(v)
		{
			VertexNode* next = v->next;
			delete(v);
			v = next;
		}
		v = 0;
		delete subset;
		subset = 0;
	}
};