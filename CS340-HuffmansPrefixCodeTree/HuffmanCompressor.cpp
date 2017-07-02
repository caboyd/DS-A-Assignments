/*	Chris Boyd
*	March 5, 2017
*/

#include "HuffmanCompressor.h"
#include <fstream>
#include <iostream>

using namespace std;

HuffmanCompressor::HuffmanCompressor(std::string fileName) 
{
	ifstream input(fileName.c_str());
	initialization(input);
	input.close();

	build();
	buildEncodeTree();
}


void HuffmanCompressor::build()
{
	PCTreeNode t;
	
	for(int i = 1; i < elementCount; i++)
	{
		PCTreeNode* t1 = new PCTreeNode{};
		t = minQueue.deleteMin();
		t1->character = t.character;
		t1->frequency = t.frequency;
		t1->left = t.left;
		t1->right = t.right;

		PCTreeNode* t2 = new PCTreeNode{};
		t = minQueue.deleteMin();
		t2->character = t.character;
		t2->frequency = t.frequency;
		t2->left = t.left;
		t2->right = t.right;

		t.character = 0;
		t.frequency = t1->frequency + t2->frequency;
		t.left = t1;
		t.right = t2;
		minQueue.insert(t);
	}
	t = minQueue.deleteMin();
	prefixTree = new PCTreeNode;
	prefixTree->character = t.character;
	prefixTree->frequency = t.frequency;
	prefixTree->left = t.left;
	prefixTree->right = t.right;
}

void HuffmanCompressor::buildEncodeTree()
{
	buildEncodeTree(prefixTree, "");
}

void HuffmanCompressor::printEncodeTree()
{	
	encodeTree.printInorder();
}

void HuffmanCompressor::initialization(std::ifstream& input)
{
	BinarySearchTree<PCTreeNode> tempTree;
	char c;
	elementCount = 0;
	//Reads all characters into BST.
	//Count frequencies
	while (input.get(c))
	{
		int asciiValue = int(c);
		bool itemFound = false;
		PCTreeNode n = tempTree.retrieve(asciiValue, itemFound);
		if (!itemFound)
		{
			elementCount++;
			n.frequency = 1;
			n.character = c;
			n.left = 0;
			n.right = 0;
			tempTree.insert(asciiValue, n);
		} else
		{
			n.frequency += 1;
			tempTree.update(asciiValue, itemFound, n);
			if (!itemFound)
				cout << "error updating frequency of " << c << endl;
		}
	}

	//Create minQueue will frequency of characters
	for (int i = 0; i < elementCount; i++)
		minQueue.insert(tempTree.pop());
}

void HuffmanCompressor::buildEncodeTree(PCTreeNode* tree, string code)
{
	if (!tree)
		return;
	if (tree->left)
	{
		string s = code + "0";
		buildEncodeTree(tree->left, s);
	}

	if (tree->right)
	{
		string s = code + "1";
		buildEncodeTree(tree->right, s);
	}
	if(tree->character != NO_CHARACTER)
		encodeTree.insert(tree->character, code);
}

void HuffmanCompressor::encode(std::string fileIn, std::string fileOut)
{
	ifstream input(fileIn.c_str());
	ofstream output(fileOut.c_str());

	char c;
	while (input.get(c))
	{
		printEncode(output, c);
	}
}

void HuffmanCompressor::decode(std::string fileIn, std::string fileOut)
{
	ifstream input(fileIn.c_str());
	ofstream output(fileOut.c_str());
	while (!input.eof())
		printDecode(input, output);
}

void HuffmanCompressor::printPrefixTree()
{
	postorder(prefixTree, 0);
}

void HuffmanCompressor::postorder(PCTreeNode *tree, int indent = 0)
{
	if (tree)
	{
		if (tree->right)
			postorder(tree->right, indent + 4);
		if (indent)
			std::cout << std::setw(indent) << "";
		if (tree->right)
			std::cout << " /\n" << std::setw(indent) << "";

		if (tree->character)
			std::cout << "(" <<tree->character << ")";
		else
			std::cout << "nil";
		std::cout << " (freq = " << tree->frequency << ")\n";

		if (tree->left)
		{
			std::cout << std::setw(indent) << ' ' << " \\\n";
			postorder(tree->left, indent + 4);
		}
	}
}

void HuffmanCompressor::printEncode(std::ofstream& output, char c)
{
	bool itemFound;
	string s = encodeTree.retrieve(c, itemFound);
	if (!itemFound)
		cout << "error code " << c << " not found\n";
	output << s;
}

void HuffmanCompressor::printDecode(std::ifstream& input, std::ofstream& output) const
{
	while (!input.eof())
		printDecode(input, output, prefixTree);
}

void HuffmanCompressor::printDecode(std::ifstream& input, std::ofstream& output, PCTreeNode* tree) const
{
	if (tree->character != NO_CHARACTER)
	{
		output << tree->character;
		return;
	}

	char c;
	input.get(c);

	if(c == '0')
	{
		if (tree->left)
			printDecode(input, output, tree->left);
	}
	if(c == '1')
	{
		if (tree->right)
			printDecode(input, output, tree->right);
	}
}
