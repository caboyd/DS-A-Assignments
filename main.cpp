#include "EdmondsCarpMaxFlow.h"

int main()
{
	EdmondsCarpMaxFlow f("input.txt");
	f.printResidualCapacity();
	f.search(1,8);
	f.paths();

	return 0;
}