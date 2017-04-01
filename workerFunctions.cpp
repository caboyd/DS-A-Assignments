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
#include <ppltasks.h>

const std::string EMPTY = "";
const std::string NULL_TASK = "NULL";

using namespace std;

extern pthread_t *tids;
//Cout output lock
extern pthread_mutex_t output_lock;

//Globals
const int NO_OF_WORKERS = 5;
const int NO_OF_WORK_POOLS = 3;
//total threads
const int n = NO_OF_WORK_POOLS * NO_OF_WORKERS;

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
string getWork(int workerID);
string removeTask(int workPoolID);
void lockOutput();
void unlockOutput();
void doWork(int workerID, string task);

void* worker(void* args)
{
	int i;
	int workerID;
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
	workerID = i + 1;

	lockOutput();

	/****************** Critical Section ****************************/
	cout << "This is worker id " << (int)i + 1 << " from pid " << (long)getpid() << endl;
	sleep(0.1);//Sleep for 100ms

	unlockOutput();

	string task = getWork(workerID);
	while(task != NULL_TASK)
	{
		doWork(workerID, task);
		task = getWork(workerID);
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
	lockOutput();
	cout << "Worker " << workerId << " has inserted task " << task << endl;
	unlockOutput();
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

string getWork(int workerID)
{
	int workPoolID = ((workerID - 1) / NO_OF_WORKERS) + 1;
	Lock(&s[workPoolID]);
	Lock(&e);
	t[workPoolID]--;
	if (t[workPoolID] == -NO_OF_WORKERS)
	{
		emptyWorkPools++;
		if (emptyWorkPools == NO_OF_WORK_POOLS)
		{
			Unlock(&e);
			Unlock(&s[workPoolID]);
			for (int i = 1; i <= NO_OF_WORK_POOLS; i++)
			{
				for (int j = 1; j <= NO_OF_WORKERS; j++)
					insertTask(i, NULL_TASK);
			}
		} else
		{
			Unlock(&e);
			Unlock(&s[workPoolID]);
		}
	} else
	{
		Unlock(&e);
		Unlock(&s[workPoolID]);
	}
	string task = removeTask(workPoolID);
	lockOutput();
	cout << "Worker " << workerID << " has removed task " << task << endl;
	unlockOutput();
	return task;
}

string removeTask(int workPoolID)
{
	Lock(&s[workPoolID]);
	while (true)
	{
		if (w[workPoolID][tail[workPoolID]] == EMPTY)
			Unlock(&s[workPoolID]);
		else
			break;
		Lock(&s[workPoolID]);
	}
	head[workPoolID]++;
	string task = w[workPoolID][head[workPoolID]];
	w[workPoolID][head[workPoolID]] = EMPTY;
	Unlock(&s[workPoolID]);
	return task;
}

void lockOutput()
{
	if (pthread_mutex_lock(&output_lock) != 0)
	{
		cerr << "Could not lock output: ";
		exit(1);
	}
}

void unlockOutput()
{
	if (pthread_mutex_unlock(&output_lock) != 0)
	{
		cerr << "Could not unlock output: ";
		exit(1);
	}
}

void doWork(int workerID, string task)
{
	lockOutput();
	cout << "Worker " << workerID << " is doing task " << task << endl;
	unlockOutput();
}
