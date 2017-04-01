/*
This program creates child threads
*/

#include <string>
#include <iostream>
#include <pthread.h>
#include <iomanip>
#include <semaphore.h>
#include <list>
#include <queue>
#include <stdlib.h>


using namespace  std;


pthread_t *tids;
//Cout output lock
pthread_mutex_t output_lock;

//Globals
const int NO_OF_WORKERS = 5;
const int NO_OF_WORK_POOLS = 3;
//total threads
const int n = NO_OF_WORKERS * NO_OF_WORK_POOLS;

int t[NO_OF_WORK_POOLS + 1];
sem_t s[NO_OF_WORK_POOLS + 1]; //t's lock
int d[NO_OF_WORK_POOLS * NO_OF_WORKERS + 1];
int head[NO_OF_WORK_POOLS + 1];
int tail[NO_OF_WORK_POOLS + 1];
string w[NO_OF_WORK_POOLS][100];
int emptyWorkPools;
sem_t e; //emptyWorkPools lock

//prototypes
void replicatedWorkers(string task);
void* worker(void* args);
void putWork(int workerId, string task);


int main(int argc, char *argv[])
{
	//Initialize semaphores
	for (int i = 1; i <= NO_OF_WORK_POOLS; i++)
	{
		Init(&s[i]);
	}
	Init(&e);

	replicatedWorkers("1");


	//Delete semaphores
	for (int i = 1; i <= NO_OF_WORK_POOLS; i++)
	{
		Destroy(&s[i]);
	}
	Destroy(&e);

	return 0;
}

void replicatedWorkers(string task)
{
	tids = new pthread_t[n];

	for (int i = 1; i <= NO_OF_WORK_POOLS; i++)
	{
		t[i] = 0;
		head[i] = 0;
		tail[i] = 0;
		for (int j = (i - 1) * NO_OF_WORKERS + 1; j <= i * NO_OF_WORKERS; j++)
		{
			d[j] = i % NO_OF_WORK_POOLS + 1;
		}
	}
	d[1] = 1;
	emptyWorkPools = 0;

	putWork(1, task);
	for (int i = 0; i < n; i++)
	{
		if (pthread_create(&tids[i], NULL, worker, NULL) > 0)
		{
			cerr << "pthread_create failure" << endl;
			exit(1);
		}
	}


	for (int i = 0; i < n; i++)
	{
		if (pthread_join(tids[i], NULL) > 0)
		{
			cerr << "pthread_join failure" << endl;
			exit(1);
		}
	}

	delete tids;
}

