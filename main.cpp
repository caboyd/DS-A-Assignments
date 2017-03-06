#include "BinaryHeap.h"

#include <iostream>
#include "HuffmanCompressor.h"

using namespace std;

int main()
{
	HuffmanCompressor c("text.txt");

	c.encode("text.txt","encoded.txt");
	c.decode("encoded.txt", "decoded.txt");
	return 0;
}