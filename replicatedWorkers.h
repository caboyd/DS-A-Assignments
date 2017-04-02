#pragma once

#include <pthread.h>
#include <semaphore.h>


pthread_t *tids;
//Cout output lock
sem_t output_lock;

//Globals
const int NO_OF_WORKERS = 5;
const int NO_OF_WORK_POOLS = 3;
const int POOL_SIZE = 1000;
//total threads
const int n = NO_OF_WORKERS * NO_OF_WORK_POOLS;

int t[NO_OF_WORK_POOLS + 1];
sem_t s[NO_OF_WORK_POOLS + 1]; //t's lock
int d[n + 1];
int head[NO_OF_WORK_POOLS + 1];
int tail[NO_OF_WORK_POOLS + 1];
int w[NO_OF_WORK_POOLS + 1][POOL_SIZE];
int emptyWorkPools;
sem_t e; //emptyWorkPools lock


//Random number of new tasks for threads to create
int newTasks[n + 1];
int taskCounter = 1;
sem_t tc; //taskCounter lock


//Prototype thread functions
void replicatedWorkers(int task);
extern void* worker(void* args);
extern void putWork(int workerID, int task);
extern void insertTask(int workPoolID, int task);
int getWork(int workerID);
int removeTask(int workPoolID);
void lockOutput();
void unlockOutput();
void doWork(int workerID, int task);