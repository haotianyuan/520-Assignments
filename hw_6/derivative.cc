#include "derivative.h"


using namespace elma;
using std::vector;

void Derivative::update() {
    //_value=1;
    if(channel("link").nonempty() ) {
         if(channel("link").size()<2){
            _queue.push_back(channel("link").latest());
         }
         else{
             if(_queue.size()<2){
                _queue.push_back(channel("link").latest());
           }else{
               _queue.pop_front();        
               _queue.push_back(channel("link").latest());
           }
         }
    }
}

double Derivative::value(){
    if(channel("link").size()<2){
        return 0;
    }
    double v1=_queue.front();
    _queue.pop_front();    
    double v2=_queue.front();
    //std::cout << v1 << "\n"; 
    //std::cout << v2 << "\n"; 

    return (v2-v1)/delta();
}