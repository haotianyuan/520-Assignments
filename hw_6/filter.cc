#include "filter.h"


using namespace elma;
using std::vector;

void Filter::update() {
    //_value=1;
    if(channel("link").nonempty() ) {
           //std::cout << channel("link").latest() << "\n";
           //std::cout << channel("link").size() << "\n";
           if(_queue.size()<10){
                _queue.push_back(channel("link").latest());
                //temp=channel("link").latest();
                //_value=_value+temp;
           }else{
               //temp=_queue.front();
               _queue.pop_front();
                //_value=_value-temp;            
               _queue.push_back(channel("link").latest());
               //temp=channel("link").latest();
               //_value=_value+temp; 
           }

            //std::cout << _queue.size() << "\n";

           //_value=10;
    }
}

double Filter::value(){
    int size=_queue.size();
    for(int i=0;i<size;i++){
        //std::cout << "queue: " <<_queue.front() << "\n";
        _value=_value+_queue.front();
        //std::cout << "result: " <<_value << "\n";
        _queue.pop_front();
    }
    
    //std::cout << "size: " <<size << "\n";

    return _value/size;
}

