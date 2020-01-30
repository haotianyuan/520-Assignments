#include <math.h>
#include <float.h> /* defines DBL_EPSILON */
#include "dynamic_array.h"
#include "gtest/gtest.h"

#define X 1.2345

namespace {

    TEST(DynamicArray, CreateAndDestroy) {
        DynamicArray * a = DynamicArray_new();
        DynamicArray_destroy(a);
    }

    TEST(DynamicArray, DeathTests) {
        DynamicArray * a = DynamicArray_new();
        ASSERT_DEATH(DynamicArray_pop(a), ".*Assertion.*");
        ASSERT_DEATH(DynamicArray_pop_front(a), ".*Assertion.*");
        DynamicArray_destroy(a);
        ASSERT_DEATH(DynamicArray_size(a), ".*Assertion.*");
    }    

    TEST(DynamicArray, SmallIndex) {
        DynamicArray * da = DynamicArray_new();
        ASSERT_EQ(DynamicArray_size(da),0);
        DynamicArray_set(da, 0, -X);        
        DynamicArray_set(da, 3, X);
        ASSERT_EQ(DynamicArray_size(da),4);
        ASSERT_EQ(DynamicArray_get(da,0), -X);
        ASSERT_EQ(DynamicArray_get(da,3), X);
        DynamicArray_destroy(da);
    }

    TEST(DynamicArray, BigIndex) {
        DynamicArray * da = DynamicArray_new();
        DynamicArray_set(da, 8, X);
        ASSERT_EQ(DynamicArray_get(da,8), X);
        DynamicArray_destroy(da);              
    }

    TEST(DynamicArray, ReallyBig) {
        DynamicArray * da = DynamicArray_new();
        DynamicArray_set(da, 400, X);
        DynamicArray_set(da, 200, X/2);        
        ASSERT_EQ(DynamicArray_get(da,200), X/2);
        ASSERT_EQ(DynamicArray_get(da,400), X);
        DynamicArray_destroy(da);              
    }  

    TEST(DynamicArray, Push) {
        DynamicArray * da = DynamicArray_new();
        double x = 0;
        while ( x < 10 ) {
            DynamicArray_push(da, x);  
            x += 0.25;
        }
        ASSERT_EQ(DynamicArray_size(da),40);
        printf("Push test Intermediate Result: %s\n", 
               DynamicArray_to_string(da));
        while ( DynamicArray_size(da) > 0 ) {
            DynamicArray_pop(da);
        }
        ASSERT_EQ(DynamicArray_size(da),0);
        DynamicArray_destroy(da);          
    }

    TEST(DynamicArray, PushFront) {
        DynamicArray * da = DynamicArray_new();
        double x = 0;
        while ( x < 10 ) {
            DynamicArray_push_front(da, x);  
            x += 0.25;
        }
        ASSERT_EQ(DynamicArray_size(da),40);
        while ( DynamicArray_size(da) > 0 ) {
            DynamicArray_pop_front(da);
        }
        ASSERT_EQ(DynamicArray_size(da),0);
        DynamicArray_destroy(da);          
    } 

    TEST(DynamnicArray,ToString) {
        DynamicArray * da = DynamicArray_new();
        double x = 1.0;
        while ( x <= 5 ) {
            DynamicArray_push(da, x);  
            x += 1.0;
        }
        char * str = DynamicArray_to_string(da);
        printf("ToString Example: %s\n", str);
        ASSERT_STREQ(
            str,
            "[1.00000,2.00000,3.00000,4.00000,5.00000]"
        );
        DynamicArray_destroy(da);
        free(str);
    }

    TEST(DynamicArray, Pop) {
        DynamicArray * da = DynamicArray_new();
        double x;
        DynamicArray_push(da, X);  
        DynamicArray_push(da, X);  
        x = DynamicArray_pop(da);  
        ASSERT_EQ(DynamicArray_size(da),1);
        ASSERT_EQ(x,X);
        ASSERT_EQ(DynamicArray_get(da,1), 0.0);
        DynamicArray_destroy(da);          
    }

    TEST(DynamicArray, Map) {
        DynamicArray * t = DynamicArray_new(),
                     * y;
        double s = 0.0;
        for ( int i=0; i<628; i++ ) {
            DynamicArray_set(t, i, s);
            s = s + 0.1;
        }
        y = DynamicArray_map(t,sin);
        for (int i=0; i<DynamicArray_size(t); i++) {
            ASSERT_NEAR(
                DynamicArray_get(y,i),sin(0.1*i), 0.0001
            );
        }
        DynamicArray_destroy(t);    
        DynamicArray_destroy(y);                    
    }         

    TEST(DynamicArray, Min) {
        DynamicArray * da = DynamicArray_new();
        DynamicArray_push(da, 0);
        DynamicArray_push(da, 1);
        DynamicArray_push(da, 0);
        DynamicArray_push(da, 9);
        DynamicArray_push(da, 18);
       
        ASSERT_EQ(DynamicArray_size(da),5);
        
        ASSERT_EQ(DynamicArray_min(da),0);
        DynamicArray_destroy(da);          
    }

