/*
	This program creates child threads
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <iostream>

using namespace  std;
int n;
pthread_t *tids;

//Prototype thread functions as C functions
extern "C"{
	void *threadout(void *args);
}


int main(int argc, char *argv[])
{
	int error;
	int i;

	/*
		Enter the number of threads to create
	*/
	cout << "Parent thread started" << endl;
	cout << "Enter the number of threads to create: ";
	cin >> n;

	/*
		Allocate space for thread ids
	*/
	tids = (pthread_t *)calloc(n, sizeof(pthread_t));
	if (tids == static_cast<pthread_t*>(NULL))
	{
		cout << "Failed to allocate memory for thread IDs";
		return 1;
	}

	/*
		Create the threads
	*/
	cout << "Parent thread creating child threads" << endl;

	for (i = 0; i < n; i++)
	{
		if (error = pthread_create(tids + i, static_cast<pthread_attr_t *>(NULL), threadout, static_cast<void *>(NULL)))
		{
			cout << "Failed to create thread: " << error << endl;
			return 1;
		}
	}

	/*
		Wait for the threads to terminate
	*/
	for (i = 0; i < n; i++)
	{
		if (error = pthread_join(tids[i], static_cast<void **>(NULL)))
		{
			cout << "Failed to join thread: " << error << endl;
			return 1;
		}
	}

	cout << "Parent thread done" << endl;

	return 0;
}
