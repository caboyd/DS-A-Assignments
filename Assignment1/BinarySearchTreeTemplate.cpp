#pragma once

#include "BinarySearchTree.h"
#include <iostream>
#include <iomanip>
using namespace std;

template <typename ItemType>
TreeNode<ItemType>* BinarySearchTree<ItemType>::smallestNode(TreeNode<ItemType> *tree);

template <typename ItemType>
BinarySearchTree<ItemType>::BinarySearchTree()
{
	root = 0;
}

template <typename ItemType>
void BinarySearchTree<ItemType>::insert(int key,const ItemType &nodeDataItem)
{
	if(root == 0)
		root = new TreeNode<ItemType>(key, nodeDataItem, 0, 0);
	else
		insert(key, nodeDataItem, root);
}

//Recursive insert
template <typename ItemType>
void BinarySearchTree<ItemType>::insert(int key,const ItemType &nodeDataItem, TreeNode<ItemType> *tree)
{
	if(key == tree->getKey())
	{
		throw DuplicateException();
	}
	if(key < tree->getKey())
	{
		//add to left child if empty
		if(tree->getLeft()== 0)
		{
			TreeNode<ItemType> *tempTree = new TreeNode<ItemType>(key, nodeDataItem, 0, 0);
			tree->setLeft(tempTree);
		} else
		{//insert into left subtree
			insert(key, nodeDataItem, tree->getLeft());
		}
	}
	if(key > tree->getKey())
	{
		//add to right child if empty
		if(tree->getRight() == 0)
		{
			TreeNode<ItemType> *tempTree = new TreeNode<ItemType>(key, nodeDataItem, 0, 0);
			tree->setRight(tempTree);
		} else
		{//insert into right subtree
			insert(key, nodeDataItem, tree->getRight());
		}
	}
}

template <typename ItemType>
void BinarySearchTree<ItemType>::remove(int key)
{
	root = remove(key, root);
}

//Recursive remove
template <typename ItemType>
TreeNode<ItemType>* BinarySearchTree<ItemType>::remove(int key, TreeNode<ItemType> *tree)
{
	if(tree == 0)
	{
		return 0;
	}

	//treeNode that should be deleted
	if(key == tree->getKey())
	{
		//if treeNode has no children we can delete it
		if(tree->getLeft() == 0 && tree->getRight() == 0)
		{
			delete tree;
			return 0;
		}
		//if treeNode has right child save it then delete tree
		if(tree->getLeft() == 0)
		{
			TreeNode<ItemType> *tempTree = tree->getRight();
			delete tree;
			return tempTree;
		}
		//if treeNode has left child save it then delete tree
		if(tree->getRight() == 0)
		{
			TreeNode<ItemType> *tempTree = tree->getLeft();
			delete tree;
			return tempTree;
		}

		//if treeNode has 2 children we must find a replacement
		//find smallest node that is bigger than this one
		TreeNode<ItemType> *tempTree = smallestNode(tree->getRight());
		//copy data to treeNode
		tree->setKey(tempTree->getKey());
		tree->setItem(tempTree->getItem());

		//delete tempTree from treeNode right subtree
		tree->setRight(remove(tempTree->getKey(), tree->getRight()));
		
		return tree;

	//treeNode the should be deleted is in left subtree
	} else if(key < tree->getKey())
	{
		tree->setLeft(remove(key, tree->getLeft()));
		return tree;
		//treeNode the should be deleted is in right subtree
	} else if(key > tree->getKey())
	{
		tree->setRight(remove(key, tree->getRight()));
		return tree;
	}

	cout << "remove error.";
	return 0;
}

template <typename ItemType>
TreeNode<ItemType>* BinarySearchTree<ItemType>::smallestNode(TreeNode<ItemType> *tree)
{
	//this is smallest treeNode
	if(tree->getLeft() == 0)
		return tree;
	else
	{	//get smallest node from left subtree
		return smallestNode(tree->getLeft());
	}

}

template <typename ItemType>
ItemType BinarySearchTree<ItemType>::retrieve(int key, bool &itemFound)
{
	return retrieve(key, itemFound, root);
}

//Recursive retrieve
template <typename ItemType>
ItemType BinarySearchTree<ItemType>::retrieve(int key, bool &itemFound, TreeNode<ItemType> *tree)
{
	if(tree == 0)
	{
		itemFound = false;
		return 0;
	}
	if(tree->getKey() == key)
	{
		itemFound = true;
		return tree->getItem();
	}
	//look in left tree
	if(key < tree->getKey())
	{
		return retrieve(key, itemFound, tree->getLeft());
	}
	//look in right tree
	if(key > tree->getKey())
	{
		return retrieve(key, itemFound, tree->getRight());
	}

	cout << "retrieve error";
	return -1;
}


template <typename ItemType>
void BinarySearchTree<ItemType>::printInorder()
{
	if(root == 0)
	{
		cout << "Binary Search Tree is empty.\n\n";
	} else
	{
		
		cout << "key | item" << endl;
		cout << "----------" << endl;
		inorder(root);
	}
}



template <typename ItemType>
void BinarySearchTree<ItemType>::inorder(TreeNode<ItemType> *tree)
{
	if(tree == 0)
		return;

	inorder(tree->getLeft());
	cout << setw(4) << tree->getKey() << setw(4) << tree->getItem() << endl;
	inorder(tree->getRight());
	return;
	
}

template <typename ItemType>
void BinarySearchTree<ItemType>::printPostorder()
{
	if(root == 0)
	{
		cout << "Binary Search Tree is empty.\n\n";
	} else
	{
		postorder(root);
	}
}

template <typename ItemType>
void BinarySearchTree<ItemType>::postorder(TreeNode<ItemType> *tree, int indent = 0)
{
	if(tree != 0)
	{
		if(tree->getRight())
		{
			postorder(tree->getRight(), indent + 4);
		}
		if(indent)
		{
			std::cout << std::setw(indent) << ' ';
		}
		if(tree->getRight()) std::cout << " /\n" << std::setw(indent) << ' ';
		std::cout << tree->getKey() << "\n ";
		if(tree->getLeft())
		{
			std::cout << std::setw(indent) << ' ' << " \\\n";
			postorder(tree->getLeft(), indent + 4);
		}
	}
}