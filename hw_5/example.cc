#include <stdlib.h>
#include "example.h"
#include <exception>
using namespace std;

using std::vector;

example::example(){}

vector<double> example::sort_by_magnitude(vector<double> &v){
    std::sort(v.begin(),v.end(),
    [](double a,double b){
        return(abs(a)<abs(b));
    }
    );
    return v;    
}

vector<int> example::primes(int n){
    vector<int> res;
    for(int i=2;i<=n;i++){
        if(i>7){
            if(i%7 != 0 && i%5 !=0 && i%3 != 0 && i%2!=0){
                res.push_back(i);
            }
        }
        else if(i>5){
             if(i%5 !=0 && i%3 != 0 && i%2!=0){
                res.push_back(i);
            }
        }
        else if(i>3){
             if(i%3 != 0 && i%2!=0){
                res.push_back(i);
            }
        } 
        else if(i>2){
             if(i%2!=0){
                res.push_back(i);
            }
        }else{
            res.push_back(i);
        }
    }
    return res;

}

vector<tuple<int,int>> example::twins(vector<int> nums){
    vector<tuple<int,int>> res;
    for(int i=0;i<nums.size()-1;i++){
        if(abs(nums[i]-nums[i+1])==2){
            tuple<int,int> temp=make_tuple(nums[i],nums[i+1]);
            res.push_back(temp);
        }
    }
    return res;
}