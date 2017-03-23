#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;


void someFunction(int** a);


int main()
{
	int i;
	int j;
	int** a;

	cout << "starting main" << endl;

	a = new int*[3];

	for (i = 0; i < 3; i++)
		a[i] = new int[3];

	a[0][0] = 10;
	a[0][1] = 20;
	a[0][2] = 30;
	a[1][0] = 40;
	a[1][1] = 50;
	a[1][2] = 60;
	a[2][0] = 70;
	a[2][1] = 80;
	a[2][2] = 90;

	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
			cout << a[i][j];
		cout << endl;
	}

	cout << "ending main" << endl;

	someFunction(a);

	return 0;
}

void someFunction(int** a)
{
	int i;
	int j;

	cout << "starting someFunction" << endl;

	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
			cout << a[i][j];
		cout << endl;
	}
	cout << "ending someFunction\n";
}
