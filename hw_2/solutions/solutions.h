#ifndef SOLUTIONS_H
#define SOLUTIONS_H

/*! @file */

typedef struct {
   double x, y, z;
 } Point;

int running_total (int a);
void reverse_in_place(int a[],int len);
int * reverse(int a[],int len);
int num_instances(int a[],int len,int num);
Point * map(Point a[],int len,Point (*f) (Point));
#endif