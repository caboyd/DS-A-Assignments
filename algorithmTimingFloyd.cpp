// This program determines the running time of an algorithm whose
// life is very short. A two-step measurement technique is used.
// The first step determines the number of times an empty loop can
// executed in one second. Dividing one second by the number of
// times the loop executed provides the estimated time for one
// iteration of the empty loop. In the second step, the algorithm
// is placed in the loop and the loop is executed the number of
// times determined in the first step. The time it takes to do
// step two is divided by the number of times determined in the
// first step. This provides the estimated time for one iteration
// of the loop when the execution of the algorithm is included.
// The difference between the time determined in step two and the
// time determined in step one is the estimated elapsed time for
// one run of the algorithm.

#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <sys/time.h>
#include "floydShortestPath.h"
#include <string>


using namespace std;

int main()
{
    // The timeval type is a struct defined in sys/time.h.
    timeval startTime;
    timeval endTime;

    // Number of times to execute do loop in Phase 1.
    int repetitions;

    // Used in Phase 1 to count number of times empty do loop executes.
    long withoutCount;

    // Used in Phase 2 to count number of times do loop executes.
    long withCount;

    // Holds the number of times empty do loop executes in Phase 1.
    vector <long> countPerRepetition;

    // Estimated elapsed time of one iteration of empty do loop
    // in Phase 1.
    double elapsedTimeWithoutAlgorithm;

    // Estimated elapsed time of one iteration of do loop in Phase 2.
    double elapsedTimeWithAlgorithm;

    // Estimated elapsed time of algorithm.
    double elapsedTime;

    // "Length" of algorithm.
    long maxIterations;

    cout << fixed << setprecision (12);

    cout << endl;

	cout << "Floyd's algorithm" << endl;
    cout << "Enter number of repetitions: ";
    cin >> repetitions;

// Phase 1: Algorithm not included in timing measurements.

    countPerRepetition.reserve (repetitions);

    // Determine the number of times the do loop can be executed in
    // approximately one second without the algorithm in the loop.
    // Repeat repetitions times.
    while (countPerRepetition.size () < repetitions)
    {
        withoutCount = 0;

        // Get the start time. NULL means return the current time.
        gettimeofday (&startTime, NULL);

        do
        {
            withoutCount ++;

            // Algorithm that you are timing is removed for this phase.
			
			//This will only initialize
			FloydShortestPath f("graph.txt");
            

            // Get the end time. NULL means return the current time.
            gettimeofday (&endTime, NULL);

            // Compute the elapsed time in microseconds (i.e., end - start).
            // Need to do the second and microsecond parts of the timeval
            // struct separately.

            // Calculates the seconds and converts to microseconds.
            elapsedTime = (endTime.tv_sec - startTime.tv_sec) * 1000000.0;

            // Calculates the microseconds.
            if (endTime.tv_usec > startTime.tv_usec)
            {
                elapsedTime += endTime.tv_usec - startTime.tv_usec;
            }
            else if (endTime.tv_usec < startTime.tv_usec)
            {
                elapsedTime += endTime.tv_usec;
                elapsedTime += (1000000.0 - startTime.tv_usec);
            }

            // This is here because it is required in the Phase 2 do loop.
            if (withoutCount == withoutCount)
            {
                ;
            }

        // Continue as long as elapsed time is less than one second.
        } while (elapsedTime < 1000000.0);

        // Record the count for this repetition
        countPerRepetition.push_back (withoutCount);
    }

    sort (countPerRepetition.begin (), countPerRepetition.end ());

    // Print the number of times the "empty" loop was executed.
    withoutCount = countPerRepetition [repetitions / 2];
    cout << "Representative count (without algorithm): " << withoutCount << endl;

    // Divide the elapsed time by 1000 to get the elpased time in milliseconds.
    elapsedTimeWithoutAlgorithm = 1000.0 / withoutCount;

    // Print the running time without the algorithm.
    cout << "Representative running time (without algorithm): " << elapsedTimeWithoutAlgorithm << " ms" << endl;

// Phase 2: Algorithm included in timing measurements.

    // Now run the algorithm in the do loop withoutCount times and determine
    // the elapsed time.

    withCount = 0;

    // Get the start time. NULL means return the current time.
    gettimeofday (&startTime, NULL);

    do
    {
        withCount ++;

        // The algorithm that you want to measure goes here. As you
        // can see, the current algorithm is just a simple loop that
        // repeats until the loop counter reaches maxIterations.

		//This will only initialize
		FloydShortestPath f("graph.txt");
		//This will be the timed function
		f.search();

        // This is here because it is required in the Phase 1 do loop.
        gettimeofday (&endTime, NULL);
        elapsedTime = (endTime.tv_sec - startTime.tv_sec) * 1000000.0;
        if (endTime.tv_usec > startTime.tv_usec)
        {
            elapsedTime += endTime.tv_usec - startTime.tv_usec;
        }
        else if (endTime.tv_usec < startTime.tv_usec)
        {
            elapsedTime += endTime.tv_usec;
            elapsedTime += 1000000.0 - startTime.tv_usec;
        }

        // If the algorithm has been executed withoutCount times, end
        // the do loop.
        if (withCount == withoutCount)
        {
            break;
        }

    // Continue until the algorithm has been executed withoutCount times.
    } while (1);

    // Get the end time. NULL means return the current time.
    gettimeofday (&endTime, NULL);

    // Compute the elapsed time in microseconds (i.e., end - start).
    // Need to do the second and microsecond parts of the timeval
    // struct separately.

    // Calculates the seconds and converts to microseconds.
    elapsedTime = (endTime.tv_sec - startTime.tv_sec) * 1000000.0;

    // Calculates the microseconds.
    if (endTime.tv_usec > startTime.tv_usec)
    {
        elapsedTime += endTime.tv_usec - startTime.tv_usec;
    }
    else if (endTime.tv_usec < startTime.tv_usec)
    {
        elapsedTime += endTime.tv_usec;
        elapsedTime += 1000000.0 - startTime.tv_usec;
    }

    // Divide the elapsed time by withCount to obtain the average.
    elapsedTimeWithAlgorithm = (elapsedTime / (double) withCount);

    // Divide the elapsed time by 1000 to get the elpased time in milliseconds.
    elapsedTimeWithAlgorithm = elapsedTimeWithAlgorithm / 1000.0;
    cout << "Representative running time (with algorithm): " << elapsedTimeWithAlgorithm << " ms" << endl;

// Phase 3: Output estimated running time of the algorithm.

    cout << "Estimated running time: " << elapsedTimeWithAlgorithm - elapsedTimeWithoutAlgorithm << " ms" << endl;
  
    return 0;
}
