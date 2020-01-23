#include "solutions.h"
#include <stdlib.h>

int running_total (int a ) {
    static int count=0;
    count+=a;
    return count;
}

void reverse_in_place(int a[],int len){
    int start=0;
    int end=len-1;
    int temp;
    while (start < end) 
    { 
        temp = a[start];    
        a[start] = a[end]; 
        a[end] = temp; 
        start++; 
        end--; 
    }    
}

int * reverse(int a[],int len){
    int * res = (int *) calloc(len, sizeof(int));
    int index=len-1;
    for(int i=0;i<len;i++){
        res[i]=a[index];
        index--;
    }
    return res;
}

int num_instances(int a[],int len,int num){
    int res=0;
    for(int i=0;i<len;i++){
        if(a[i]==num){
            res++;
        }
    }
    return res;
}

Point * map(Point a[],int len,Point (*f) (Point)){
    Point * res = (Point *) calloc(len, sizeof(Point));
    for(int i=0;i<len;i++){
        res[i]=f(a[i]);
    }
    return res;
}