/*
 * Templated BST Data Structure 
 * Author: Christopher Boyd
 * Created: December 1, 2015
 * Updated: March 5, 2017
 * Course: CS 210
 */

#pragma once
template <typename ItemType>       // Forward declaration of the BinarySearchTree class
class BinarySearchTree;

//Exception class thrown when inserting item with duplicate key
class DuplicateException{};

//Class treeNode is a friend class to BinarySearchTree
//BinarySearchTree uses TreeNode for each TreeNode
template <typename ItemType>
class TreeNode
{
private:
	int key;
	ItemType item;
	TreeNode<ItemType> *leftTree;
	TreeNode<ItemType> *rightTree;

	//Constructor to initalize TreeNode to 0
	TreeNode();

	//Constructor to Initialize TreeNode to an ItemType
	TreeNode(int k, const ItemType& nodeDataItem);
	TreeNode(int k, const ItemType& nodeDataItem, TreeNode<ItemType>* left, TreeNode<ItemType>* right);

	int getKey()const{return key;}
	ItemType getItem()const{return item;}
	TreeNode<ItemType>* getLeft(){return leftTree;}
	TreeNode<ItemType>* getRight(){return rightTree;}

	void setKey(int k){key = k;}
	void setItem(const ItemType &nodeDataItem){item = nodeDataItem;}
	void setLeft(TreeNode<ItemType> *left){leftTree = left;}
	void setRight(TreeNode<ItemType> *right){rightTree = right;}

	//Destructor
	~TreeNode(){}

	//Give BinarySearchTree access to TreeNode's private members
	friend class BinarySearchTree<ItemType>;
};

template <typename ItemType>
class BinarySearchTree
{
private:
	TreeNode<ItemType> *root;
public:
	//Default Constructor
	BinarySearchTree();

	//Insert into tree using key
	void insert(int key,const ItemType &nodeDataItem);

	//Remove item at key if found
	void remove(int key);

	//Return and remove smallest ItemType
	ItemType pop();
	
	//search for item at key
	ItemType retrieve(int key, bool &itemFound);

	//Updates ItemType in a node
	void update(int key, bool &itemFound, const ItemType &nodeDataItem);

	//Prints items in a table in order
	void printInorder();

	//Prints items in a tree
	//Far left item is the root
	void printPostorder();


	//Helper fucntions
private:
	ItemType retrieve(int key, bool &itemFound, TreeNode<ItemType> *tree);
	void insert(int key, const ItemType &nodeDataItem, TreeNode<ItemType> *tree);
	TreeNode<ItemType>* smallestNode(TreeNode<ItemType> *tree);
	TreeNode<ItemType>* remove(int key, TreeNode<ItemType> *tree);
	void inorder(TreeNode<ItemType>* tree);
	void postorder(TreeNode<ItemType>* tree, int indent = 0);
	TreeNode<ItemType>* getNode(int key, TreeNode<ItemType> *tree);
};



