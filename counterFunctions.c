/*
A set of functions that can be used to implement a shared variable
protected by a semaphore. 
*/

#include <errno.h>
#include <semaphore.h>

static int shared = 0;
static sem_t sem;

/*
Initializes the shared variable.
*/

int InitializeShared (int x)
{   
    if (sem_init (&sem, 0, 1) == -1)
    {
        return -1;
    }
    shared = x;

    return 0;
}

/*
Returns the current value of the shared variable.
*/

int GetShared (int *x)
{
    while (sem_wait (&sem) == -1)
    {
        if (errno != EINTR)
        {
            return -1;
        }
    }
    *x = shared;

    return sem_post (&sem);
}

/*
Atomically increments the value of the shared variable.
*/

int IncrementShared ()
{
    while (sem_wait (&sem) == -1)
    {
        if (errno != EINTR) 
        {
            return -1; 
        }
    }
    shared++;

    return sem_post (&sem); 
}
