/** @file Timer.cpp
* @mainpage Project 13 (Timer ADT)
* @author Saharath Kleips
* @version 1.00
* @brief This program will be used to measure the length of time between two
* events.
* @details The specifics of this project match those of the book C++ Data
* Structures - A Laboratory Course (3rd Edition) Project 13. This implementation
* is designed to compare the performance of search and sorting routines, and the
* performance implications of C++ constructs. This implementation may however be
* used to measure the time between two points in a program.
*/

//
// HEADER FILES ////////////////////////////////////////////////////////////////
//

#include "Timer.h"

//
// TIMER FUNCTION IMPLEMENTATIONS //////////////////////////////////////////////
//

/** The default constructor
* that initializes the internal timer values, so that the timer is ready to
* measure time.
*/
Timer::Timer()
{
    timerWasStarted = false;
}

/** Starts the timer.
* Marks the beginning of a time interval.
* @pre The clock function is working correctly.
* @throw The clock is not working properly.
*/
void Timer::start() throw (runtime_error)
{
    if(timerWasStarted == true)
        throw runtime_error("start() while timer was started");
    gettimeofday(&beginTime, NULL);
    timerWasStarted = true;
}

/** Stops the timer.
* Marks the end of a time interval.
* @pre The beginning of a time interval has been marked.
* @throw The clock has not been started.
*/
void Timer::stop() throw (logic_error)
{
    if(timerWasStarted == false)
        throw logic_error("stop() while timer was stopped");
    struct timeval t;
    gettimeofday(&t, NULL);
    duration.tv_sec = (t.tv_sec - beginTime.tv_sec);
    duration.tv_usec = (t.tv_usec - beginTime.tv_usec);
    timerWasStarted = false;
}

/** Returns the length of the time interval in seconds.
* @pre The beginning and end of a time interval have been marked.
* @throw The clock has not been started and/or stopped.
* @return The length of time interval in seconds.
* @error Investigate the weird reason why I can't simply return the arithmetic
* in d, but instead have to place it into a variable first.
*/
double Timer::getElapsedTime() const throw (logic_error)
{
    if(timerWasStarted == true)
        throw logic_error("getElapsedTime() while timer was started");
    double d = (duration.tv_sec * 1000000) + duration.tv_usec;
    d = d / 1000000;
    return d;
}