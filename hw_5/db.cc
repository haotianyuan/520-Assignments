#include <exception>
#include "db.h"

using namespace std;

DB::DB() : _next_key(0) {}

DB &DB::insert(const string name, double mass, double distance) {
   
   for(int i=0;i<=_next_key;i++){
       auto e = _data.find(i);
       if ( e != _data.end() ) {
           if(NAME(find(i))== name){
               throw runtime_error("Name already exists");
           }
       }
   }


    int key = _next_key++;
    _data[key] = make_tuple(name, mass, distance);
    return *this;

}

DB &DB::drop(int key) {

    auto e = _data.find(key);

    if ( e != _data.end() ) {
        _data.erase (e);
    }

    return *this;
}

DB::Row DB::to_row(int key, const DB::Value value) const {
    return make_tuple(key, get<0>(value), get<1>(value), get<2>(value));
}

DB::Row DB::find(int key) const {

    auto e = _data.find(key);

    if ( e != _data.end() ) {
        return to_row(key,e->second);
    } else {
        throw runtime_error("Could not find an entry with the given key");
    }

}

vector<DB::Row> DB::where(function<bool(const DB::Row)> f) const {

    vector<Row> rows;

    for( auto [key, value] : _data ) {
        auto row = to_row(key,value);
        if ( f(row) == true ) {
            rows.push_back(row);
        }
    }

    return rows;

}

DB::Row DB::find_by_name(const string name) const{
    for(int i=0;i<=_next_key;i++){
       auto e = _data.find(i);
       if ( e != _data.end() ) {
           if(NAME(find(i))== name){
               return to_row(i,e->second);
           }
       }
   }
   throw runtime_error("Could not find row by name");
}

DB &DB::create_test_data(int n){
    for(int i=0;i<n;i++){
        double mass = (double)rand() / RAND_MAX;
        mass = 0.01 + mass * (1000 - 0.01);

        double distance = (double)rand() / RAND_MAX;
        distance = 0.01 + distance * (10000000 - 0.1);

        auto randchar = []() -> char
        {
        const char charset[] =
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";
            const size_t max_index = (sizeof(charset) - 1);
            return charset[ rand() % max_index ];
        };
        string str(8,0);
        generate_n( str.begin(), 8, randchar );
        insert(str,mass,distance);
    }
     return *this;
}

int DB::size() const{
    return _next_key;
}

double DB::accumulate(function<double(const Row)> f) const{
    double sum=0;
    for(auto[key,value]: _data){
        auto row=to_row(key,value);
        sum+=f(row);
    }
    return sum;
}


double DB::average_mass() const{
    double mass=0;
    for(int i=0;i<=_next_key;i++){
       auto e = _data.find(i);
        if ( e != _data.end() ) {
            mass+=MASS(find(i));
       }
      // mass+=MASS(find(i));
   }
   return mass/size();
}

double DB::average_distance() const{
    double distance=0;
    for(int i=0;i<=_next_key;i++){
       auto e = _data.find(i);
        if ( e != _data.end() ) {
            distance+=DISTANCE(find(i));
       }
      // mass+=MASS(find(i));
   }
   return distance/size();
}

