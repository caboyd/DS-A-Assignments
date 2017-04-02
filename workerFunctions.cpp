/*
Child thread function
*/

#include <iostream>
#include <string>
#include <stdlib.h>
#include "Sleep.h"
#include <queue>
#include "Semaphore.h"
#include "replicatedWorkers.h"


using namespace std;

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
	for (i = 1; i <= n; i++)
	{
		if (pthread_equal(tid, tids[i]))
		{
			break;
		}
	}
	workerID = (int)i;
	int workPoolID = ((workerID - 1) / NO_OF_WORKERS) + 1;

	int task = getWork(workerID);
	while(task != NULL_TASK)
	{
		doWork(workerID, task);

		lockOutput();
		cout << "Worker " << workerID << " has finished task " << task;
		cout << " in workPoolID " << workPoolID << endl;
		unlockOutput();

		task = getWork(workerID);
	}

	lockOutput();
	cout << "Worker " << workerID << " has terminated" << endl;
	unlockOutput();

	return NULL;
}


void putWork(int workerID, int task)
{
	int workPoolID = d[workerID];
	semLock(&s[workPoolID]);
	semLock(&e);
	t[workPoolID]++;
	if (t[workPoolID] == -NO_OF_WORKERS + 1)
		emptyWorkPools--;
	semUnlock(&e);
	semUnlock(&s[workPoolID]);
	insertTask(workPoolID, task);

	d[workerID] = workPoolID % NO_OF_WORK_POOLS + 1;
}

void insertTask(int workPoolID, int task)
{
	semLock(&s[workPoolID]);
	tail[workPoolID]++;
	w[workPoolID][tail[workPoolID]] = task;
	semUnlock(&s[workPoolID]);
	return;
}

int getWork(int workerID)
{
	int workPoolID = ((workerID - 1) / NO_OF_WORKERS) + 1;
	semLock(&s[workPoolID]);
	semLock(&e);
	t[workPoolID]--;
	if (t[workPoolID] == -NO_OF_WORKERS)
	{
		emptyWorkPools++;
		if (emptyWorkPools == NO_OF_WORK_POOLS)
		{
			semUnlock(&e);
			semUnlock(&s[workPoolID]);
			for (int i = 1; i <= NO_OF_WORK_POOLS; i++)
			{
				for (int j = 1; j <= NO_OF_WORKERS; j++)
					insertTask(i, NULL_TASK);
			}
		} else
		{
			semUnlock(&e);
			semUnlock(&s[workPoolID]);
		}
	} else
	{
		semUnlock(&e);
		semUnlock(&s[workPoolID]);
	}
	int task = removeTask(workPoolID);
	return task;
}

int removeTask(int workPoolID)
{
	semLock(&s[workPoolID]);
	while (true)
	{
		if (w[workPoolID][tail[workPoolID]] == EMPTY)
			semUnlock(&s[workPoolID]);
		else
			break;
		semLock(&s[workPoolID]);
	}
	head[workPoolID]++;
	int task = w[workPoolID][head[workPoolID]];
	w[workPoolID][head[workPoolID]] = EMPTY;
	semUnlock(&s[workPoolID]);
	return task;
}

void lockOutput()
{
	semLock(&output_lock);
}

void unlockOutput()
{
	semUnlock(&output_lock);
}

void doWork(int workerID, int task)
{
	lockOutput();
	cout << "Worker " << workerID << " has started task " << task;
	cout << " in workPoolID " << ((workerID - 1) / NO_OF_WORKERS) + 1 << endl;
	unlockOutput();
	if(newTasks[workerID] > 0)
	{
		newTasks[workerID]--;
		int workPoolID = d[workerID];
		semLock(&tc);
		taskCounter++;
		int tempTaskCounter = taskCounter;
		semUnlock(&tc);

		putWork(workerID, tempTaskCounter);

		lockOutput();
		cout << "Worker " << workerID << " has inserted task " << tempTaskCounter;
		cout << " in workPoolID " << workPoolID << endl;
		unlockOutput();
	}

	//10 to 100ms sleep
	sleep((double)(rand() % 10 + 1) / 100);
}
