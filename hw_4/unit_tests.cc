#include <math.h>
#include <float.h> /* defines DBL_EPSILON */
#include <assert.h>
#include "typed_array.h"
#include "point.h"
#include "gtest/gtest.h"
#include "complex.h"

namespace {

    TEST(TypedArray, Construction) {
        TypedArray<Point> b;
        b.set(0, Point(1,2,3));
        b.set(1, Point(2,3,4));
        b.set(20, Point(3,4,5));
        EXPECT_EQ(b.get(0).x, 1);
        EXPECT_EQ(b.get(1).y, 3);
        EXPECT_EQ(b.get(20).z, 5);
    }

    TEST(TypedArray, Defaults) {
        TypedArray<Point> x;
        Point& y = x.get(3);
        std::cout << x << "\n";
        EXPECT_DOUBLE_EQ(y.magnitude(), 0.0);
    }

    TEST(TypedArray, Matrix) {

        TypedArray<TypedArray<double>> m;

        for (int i=0; i<3; i++) {
            for (int j=0; j<3; j++) {
                m.get(i).set(j,3*i+j);
            }
        }

        std::cout << m << "\n"; 

        for (int i=0; i<3; i++) {
            for (int j=0; j<3; j++) {
                EXPECT_DOUBLE_EQ(m.get(i).get(j),3*i+j);
            }
        }

    }

    TEST(TypedArray,CopyElementsInSet1) {
        TypedArray<Point> b;
        Point p(1,2,3);
        b.set(0, p);
        p.x = 4;
        EXPECT_DOUBLE_EQ(b.get(0).x, 1);
    }

    TEST(TypedArray,CopyElementsInSet2) {
        TypedArray<TypedArray<double>> m;
        TypedArray<double> x;
        x.set(0,0);
        m.set(0,x);
        x.set(0,-1);
        EXPECT_DOUBLE_EQ(m.get(0).get(0),0.0); // If set didn't make a copy
                                               // then we would expect m[0][0]
                                               // to be x[0], which we changed 
                                               // to -1.
    } 

    TEST(TypedArray, Push) {
        TypedArray<Point> b;
        b.push(Point(1,2,3));
        b.push(Point(2,3,4));
        b.push(Point(3,4,5));
        b.push(Point(1,2,3));
        b.push(Point(2,3,4));
        b.push(Point(3,4,5));
        b.push(Point(1,2,3));
        b.push(Point(2,3,4));
        b.push(Point(3,4,5));
        b.push(Point(3,4,5));
        b.push(Point(3,4,10));
        b.push(Point(9,4,10));
        b.push(Point(8,123,10));
        EXPECT_EQ(b.get(0).x, 1);
        EXPECT_EQ(b.get(1).y, 3);
        EXPECT_EQ(b.get(2).z, 5);
        EXPECT_EQ(b.get(10).z, 10);
        EXPECT_EQ(b.get(12).y, 123);
        EXPECT_EQ(b.size(),13);
    }   

    TEST(TypedArray, Pop) {
        TypedArray<Point> b;
        b.push(Point(1,2,3));
        b.push(Point(2,3,4));
        b.push(Point(3,4,5));
        EXPECT_EQ(b.size(),3);
        b.pop();
        EXPECT_EQ(b.size(),2);
        EXPECT_EQ(b.get(1).x,2);
    }   

    TEST(TypedArray, push_Front) {
        TypedArray<Point> b;
        b.push(Point(1,2,3));
        b.push(Point(2,3,4));
        b.push(Point(3,4,5));
        EXPECT_EQ(b.size(),3);
        b.push_front(Point(0,1,1));
        b.push_front(Point(0,1,1));
        b.push_front(Point(0,1,1));
        b.push_front(Point(0,1,1));
        b.push_front(Point(0,1,1));
        b.push_front(Point(0,1,1));
        b.push_front(Point(0,1,1));
        b.push_front(Point(111,1111,111));
        EXPECT_EQ(b.size(),11);
        EXPECT_EQ(b.get(0).x,111);
    }   
    TEST(TypedArray, push_Front1) {
        TypedArray<Point> b;
        b.push_front(Point(0,1,1));
        EXPECT_EQ(b.size(),1);
        EXPECT_EQ(b.get(0).x,0);
    }

    TEST(TypedArray, pop_front) {
        TypedArray<Point> b;
        b.push(Point(1,2,3));
        b.push(Point(2,3,4));
        b.push(Point(3,4,5));

        EXPECT_EQ(b.size(),3);
        b.pop_front();
        EXPECT_EQ(b.get(0).x,2);
        EXPECT_EQ(b.size(),2);
    }

