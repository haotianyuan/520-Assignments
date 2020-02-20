#include "random_process.h"

using namespace elma;

void RandomProcess::update() {
      double r = ((double) rand() / (RAND_MAX));
      std:: cout<< "value: "<< r<< std::endl;
      channel("link").send(r);
}
