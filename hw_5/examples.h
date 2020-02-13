#ifndef __EXAMPLES_H
#define __EXAMPLES_H

#include <string>
#include <tuple>
#include <map>
#include <vector>
#include <functional>

using namespace std;

class examples {

  public:
    examples();
    vector<double> sort_by_magnitude(vector<double> &v);
    vector<int> primes(int n);
    vector<tuple<int,int>> twins(vector<int> nums);
  private:

   

};

#endif

