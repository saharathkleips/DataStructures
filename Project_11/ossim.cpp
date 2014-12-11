//--------------------------------------------------------------------
//
//  Laboratory 11, Programming Exercise 1                     ossim.cs
//
//  (Shell) Operating system task scheduling simulation
//
//--------------------------------------------------------------------

// Simulates an operating system's use of a priority queue to regulate
// access to a system resource (printer, disk, etc.).

#include <iostream>
#include <cstdlib>
#include "PriorityQueue.cpp"

using namespace std;

//--------------------------------------------------------------------
//
// Declaration for the task data struct
//

struct TaskData
{
    int getPriority () const
        { return priority; }     // Returns the priority. Needed by the heap.

    int priority,                // Task's priority
        arrived;                 // Time when task was enqueued

};


//--------------------------------------------------------------------

int main ()
{
    PriorityQueue<TaskData, int, Less<int> > taskPQ;   // Priority queue of tasks
    TaskData task;               // Task
    int simLength,               // Length of simulation (minutes)
        minute,                  // Current minute
        numPtyLevels,            // Number of priority levels
        numArrivals,             // Number of new tasks arriving
        j;                       // Loop counter

    // Seed the random number generator
    srand( 7 );

    cout << endl << "Enter the number of priority levels : ";
    cin >> numPtyLevels;

    cout << "Enter the length of time to run the simulator : ";
    cin >> simLength;

    for ( minute = 0 ; minute < simLength ; minute++ )
    {
        // Dequeue the first task in the queue (if any).
	// Your code here
        if(!taskPQ.isEmpty())
        {
            task = taskPQ.dequeue();
            cout << "At " << minute << " dequeued : ";
            cout << task.priority << " " << task.arrived << " " <<
                (minute - task.arrived) << endl;
        }

        // Determine the number of new tasks and add them to
        // the queue.
	// Your code here
        switch(rand() % 4)
        {
            case 1:
                if(!taskPQ.isFull())
                {
                    task.priority = rand() % numPtyLevels;
                    task.arrived = minute;
                    taskPQ.enqueue(task);
                }
                break;
            case 2:
                for(j = 0; j < 2 && !taskPQ.isFull(); j++)
                {
                    task.priority = rand() % numPtyLevels;
                    task.arrived = minute;
                    taskPQ.enqueue(task);
                }
                break;
        }

    }

    return 0;
}

