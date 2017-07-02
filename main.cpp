#include "EdmondsCarpMaxFlow.h"
#include <iostream>

using namespace std;

int main()
{
	EdmondsCarpMaxFlow f("input.txt");
	cout << "Initial Residual Capacity Matrix\n";
	cout << "For 8 vertex graph\n\n";
	f.printResidualCapacity();
	f.search(1,8);
	cout << "Paths\n";
	f.paths();

	return 0;
}