#include <stdio.h>
#include <stdlib.h>

void someFunction (int** a);

int main ()
{
    int i;
    int j;
    int** a;

    fprintf (stderr, "starting main\n");

    a = (int **) calloc (3, sizeof (int *));

    for (i = 0; i < 3; i ++)
    {
        a [i] = calloc (3, sizeof (int *));
    }

    a [0][0] = 10;
    a [0][1] = 20;
    a [0][2] = 30;
    a [1][0] = 40;
    a [1][1] = 50;
    a [1][2] = 60;
    a [2][0] = 70;
    a [2][1] = 80;
    a [2][2] = 90;

    for (i = 0; i < 3; i ++)
    {
        for (j = 0; j < 3; j ++)
        {
            fprintf (stderr, "%d ", a [i][j]);
        }
        fprintf (stderr, "\n");
    }

    fprintf (stderr, "ending main\n");

    someFunction (a);

    return (0);
}

void someFunction (int** a)
{
    int i;
    int j;

    fprintf (stderr, "starting someFunction\n");

    for (i = 0; i < 3; i ++)
    {
        for (j = 0; j < 3; j ++)
        {
            fprintf (stderr, "%d ", a [i][j]);
        }
        fprintf (stderr, "\n");
    }

    fprintf (stderr, "ending someFunction\n");

    return;
}
