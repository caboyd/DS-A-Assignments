/**
 *	Author: Chris Boyd
 *	Date: April 1, 2017
 *
 * replicatedWorkers.h
 *
 * Header file containing global and constants for replicatedWorkers.cpp
 * and prototypes for workerFunctions.cpp
 */
#pragma once

#include <pthread.h>
#include <semaphore.h>

 //Constants for replicated workers
const int EMPTY = 0;
const int NULL_TASK = -1;
const int NO_OF_WORKERS = 5;
const int NO_OF_WORK_POOLS = 3;
const int POOL_SIZE = 1000;

//total threads
const int n = NO_OF_WORKERS * NO_OF_WORK_POOLS;

//globals needed by Hilderman's algorithm
//for ReplicatedWorkers
extern int t[NO_OF_WORK_POOLS + 1];
extern sem_t s[NO_OF_WORK_POOLS + 1]; //t's lock
extern int d[n + 1];
extern int head[NO_OF_WORK_POOLS + 1];
extern int tail[NO_OF_WORK_POOLS + 1];
extern int w[NO_OF_WORK_POOLS + 1][POOL_SIZE];
extern int emptyWorkPools;
extern sem_t e; //emptyWorkPools lock
//threads
extern pthread_t *tids;
//cout output lock
extern sem_t output_lock;
//holds number of new tasks for threads to create
extern int newTasks[n + 1];
//counter for created tasks
extern int taskCounter;
//taskCounter lock
extern sem_t tc;

//Prototypes for workerFunctions.cpp
void* worker(void* args);

//Checks if work pools are empty before
//calling insertTask. increments which
//pool worker will insert next task
void putWork(int workerID, int task);

//Inserts a new task in w for woorkPoolID
void insertTask(int workPoolID, int task);

//Checks if all works pool are empty
//and if so then inserts null tasks for every worker
//then calls remove task
int getWork(int workerID);

//Loops until work is found in the workers pool
//Removes a task from w and returns it
int removeTask(int workPoolID);


//Prints current task worker is working on
//If newTasks[workerID] > 0, will insert new task and decrement newTasks
//Sleeps for a random short time between 10 and 100ms
void doWork(int workerID, int task);