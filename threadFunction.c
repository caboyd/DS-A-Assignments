/*
A thread function with a critical section protected by a semaphore
passed as its parameter.
*/

#include <errno.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

#define TEN_MILLION 10000000L
#define BUFSIZE 1024

extern pthread_t *tids;
extern int n;

void *threadout (void *args)
{
    char buffer [BUFSIZE];
    char *c;
    int i;
    sem_t *semp;
    pthread_t tid = pthread_self ();
    struct timespec sleeptime;

    semp = (sem_t *) args;
    sleeptime.tv_sec = 0;
    sleeptime.tv_nsec = TEN_MILLION;

/* This for loop converts a thread id into an integer. It works
   on both Hercules and the Linux machines in CL115. It solves
   the problem of printing thread ids when they are implemented
   as structs (such on the Linux machines in CL115). In this way,
   thread ids are handled consistently when printed from the
   different POSIX implementations.                             */
    for (i = 0; i < n; i ++)
    {
        if (pthread_equal (tid, tids [i]))
        {
            break;
        }
    }
    snprintf (buffer, BUFSIZE, "This is tid %d from pid %ld\n", (int) i + 2, (long) getpid ());
    c = buffer;

/****************** Lock ****************************************/
    while (sem_wait (semp) == -1)
    {
        if(errno != EINTR)
        {
            fprintf (stderr, "Thread failed to lock semaphore\n");
            return NULL;
        }
    }

/****************** Critical Section ****************************/
    while (*c != '\0')
    {
        fputc (*c, stderr);
        c++;
        nanosleep (&sleeptime, NULL);
    }

/****************** Unlock **************************************/
    if (sem_post (semp) == -1)
    {
        fprintf (stderr, "Thread failed to unlock semaphore\n");
    }

    return NULL;
}
