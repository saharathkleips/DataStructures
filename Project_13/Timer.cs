// Timer.cpp

#ifndef TIMER_CPP
#define TIMER_CPP

#include "Timer.h"

Timer::Timer() : beginTime(0), duration(0) {
}

void Timer::start() throw (runtime_error) {
    beginTime = clock();
    if( beginTime == (clock_t)-1 ) {
	throw runtime_error("clock() returned -1. Serious problem. Can't run timer.");
    }
}

void Timer::stop() throw (logic_error){
    if( beginTime == (clock_t)-1 ) {
	throw logic_error("Timer was never started.");
    }
    duration = clock() - beginTime;
}

double Timer::getElapsedTime() const {
    // Place your code here
}

#endif	//#ifndef TIMER_CPP
