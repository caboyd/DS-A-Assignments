/*
    This program creates child threads
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int n;
pthread_t *tids;
void *threadout (void *args);

int main (int argc, char *argv [])
{
    int error;
    int i;

/*
    Enter the number of threads to create
*/
    fprintf (stderr, "Parent thread started\n");
    fprintf (stderr, "Enter the number of threads to create: ");
    scanf ("%d", &n);

/*
    Allocate space for thread ids
*/
    tids = (pthread_t *) calloc (n, sizeof (pthread_t));
    if (tids == (pthread_t *) NULL)
    {
        fprintf (stderr, "Failed to allocate memory for thread IDs");
        return 1;
    }

/*
    Create the threads
*/
    fprintf (stderr, "Parent thread creating child threads\n");

    for (i = 0; i < n; i++)
    {
        if (error = pthread_create (tids + i, (pthread_attr_t *) NULL, threadout, (void *) NULL))
        {
            fprintf (stderr, "Failed to create thread:%s\n", strerror (error));
            return 1;
        }
    }

/*
    Wait for the threads to terminate
*/
    for (i = 0; i < n; i++)
    {
        if (error = pthread_join (tids [i], (void **) NULL))
        {
            fprintf (stderr, "Failed to join thread:%s\n", strerror (error));
            return 1;
        }
    }

    fprintf (stderr, "Parent thread done\n");

    return 0;
}
