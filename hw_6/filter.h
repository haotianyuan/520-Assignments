#ifndef FILTER_H
#define FILTER_H

#include <vector>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <deque>          // std::deque
#include <list>           // std::list
#include <queue>          // std::queue

#include "elma/elma.h"

using std::string;
using std::vector;
using std::queue;
using namespace elma;

class Filter : public Process {
    public: 
        Filter(string name) : Process(name) {
            _value=0;
            _queue.clear();
            temp=0;
        }
        void init() {}
        void start() {}
        void update();
        double value();
        void stop() {}
    private:
        double _value;
        deque<double> _queue;
        double temp;
    };


#endif