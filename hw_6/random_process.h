#ifndef RANDOM_PROCESS_H
#define RANDOM_PROCESS_H

#include <vector>
#include <string>
#include <iostream>
#include <stdlib.h>

#include "elma/elma.h"

using std::string;
using std::vector;
using namespace elma;

class RandomProcess : public Process {
  public: 
    RandomProcess(string name) : Process(name) {}
    void init() {}
    void start() {}
    void update();
    void stop() {}
  private:
  
};


#endif