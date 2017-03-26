/*
Child thread function
*/

#include <iostream>
#include <pthread.h>

using namespace std;

extern pthread_t *tids;
//Global matrixes
//Cout output lock
extern pthread_mutex_t output_lock;
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
	void* threadMultiplyMatrix(void* args);
	void* verboseThreadMultiplyMatrix(void* args);
}

void* threadMultiplyMatrix(void* args)
{
	//Parse args
	rowcol* r = static_cast<rowcol*>(args);
	int row = r->row;
	int col = r->col;
	int result =  0;
	for(int i = 0; i < n; i++)
	{
		c[row][col] += a[row][i] * b[i][col];
	}

	delete r;
	return NULL;
}

void* verboseThreadMultiplyMatrix(void* args)
{
	if (pthread_mutex_lock(&output_lock) != 0)
	{
		cerr << "Could not lock output: ";
		exit(4); //something horrible happened - exit whole program with error
	}

	//Print thread
	pthread_t tid = pthread_self();
	for (int i = 0; i < n; i++)
	{
		if (pthread_equal(tid, tids[i]))
		{
			cout << "Thread: " << i << endl;
		}
	}

	//Parse args
	rowcol* r = static_cast<rowcol*>(args);
	int row = r->row;
	int col = r->col;

	//Print row
	cout << "row: " << row << endl;
	for(int i = 0; i < n; i++)
	{
		cout << c[row][i] << " ";
	}
	cout << endl;
	//Print column
	cout << "col: " << col << endl;
	for (int i = 0; i < n; i++)
	{
		cout << c[i][col] << " ";
	}
	cout << endl;

	int result = 0;
	for (int i = 0; i < n; i++)
	{
		c[row][col] += a[row][i] * b[i][col];
	}


	if (pthread_mutex_unlock(&output_lock) != 0)
	{
		cerr << "Could not unlock output: ";
		exit(5);
	}


	delete r;
	return NULL;
}
