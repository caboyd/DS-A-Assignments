/**/

#pragma once
#include "BinaryHeap.h"
#include "BinarySearchTree.cpp"
#include <string>

const int NO_CHARACTER = 0;

class HuffmanCompressor
{
private:
	BinaryHeap minQueue;
	PCTreeNode* prefixTree;
	BinarySearchTree<std::string> encodeTree;
	int elementCount;
public:
	HuffmanCompressor(std::string fileName);
	//Builds the BST for Huffmans Prefix Code Tree
	//Points root to the BST of Huffmans Prefix Code Tree
	void build();
	void buildEncodeTree();
	void encode(std::string fileIn, std::string fileOut);

	void decode(std::string fileName, std::string fileOut);

private:

	void initialization(std::ifstream& input);

	void buildEncodeTree(PCTreeNode* tree, std::string code);

	void printEncode(std::ofstream& output, char c);
	void printDecode(std::ifstream& input, std::ofstream& output) const;
	void printDecode(std::ifstream& input, std::ofstream& output, PCTreeNode* tree) const;
};