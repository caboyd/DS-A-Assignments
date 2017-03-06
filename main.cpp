/*	Chris Boyd
*	March 5, 2017
*	
*	Description: Performs huffmans encoding on
*	text.txt file and then decodes the encoded file.
*/

#include <iostream>
#include "HuffmanCompressor.h"

using namespace std;

int main()
{
	HuffmanCompressor c("text.txt");
	cout << "Prefix Codes for encoding text.txt\n\n";
	c.printEncodeTree();
	cout << "\n\n\n";
	cout << "Binary Search Tree for decoding\n\n";
	c.printPrefixTree();
	c.encode("text.txt","encoded.txt");
	c.decode("encoded.txt", "decoded.txt");
	return 0;
}