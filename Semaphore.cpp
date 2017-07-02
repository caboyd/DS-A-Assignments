#include "Semaphore.h"
#include <iostream>
#include <stdlib.h>
#include <errno.h>

void semInit(sem_t *sem)
{
	if (sem_init(sem, 0, 1) == -1)
	{
		std::cerr << "Failed to initialize semaphore";
		exit(1);
	}
}

void semLock(sem_t *sem)
{
	while (sem_wait(sem) == -1)
	{
		if (errno != EINTR)
		{
			std::cerr << "Thread failed to lock semaphore\n";
			exit(1);
		}
	}
}

void semUnlock(sem_t *sem)
{
	if (sem_post(sem) == -1)
	{
		std::cerr << "Thread failed to unlock semaphore\n";
		exit(1);
	}
}

void semDestroy(sem_t *sem)
{
	if (sem_destroy(sem) == -1)
	{
		std::cerr << "Failed to destroy semaphore";
		exit(1);
	}
}
