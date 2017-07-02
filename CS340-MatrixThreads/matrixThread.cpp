/*
Child thread function
*/

#include <iostream>
#include <pthread.h>
#include <stdlib.h>

using namespace std;

extern pthread_t *tids;
//Global matrixes
//Cout output lock
extern pthread_mutex_t output_lock;
extern int ** a;
extern int ** b;
//c matrix will be of dimensions m x r
extern int ** c;
extern int n, m, r;

struct RowCol
{
	int row, col;
};

//Prototype thread functions as C functions
extern "C" {
	void* threadMultiplyMatrix(void* args);
	void* verboseThreadMultiplyMatrix(void* args);
}

void* threadMultiplyMatrix(void* args)
{
	//Parse args
	RowCol* rc = static_cast<RowCol*>(args);
	int row = rc->row;
	int col = rc->col;
	delete rc;
	int result =  0;
	for(int i = 0; i < n; i++)
	{
		c[row][col] += a[row][i] * b[i][col];
	}
	return NULL;
}

void* verboseThreadMultiplyMatrix(void* args)
{
	if (pthread_mutex_lock(&output_lock) != 0)
	{
		cerr << "Could not lock output: ";
		exit(1); //something horrible happened - exit whole program with error
	}

	//Print thread
	pthread_t tid = pthread_self();
	for (int i = 0; i <= n; i++)
	{
		if (pthread_equal(tid, tids[i]))
		{
			cout << "Thread: " << i << endl;
			break;
		}
	}

	//Parse args
	RowCol* rc = static_cast<RowCol*>(args);
	int row = rc->row;
	int col = rc->col;
	delete rc;

	//Print row
	cout << "row: " << row + 1 << "\n\t";
	for(int i = 0; i < n; i++)
	{
		cout << a[row][i] << " ";
	}
	cout << endl;
	//Print column
	cout << "col: " << col + 1 << "\n\t";
	for (int i = 0; i < n; i++)
	{
		cout << b[i][col] << " ";
	}
	cout << endl << endl;

	int result = 0;
	for (int i = 0; i < n; i++)
	{
		c[row][col] += a[row][i] * b[i][col];
	}

	if (pthread_mutex_unlock(&output_lock) != 0)
	{
		cerr << "Could not unlock output: ";
		exit(1);
	}

	return NULL;
}
