/*		Name: Chris Boyd
Date: Dec 1, 2015

Description: Binary search tree implementation
*/

#include "BinarySearchTreeTemplate.cpp"
#include <iostream>
using namespace std;

int main()
{
	BinarySearchTree<int> tree;

	//print empty tree
	tree.printInorder();

	//insert one item with key 10
	//I will just use dummy data
	tree.insert(10, 0);


	tree.printInorder();
	cout << endl;

	tree.insert(9, 0);
	tree.insert(11, 0);

	tree.printInorder();
	cout << endl;


	tree.insert(4, 0);
	tree.insert(16, 0);
	tree.insert(13, 0);
	tree.insert(2, 0);
	tree.insert(20, 0);
	tree.insert(14, 0);
	tree.insert(17, 0);
	tree.insert(24, 0);

	tree.printPostorder();
	cout << endl;
	cout << endl;
	cout << endl;

	//delete leaf node
	tree.remove(20);
	tree.printPostorder();
	cout << endl;
	cout << endl;
	cout << endl;

	//delete root node
	tree.remove(10);
	tree.printPostorder();
	cout << endl;
	cout << endl;
	cout << endl;

	//delete root node
	tree.remove(11);
	tree.printPostorder();
	cout << endl;
	cout << endl;
	cout << endl;

	bool itemFound = false;
	int num;
	//find 13 ,16, 2
	cout << "Searching for 13" << endl;
	num = tree.retrieve(13, itemFound);
	if (itemFound)
		cout << "13 was found" << endl;
	else
		cout << "13 was not found" << endl;

	itemFound = false;
	cout << "Searching for 16" << endl;
	num = tree.retrieve(16, itemFound);
	if (itemFound)
		cout << "16 was found" << endl;
	else
		cout << "16 was not found" << endl;

	itemFound = false;
	cout << "Searching for 2" << endl;
	num = tree.retrieve(2, itemFound);
	if (itemFound)
		cout << "2 was found" << endl;
	else
		cout << "2 was not found" << endl;


	itemFound = false;
	cout << "Searching for 40" << endl;
	num = tree.retrieve(40, itemFound);
	if (itemFound)
		cout << "40 was found" << endl;
	else
		cout << "40 was not found" << endl;
	cin.get();
	return 0;
}