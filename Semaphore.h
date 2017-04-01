#pragma once
#include <semaphore.h>


void Init(sem_t *sem);
void Lock(sem_t *sem);
void Unlock(sem_t *sem);
void Destroy(sem_t *sem);
