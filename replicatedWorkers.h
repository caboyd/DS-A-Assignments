#pragma once

#include <pthread.h>
#include <semaphore.h>

const int EMPTY = 0;
const int NULL_TASK = -1;
const int NO_OF_WORKERS = 5;
const int NO_OF_WORK_POOLS = 3;
const int POOL_SIZE = 1000;
//total threads
const int n = NO_OF_WORKERS * NO_OF_WORK_POOLS;

//globals
extern int t[NO_OF_WORK_POOLS + 1];
extern sem_t s[NO_OF_WORK_POOLS + 1]; //t's lock
extern int d[n + 1];
extern int head[NO_OF_WORK_POOLS + 1];
extern int tail[NO_OF_WORK_POOLS + 1];
extern int w[NO_OF_WORK_POOLS + 1][POOL_SIZE];
extern int emptyWorkPools;
extern sem_t e; //emptyWorkPools lock

extern pthread_t *tids;
//Cout output lock
extern sem_t output_lock;

//Random number of new tasks for threads to create
extern int newTasks[n + 1];
extern int taskCounter;
extern sem_t tc; //taskCounter lock


//Prototype thread functions
void replicatedWorkers(int task);
extern void* worker(void* args);
extern void putWork(int workerID, int task);
void insertTask(int workPoolID, int task);
int getWork(int workerID);
int removeTask(int workPoolID);
void lockOutput();
void unlockOutput();
void doWork(int workerID, int task);