/** @file storesim.cpp
* @mainpage Project 7 (Queue ADT)
* @author Saharath Kleips
* @version 1.00
* @brief This program simulates the flow of customers through a line in a store.
* @details The specifications of this project match those of the book C++ Data
* Structures - A Laboratory Course (3rd Edition) Project 7. The shell of this
* program have been modified form the book mentioned above.
*/ 

//
// HEADER FILES ////////////////////////////////////////////////////////////////
//

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include "config.h"

#if LAB7_TEST1
#   include "QueueLinked.cpp"
#else
#   include "QueueArray.cpp"
#endif

using namespace std;

//
// MAIN FUNCTION IMPLEMENTATION ////////////////////////////////////////////////
//
int main ()
{
    #if LAB7_TEST1
        QueueLinked<int> custQ;
    #else
        QueueArray<int> custQ;
    #endif

    // SIMULATION VARIABLES //
    int simLength = 0;      //Length of Simulation (Simulated Minutes)
    int minute = 0;         //Current Minute
    int timeArrived = 0;    //Time dequeued customer arrived
    int waitTime = 0;       //How long dequeued customer waited
    int totalServed = 0;    //Total customers served
    int totalWait = 0;      //Total waiting time
    int maxWait = 0;        //Longest wait
    int numArrivals = 0;    //Number of new arrivals
    srand(7);           //Seed random number
    int rng = 0;            //Random number place holder

    cout << endl << "Enter the length of time to run the simulator : ";
    cin >> simLength;

    while(minute != simLength)
    {
        // Increment Step //
        minute++;
        numArrivals = 0;

        // Serve Customer //
        if (!custQ.isEmpty())
        {
            timeArrived = custQ.dequeue();
            totalServed++;

            // Calculate Wait Times //
            waitTime = minute - timeArrived;
            totalWait += waitTime;
            if(waitTime > maxWait)
                maxWait = waitTime;
        }

        // Add Customers //
        rng = rand() % 4;
        switch (rng)
        {
            case 0:
                //Do not add any customers
                break;
            case 1:
                custQ.enqueue(minute);
                numArrivals++;
                break;
            case 2:
                custQ.enqueue(minute);
                custQ.enqueue(minute);
                numArrivals += 2;
                break;
            case 3:
                //Do not add any customers
                break;
            default:
                //Do not add any customers
                break;
        }

        // Display Updates //
        //cout << endl;
        //cout << "Current Minute           : " << minute << endl;
        //cout << "Time Dequeued Arrived    : " << timeArrived << endl;
        //cout << "Dequeued Customer Waited : " << waitTime << endl;
        //cout << "Number of new arrivals   : " << numArrivals << endl;
        // Apparently I don't need the above....
    }

    // Display Results //
    cout << endl;
    cout << "Customers served : " << totalServed << endl;
    cout << "Average wait     : " << setprecision(2) 
        << double(totalWait)/totalServed << endl;
    cout << "Longest wait     : " << maxWait << endl;
}