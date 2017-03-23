/*
Child thread function
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <iostream>

using namespace std;

//Global matrixes
extern int ** a;
extern int ** b;
//c matrix will be of dimensions m x r
extern int ** c;
extern int n;

struct rowcol
{
	int row, col;
};

//Prototype thread functions as C functions
extern "C" {
	void *threadMultiplyMatrix(void *args);
}

void *threadMultiplyMatrix(void *args)
{
	//Parse args
	rowcol *r = static_cast<rowcol*>(args);
	int row = r->row;
	int col = r->col;
	int result =  0;
	for(int i = 0; i < n; i++)
	{
		c[row][col] += a[row][i] * b[i][col];
	}

	return static_cast<void*>(NULL);
}
