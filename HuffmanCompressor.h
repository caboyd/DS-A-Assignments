/*	Chris Boyd
 *	March 5, 2017
 */

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
	//Calls initialize, build, buildEncodeTree
	HuffmanCompressor(std::string fileName);

	//Builds the BST for Huffmans Prefix Code Tree
	//Points root to the BST of Huffmans Prefix Code Tree
	void build();

	//Builds encode tree using prefixTree
	void buildEncodeTree();

	//Encodes a file to 1s and 0s using encode tree
	//Reads from a text file and outputs 0/1s to output file
	void encode(std::string fileIn, std::string fileOut);

	//Decodes an encoded file
	void decode(std::string fileName, std::string fileOut);

	//Prints the prefix BST with chars and frequency
	void printPrefixTree();
	
	//Prings the chars and corresponding codes
	void printEncodeTree();
private:

	//Reads all characters from file into BST.
	//Places PCTreeNodes into minQueue for each char found
	void initialization(std::ifstream& input);

	//helper functions
	void buildEncodeTree(PCTreeNode* tree, std::string code);
	void printEncode(std::ofstream& output, char c);
	void printDecode(std::ifstream& input, std::ofstream& output) const;
	void printDecode(std::ifstream& input, std::ofstream& output, PCTreeNode* tree) const;
	void postorder(PCTreeNode* tree, int indent);
};