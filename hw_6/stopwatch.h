#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <chrono>

using namespace std::chrono;


class stopwatch{
    typedef std::chrono::duration<int,std::milli> milliseconds_type;
    typedef std::chrono::duration<double,std::ratio<1,1>> seconds_type;
    typedef std::chrono::duration<int,std::nano> nanoseconds_type;
    public:
        stopwatch(){}
        void start();             
        void stop();             
        void reset();              

        double get_minutes();      
        double get_seconds();      
        double get_milliseconds(); 
        double get_nanoseconds();  
    private:
        high_resolution_clock:: time_point _begin;
        high_resolution_clock:: time_point _end;
        high_resolution_clock:: time_point _zero; 
        duration<double> _duration;
};

#endif