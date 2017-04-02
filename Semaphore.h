/*
 * Semaphore.h
 *
 *	Contains functions to make semaphores easier to use
 *
 */
#pragma once
#include <semaphore.h>

//Initialize semaphore with 1 resource
void semInit(sem_t *sem);
//Wait and lock semaphore
void semLock(sem_t *sem);
//unlock semaphore
void semUnlock(sem_t *sem);
//destroy semaphore
void semDestroy(sem_t *sem);
