#pragma once
#include <semaphore.h>


void semInit(sem_t *sem);
void semLock(sem_t *sem);
void semUnlock(sem_t *sem);
void semDestroy(sem_t *sem);
