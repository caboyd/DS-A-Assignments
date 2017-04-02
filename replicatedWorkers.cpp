/*
*	Author: Chris Boyd
*	Date: April 1, 2017
*	Assignment 6
*
*	Replicated Workers algorithm 
*
*/

#include <iostream>
#include <stdlib.h>
#include "Semaphore.h"
#include "replicatedWorkers.h"
#include <time.h>

using namespace  std;

int t[NO_OF_WORK_POOLS + 1];
sem_t s[NO_OF_WORK_POOLS + 1];
int d[n + 1];
int head[NO_OF_WORK_POOLS + 1];
int tail[NO_OF_WORK_POOLS + 1];
int w[NO_OF_WORK_POOLS + 1][POOL_SIZE];
int emptyWorkPools;
sem_t e;
pthread_t *tids;
sem_t output_lock;
int newTasks[n + 1];
int taskCounter;
sem_t tc;


//Prototypes
//Performs Hilderman's replicated Workers algorithm
void* replicatedWorkers(int task);

int main(int argc, char *argv[])
{
	srand(time(0));
	pthread_t parent;

	if (pthread_create(&parent, NULL, replicatedWorkers, NULL) > 0)
	{
		cerr << "pthread_create failure" << endl;
		exit(1);
	}

	if (pthread_join(parent, NULL) > 0)
	{
		cerr << "pthread_join failure" << endl;
		exit(1);
	}

	return 0;
}

void* replicatedWorkers(int task)
{
	cout << "Pid " << (long)getpid() << " has started" << endl;

	//Initialize semaphores
	for (int i = 1; i <= NO_OF_WORK_POOLS; i++)
		semInit(&s[i]);
	semInit(&e);
	semInit(&tc);
	semInit(&output_lock);

	//Allocated threads
	tids = new pthread_t[NO_OF_WORK_POOLS * NO_OF_WORKERS + 1];

	for (int i = 1; i <= NO_OF_WORK_POOLS; i++)
	{
		//initialzie workpools to empty
		for (int j = 0; j < POOL_SIZE; j++)
			w[i][j] = EMPTY;

		//initialize globals
		t[i] = 0;
		head[i] = 0;
		tail[i] = 0;
		for (int j = (i - 1) * NO_OF_WORKERS + 1; j <= i * NO_OF_WORKERS; j++)
		{
			//Initialize which workpool a worker will insert to
			d[j] = i % NO_OF_WORK_POOLS + 1;
			//Initialzie random count of new tasks
			//10 to 20 new tasks per thread
			newTasks[j] = rand() % 20 + 10;
		}
	}
	//worker 1 inserts into workpool 1
	d[1] = 1;

	emptyWorkPools = 0;

	//initializer global task counter
	taskCounter = 1;

	//Insert first task
	putWork(1, taskCounter);
	cout << "Pid " << (long)getpid() << " has created task " << taskCounter;
	cout << " in workPoolID " << 1 << endl;

	//create threads
	for (int i = 1; i <= n; i++)
	{
		if (pthread_create(&tids[i], NULL, worker, NULL) > 0)
		{
			cerr << "pthread_create failure" << endl;
			exit(1);
		}
	}

	//wait for threads to end
	for (int i = 1; i <= n; i++)
	{
		if (pthread_join(tids[i], NULL) > 0)
		{
			cerr << "pthread_join failure" << endl;
			exit(1);
		}
	}

	//Delete semaphores
	for (int i = 1; i <= NO_OF_WORK_POOLS; i++)
		semDestroy(&s[i]);
	semDestroy(&e);
	semDestroy(&tc);
	semDestroy(&output_lock);

	delete tids;

	cout << "Pid " << (long)getpid() << " has terminated" << endl;
}

