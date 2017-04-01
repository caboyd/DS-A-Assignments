/*
Child thread function
*/

#include <iostream>
#include <string>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>
#include "Sleep.h"

using namespace std;

extern pthread_t *tids;

//total num of workers
extern const int n;

//Cout output lock
extern pthread_mutex_t output_lock;


//Prototype thread functions
void* worker(void* args);


void* worker(void* args)
{
	string s;
	int i;
	pthread_t tid = pthread_self();

	/* This for loop converts a thread id into an integer. It works
	on both Hercules and the Linux machines in CL115. It solves
	the problem of printing thread ids when they are implemented
	as structs (such on the Linux machines in CL115). In this way,
	thread ids are handled consistently when printed from the
	different POSIX implementations.                             */
	for (i = 0; i < n; i++)
	{
		if (pthread_equal(tid, tids[i]))
		{
			break;
		}
	}
	s = "This is tid" + ((int)i + 2);
	s += " from pid " + (long)getpid();

	/****************** Lock ****************************************/
	if (pthread_mutex_lock(&output_lock) != 0)
	{
		cerr << "Could not lock output: ";
		exit(1);
	}

	/****************** Critical Section ****************************/

	cout << s;
	sleep(0.1);//Sleep for 100ms

	/****************** Unlock **************************************/
	if (pthread_mutex_unlock(&output_lock) != 0)
	{
		cerr << "Could not unlock output: ";
		exit(1);
	}

	return NULL;
}