    TEST(DynamicArray, Max) {
        DynamicArray * da = DynamicArray_new();
        DynamicArray_push(da, 0);
        DynamicArray_push(da, 1);
        DynamicArray_push(da, -9);
        DynamicArray_push(da, 9);
        DynamicArray_push(da, 18);
       
        ASSERT_EQ(DynamicArray_size(da),5);
        
        ASSERT_EQ(DynamicArray_max(da),18);
        DynamicArray_destroy(da);          
    }

    TEST(DynamicArray, Mean) {
        DynamicArray * da = DynamicArray_new();
        DynamicArray_push(da, 0);
        DynamicArray_push(da, 1.8);
        DynamicArray_push(da, -1.8);
        DynamicArray_push(da, 3.6);
        DynamicArray_push(da, -10);
       
        ASSERT_EQ(DynamicArray_size(da),5);
        
        ASSERT_EQ(DynamicArray_mean(da),-1.28);
        DynamicArray_destroy(da);          
    }

     TEST(DynamicArray, Median1) {
        DynamicArray * da = DynamicArray_new();
        
        DynamicArray_push(da, 1);
        DynamicArray_push(da, 2);
        DynamicArray_push(da, 3);
        DynamicArray_push(da, 4);
        DynamicArray_push(da, 5);
        DynamicArray_push(da, 6);
        DynamicArray_push(da, 7);
        DynamicArray_push(da, 0);
        DynamicArray_push(da, -1);
        
        ASSERT_EQ(DynamicArray_size(da),9);
        
        ASSERT_EQ(DynamicArray_median(da),3);
        DynamicArray_destroy(da);          
    }

    TEST(DynamicArray, Median2) {
        DynamicArray * da = DynamicArray_new();
        DynamicArray_push(da, 2);
        DynamicArray_push(da, 3);
        DynamicArray_push(da, 4);
        DynamicArray_push(da, 5);
        DynamicArray_push(da, 6);
        DynamicArray_push(da, 7);
        DynamicArray_push(da, 0);
        DynamicArray_push(da, -1);

        ASSERT_EQ(DynamicArray_size(da),8);
        
        ASSERT_EQ(DynamicArray_median(da),3.5);
        DynamicArray_destroy(da);          
    }

     TEST(DynamicArray, Sum) {
        DynamicArray * da = DynamicArray_new();
        DynamicArray_push(da, 2);
        DynamicArray_push(da, -3);
        DynamicArray_push(da, 4);
        DynamicArray_push(da, 9);
        DynamicArray_push(da, 0);
        DynamicArray_push(da, -22);

        ASSERT_EQ(DynamicArray_size(da),6);
        
        ASSERT_EQ(DynamicArray_sum(da),-10);
        DynamicArray_destroy(da);          
    }

    TEST(DynamicArray, First) {
        DynamicArray * da = DynamicArray_new();
        DynamicArray_push(da, 2);
        DynamicArray_push(da, -3);

        ASSERT_EQ(DynamicArray_size(da),2);
        
        ASSERT_EQ(DynamicArray_first(da),2);
        DynamicArray_destroy(da);          
    }

    TEST(DynamicArray, Last) {
        DynamicArray * da = DynamicArray_new();
        DynamicArray_push(da, 2);
        DynamicArray_push(da, -3);
        DynamicArray_push(da, 4);
        DynamicArray_push(da, 9);
        DynamicArray_push(da, 0);
        DynamicArray_push(da, 2);

        ASSERT_EQ(DynamicArray_size(da),6);
        
        ASSERT_EQ(DynamicArray_last(da),2);
        DynamicArray_destroy(da);          
    }

    TEST(DynamicArray, Copy) {
        DynamicArray * da = DynamicArray_new();
                     
        DynamicArray_push(da, 2);
        DynamicArray_push(da, -3);
        DynamicArray_push(da, 4);
        DynamicArray_push(da, 9);
        DynamicArray_push(da, 0);
        DynamicArray_push(da, 2);
        DynamicArray * b = DynamicArray_copy(da);
        ASSERT_EQ(DynamicArray_size(da),6);
        ASSERT_EQ(DynamicArray_size(b),6);
        ASSERT_EQ(DynamicArray_get(b,0),2);
        ASSERT_EQ(DynamicArray_get(b,1),-3);
        ASSERT_EQ(DynamicArray_get(b,2),4);
        ASSERT_EQ(DynamicArray_get(b,3),9);
        ASSERT_EQ(DynamicArray_get(b,4),0);
        ASSERT_EQ(DynamicArray_get(b,5),2);
        DynamicArray_destroy(da);        
        DynamicArray_destroy(b);     
    }

    TEST(DynamicArray, Cop1) {
        DynamicArray * da = DynamicArray_new();
                     
        DynamicArray * b = DynamicArray_copy(da);
        ASSERT_EQ(DynamicArray_size(da),0);
        ASSERT_EQ(DynamicArray_size(b),0);
        DynamicArray_destroy(da);        
        DynamicArray_destroy(b);     
    }

