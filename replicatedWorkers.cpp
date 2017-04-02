/*
This program creates child threads
*/

#include <string>
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include "Semaphore.h"
#include "replicatedWorkers.h"

using namespace  std;

//globals
int t[NO_OF_WORK_POOLS + 1];
sem_t s[NO_OF_WORK_POOLS + 1]; //t's lock
int d[n + 1];
int head[NO_OF_WORK_POOLS + 1];
int tail[NO_OF_WORK_POOLS + 1];
int w[NO_OF_WORK_POOLS + 1][POOL_SIZE];
int emptyWorkPools;
sem_t e; //emptyWorkPools lock

pthread_t *tids;
//Cout output lock
sem_t output_lock;

//Random number of new tasks for threads to create
int newTasks[n + 1];
int taskCounter = 1;
sem_t tc; //taskCounter lock

int main(int argc, char *argv[])
{
	srand(time(0));
	replicatedWorkers(taskCounter);
	return 0;
}

void replicatedWorkers(int task)
{
	cout << "Pid " << (long)getpid() << " has started" << endl;

	//Initialzie random count of new tasks


	//Initialize semaphores
	for (int i = 1; i <= NO_OF_WORK_POOLS; i++)
		semInit(&s[i]);
	semInit(&e);
	semInit(&tc);
	semInit(&output_lock);

	//Allocated threads
	tids = new pthread_t[NO_OF_WORK_POOLS * NO_OF_WORKERS + 1];

	//initialize
	for (int i = 1; i <= NO_OF_WORK_POOLS; i++)
	{
		//initialzie workpools to empty
		for (int j = 0; j < POOL_SIZE; j++)
			w[i][j] = EMPTY;

		t[i] = 0;
		head[i] = 0;
		tail[i] = 0;
		for (int j = (i - 1) * NO_OF_WORKERS + 1; j <= i * NO_OF_WORKERS; j++)
		{
			d[j] = i % NO_OF_WORK_POOLS + 1;
			//10 to 20 new tasks per thread
			newTasks[j] = rand() % 20 + 10;
		}
	}

	d[1] = 1;

	emptyWorkPools = 0;

	//Insert first task
	putWork(1, task);
	cout << "Pid " << (long)getpid() << " has created task " << task;
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

	cout << "Pid " << (long)getpid() << " has terminated." << endl;
}

