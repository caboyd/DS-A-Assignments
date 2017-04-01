#include <semaphore.h>

void Init (sem_t *sem);
void Lock (sem_t *sem);
void Unlock (sem_t *sem);
void Destroy (sem_t *sem);

void Init (sem_t *sem)
{
    if (sem_init (sem, 0, 1) == -1)
    {
        perror ("Failed to initialize semaphore");
        exit (1);
    }

    return;
}

void Lock (sem_t *sem)
{
    while (sem_wait (sem) == -1)
    {
        if(errno != EINTR)
        {
            fprintf (stderr, "Thread failed to lock semaphore\n");
            exit (1);
        }
    }

    return;
}

void Unlock (sem_t *sem)
{
    if (sem_post (sem) == -1)
    {
        fprintf (stderr, "Thread failed to unlock semaphore\n");
        exit (1);
    }

    return;
}

void Destroy (sem_t *sem)
{
    if (sem_destroy (sem) == -1)
    {
        perror ("Failed to destroy semaphore");
        exit (1);
    }

    return;
}