    TEST(DynamicArray, Range) {
        DynamicArray * da = DynamicArray_range(0, 10, 2);
                     
        
        ASSERT_EQ(DynamicArray_size(da),6);

        ASSERT_EQ(DynamicArray_get(da,0),0);
        ASSERT_EQ(DynamicArray_get(da,1),2);
        ASSERT_EQ(DynamicArray_get(da,2),4);
        ASSERT_EQ(DynamicArray_get(da,3),6);
        ASSERT_EQ(DynamicArray_get(da,4),8);
        ASSERT_EQ(DynamicArray_get(da,5),10);
        
        DynamicArray_destroy(da);        
          
    }

    TEST(DynamicArray, Range1) {
        DynamicArray * da = DynamicArray_range(0,-3,1);
                     
        
        ASSERT_EQ(DynamicArray_size(da),0);
        

        DynamicArray_destroy(da);        
          
    }

    TEST(DynamicArray, Range2) {
        DynamicArray * da = DynamicArray_range(0,1,1.1);
                     
        
        ASSERT_EQ(DynamicArray_size(da),1);
        

        DynamicArray_destroy(da);        
          
    }

    TEST(DynamicArray, Range3) {
        DynamicArray * da = DynamicArray_range(0,26,6);
                     
        ASSERT_EQ(DynamicArray_size(da),5);
        ASSERT_EQ(DynamicArray_get(da,0),0);
        ASSERT_EQ(DynamicArray_get(da,1),6);
        ASSERT_EQ(DynamicArray_get(da,2),12);
        ASSERT_EQ(DynamicArray_get(da,3),18);
        ASSERT_EQ(DynamicArray_get(da,4),24);
        

        DynamicArray_destroy(da);        
          
    }

    TEST(DynamicArray, Range4) {
        DynamicArray * da = DynamicArray_range(0,-12,-5);
                     
        ASSERT_EQ(DynamicArray_size(da),3);
        ASSERT_EQ(DynamicArray_get(da,0),0);
        ASSERT_EQ(DynamicArray_get(da,1),-5);
        ASSERT_EQ(DynamicArray_get(da,2),-10);
        
        DynamicArray_destroy(da);        
          
    }

    TEST(DynamicArray, Concat) {
        DynamicArray * a = DynamicArray_range(0,10,5);
        DynamicArray * b = DynamicArray_range(10,20,5);
        DynamicArray * c = DynamicArray_concat(a,b);       

        ASSERT_EQ(DynamicArray_size(c),6);
        ASSERT_EQ(DynamicArray_get(c,0),0);
        ASSERT_EQ(DynamicArray_get(c,1),5);
        ASSERT_EQ(DynamicArray_get(c,2),10);
        ASSERT_EQ(DynamicArray_get(c,3),10);
        ASSERT_EQ(DynamicArray_get(c,4),15);
        ASSERT_EQ(DynamicArray_get(c,5),20);
        
        DynamicArray_destroy(a);   
        DynamicArray_destroy(b);  
        DynamicArray_destroy(c);       
          
    }

    TEST(DynamicArray, Take) {
        DynamicArray * a = DynamicArray_range(0,20,5);
        DynamicArray * b = DynamicArray_take(a,4);

        ASSERT_EQ(DynamicArray_size(b),4);
        ASSERT_EQ(DynamicArray_get(b,0),0);
        ASSERT_EQ(DynamicArray_get(b,1),5);
        ASSERT_EQ(DynamicArray_get(b,2),10);
        ASSERT_EQ(DynamicArray_get(b,3),15);
        
        DynamicArray_destroy(a);   
        DynamicArray_destroy(b);       
    }

    TEST(DynamicArray, Take1) {
        DynamicArray * a = DynamicArray_range(0,20,5);
        DynamicArray * b = DynamicArray_take(a,-10);

        ASSERT_EQ(DynamicArray_size(b),10);
        ASSERT_EQ(DynamicArray_get(b,0),20);
        ASSERT_EQ(DynamicArray_get(b,1),15);
        ASSERT_EQ(DynamicArray_get(b,2),10);
        ASSERT_EQ(DynamicArray_get(b,3),5);
        ASSERT_EQ(DynamicArray_get(b,4),0);
        ASSERT_EQ(DynamicArray_get(b,5),0);
        ASSERT_EQ(DynamicArray_get(b,6),0);
        ASSERT_EQ(DynamicArray_get(b,7),0);
        ASSERT_EQ(DynamicArray_get(b,8),0);
        ASSERT_EQ(DynamicArray_get(b,9),0);
        
        DynamicArray_destroy(a);   
        DynamicArray_destroy(b);       
    }

    TEST(DynamicArray, Take2) {
        DynamicArray * a = DynamicArray_range(0,20,5);
        DynamicArray * b = DynamicArray_take(a,0);

        ASSERT_EQ(DynamicArray_size(b),0);
        
        DynamicArray_destroy(a);   
        DynamicArray_destroy(b);       
    }













}