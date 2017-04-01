/*
Child thread function
*/

#include <iostream>
#include <string>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>
#include "Sleep.h"
#include <queue>
#include "semaphoreFunctions.cpp"

using namespace std;

extern pthread_t *tids;
//Cout output lock
extern pthread_mutex_t output_lock;

//Globals
extern const int NO_OF_WORKERS = 5;
extern const int NO_OF_WORK_POOLS = 3;
//total threads
extern const int n;

extern int t[NO_OF_WORK_POOLS + 1];
extern sem_t s[NO_OF_WORK_POOLS + 1]; //t's lock
extern int d[NO_OF_WORK_POOLS * NO_OF_WORKERS + 1];
extern int head[NO_OF_WORK_POOLS + 1];
extern int tail[NO_OF_WORK_POOLS + 1];
extern string w[NO_OF_WORK_POOLS][100];
extern int emptyWorkPools;
extern sem_t e; //emptyWorkPools lock



//Prototype thread functions
extern void* worker(void* args);
extern void putWork(int workerId, string task);
extern void insertTask(int workPoolID, string task);

void* worker(void* args)
{
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


	/****************** Lock ****************************************/
	if (pthread_mutex_lock(&output_lock) != 0)
	{
		cerr << "Could not lock output: ";
		exit(1);
	}

	/****************** Critical Section ****************************/

	cout << "This is worker id " << (int)i + 1 << " from pid " << (long)getpid() << endl;
	sleep(0.1);//Sleep for 100ms


	/****************** Unlock **************************************/
	if (pthread_mutex_unlock(&output_lock) != 0)
	{
		cerr << "Could not unlock output: ";
		exit(1);
	}

	return NULL;
}


void putWork(int workerId, string task)
{
	int workPoolID = d[workerId];
	Lock(&s[workPoolID]);
	Lock(&e);
	t[workPoolID]++;
	if (t[workPoolID] == -NO_OF_WORKERS + 1)
		emptyWorkPools--;
	Unlock(&e);
	Unlock(&s[workPoolID]);
	insertTask(workPoolID, task);
	d[workerId] = workPoolID % NO_OF_WORK_POOLS + 1;
}

void insertTask(int workPoolID, string task)
{
	Lock(&s[workPoolID]);
	tail[workPoolID]++;
	w[workPoolID][tail[workPoolID]] = task;
	Unlock(&s[workPoolID]);
	return;
}
