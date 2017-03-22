/*
    Child thread function
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

extern int n;
extern pthread_t *tids;

void *threadout (void *args)
{
    int i;
    pthread_t tid = pthread_self ();

/*
    This for loop converts a thread id into an integer. It works
    on both Hercules and the Linux machines in CL115. It solves
    the problem of printing thread ids when they are implemented
    as structs (such on the Linux machines in CL115). In this way,
    thread ids are handled consistently when printed from the
    different POSIX implementations.
*/
    for (i = 0; i < n; i ++)
    {
        if (pthread_equal (tid, tids [i]))
        {
            break;
        }
    }

/*
    Print the child's thread ID to show that it was actually
    created.

    NOTE: This is not actually how child threads should use the
    screen or any shared resource. The problem is that any child
    thread can write to the screen (or use the shared resource)
    at any time. If the more than one child thread writes to the
    screen (or uses the shared resource) at the same time, the
    results should be considered unreliable.
*/
    fprintf (stderr, "Child thread done (ID = %d)\n", i);

    return (void *) NULL;
}
