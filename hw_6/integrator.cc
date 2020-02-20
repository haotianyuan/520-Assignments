#include "integrator.h"
using namespace elma;
using std::vector;

void Integrator::update() {
    if(channel("link").nonempty() ) {
        temp=channel("link").latest();
        //std::cout << delta() << "\n"; 
        double temp_integrator=delta() * temp;
        _queue.push_back(temp_integrator);
    }
}

double Integrator::value(){
    int size=_queue.size();
    for(int i=0;i<size;i++){
        std::cout << "value: " << _queue.front() << "\n";
        _value=_value+_queue.front();
        _queue.pop_front();
    }

    return _value;
}