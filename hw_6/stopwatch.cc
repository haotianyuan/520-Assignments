#include "stopwatch.h"
#include <iostream>
#include <ratio>

using namespace std::chrono;

void stopwatch::start(){
    _begin = high_resolution_clock::now();
}

void stopwatch::stop(){
    _end = high_resolution_clock::now();
    _duration += duration<double>(_end - _begin);
}

void stopwatch::reset(){
    _duration = duration<double>(_zero-_zero);
}

double stopwatch::get_minutes(){
    return _duration.count()/60;
}

double stopwatch::get_seconds(){
    return _duration.count();
}

double stopwatch::get_milliseconds(){
    //return milliseconds_type(_duration.count());
    return _duration.count()*1000;
}

double stopwatch::get_nanoseconds(){
    //return nanoseconds_type(_duration.count());
    return _duration.count()*1000000000;
}