    TEST(TypedArray, concat) {
        TypedArray<int> a;
        a.set(0,0);
        a.set(1,1);
        TypedArray<int> b=a.concat(a).concat(a);

        EXPECT_EQ(b.size(),6);
        EXPECT_EQ(b.get(0),0);
        EXPECT_EQ(b.get(2),0);
        EXPECT_EQ(b.get(3),1);
    }

    TEST(TypedArray, concat1) {
        TypedArray<int> a;
        a.set(0,0);
        a.set(1,1);
        TypedArray<int> b;
        b.push(2);
        b.push(3);
        b.push(4);
        TypedArray<int> c=a.concat(b);

        EXPECT_EQ(c.size(),5);
        EXPECT_EQ(c.get(0),0);
        EXPECT_EQ(c.get(4),4);
    }

    TEST(TypedArray, reverse) {
        TypedArray<int> a;
        TypedArray<int> b=a.reverse();

        EXPECT_EQ(a.size(),0);
        EXPECT_EQ(b.size(),0);
    }

    TEST(TypedArray, reverse1) {
        TypedArray<int> a;
        a.push(1);
        a.push(2);
        a.push(3);
        TypedArray<int> b=a.reverse();
        EXPECT_EQ(a.size(),3);
        EXPECT_EQ(b.size(),3);
        EXPECT_EQ(b.get(0),3);
        EXPECT_EQ(b.get(1),2);
        EXPECT_EQ(b.get(2),1);
    }

    TEST(TypedArray, operator) {
        TypedArray<int> a;
        a.push(1);
        a.push(2);
        a.push(3);
        //TypedArray<int> b=a.reverse();
        TypedArray<int> b = a + a + a;
        EXPECT_EQ(b.size(),9);
        EXPECT_EQ(b.get(0),1);
        EXPECT_EQ(b.get(1),2);
        EXPECT_EQ(b.get(2),3);
        EXPECT_EQ(b.get(3),1);
        EXPECT_EQ(b.get(4),2);
        EXPECT_EQ(b.get(5),3);
    }

    TEST(TypedArray, operator1) {
        TypedArray<int> a;
        a.push(1);
        a.push(2);
        a.push(3);

        TypedArray<int> b=a.reverse();
        TypedArray<int> c = a + b;
        //std::cout << a.get(0) << "\n";
        //std::cout << a.get(1) << "\n";
        //std::cout << a.get(2) << "\n";
        EXPECT_EQ(c.size(),6);
        EXPECT_EQ(c.get(0),3);
        EXPECT_EQ(c.get(1),2);
        EXPECT_EQ(c.get(2),1);
        EXPECT_EQ(c.get(3),3);
        EXPECT_EQ(c.get(4),2);
        EXPECT_EQ(c.get(5),1);
    }


    // Complex 
    TEST(Examples,Complex) {
        Complex x(1,2), y(3);
    }

    template<typename T>
    int compare(const T& x, const T& y) {
        if ( x < y ) {
            return -1;
        } else if ( y < x ) {
            return 1;
        } else {
            return 0;
        }
    }    

    TEST(Examples,Templates) {
        EXPECT_EQ(compare(1.0, 2.0), -1);
        EXPECT_EQ(compare(Complex(5,4), Complex(-3,4)), 1);
    }

    TEST(Examples,Real) {
        Complex x(1,2);
        EXPECT_EQ(x.real(),1);
        
        Complex y(100);
        EXPECT_EQ(y.real(),100);
    }

    TEST(Examples,imaginary) {
        Complex x(1,2);
        EXPECT_EQ(x.imaginary(),2);
        
        Complex y(100);
        EXPECT_EQ(y.imaginary(),0);
    }

    TEST(Examples,plus) {
        Complex x(1,2);
        Complex y(3,4);
        Complex z=x+y;
        EXPECT_EQ(z.real(),4);
        EXPECT_EQ(z.imaginary(),6);
    }

    TEST(Examples,multiple) {
        Complex x(3,2);
        Complex y(1,4);
        Complex z=x*y;
        EXPECT_EQ(z.real(),-5);
        EXPECT_EQ(z.imaginary(),14);
    }

    TEST(Examples,equal) {
        Complex x(3,2);
        Complex y(1,4);
        bool check=(x==y);
        EXPECT_EQ(check,false);
    }

    TEST(Examples,equal1) {
        Complex x(3,2);
        Complex y(3,2);
        bool check=(x==y);
        EXPECT_EQ(check,true);
    }

    TEST(Examples,conjugate) {
        Complex x(3,2);
        Complex y=x.conjugate();
        
        EXPECT_EQ(x.real(),3);
        EXPECT_EQ(x.imaginary(),2);
    }










    














}