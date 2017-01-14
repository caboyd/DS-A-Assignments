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
	TreeNode<ItemType> *rightTree;
	TreeNode<ItemType> *leftTree;

	//Constructor to initalize TreeNode to 0
		TreeNode() :key(-1), item(0), rightTree(0), leftTree(0){}

	//Constructor to Initialize TreeNode to an ItemType
	TreeNode(int k, const ItemType &nodeDataItem):leftTree(0), righTree(0)
	{
		key = k;
		item = nodeDataItem;
	}

	TreeNode(int k, const ItemType &nodeDataItem, TreeNode<ItemType> *left, TreeNode<ItemType> *right)
	{
		key = k;
		item = nodeDataItem;
		leftTree = left;
		rightTree = right;
	}

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

	//search for item at key
	ItemType retrieve(int key, bool &itemFound);

	//Prints items in a table in order
	void printInorder();

	//Prints items in a tree
	//Far left item is the root
	void printPostorder();

	//Helper fucntions
private:
	ItemType retrieve(int key, bool &itemFound, TreeNode<ItemType> *tree);
	void insert(int key, const ItemType &nodeDataItem, TreeNode<ItemType> *tree);
	TreeNode<ItemType>* remove(int key, TreeNode<ItemType> *tree);
	TreeNode<ItemType>* smallestNode(TreeNode<ItemType> *tree);
	void inorder(TreeNode<ItemType>* tree);
	void postorder(TreeNode<ItemType>* tree, int indent = 0);
};

