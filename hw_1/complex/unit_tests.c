#include "complex.h"
#include "gtest/gtest.h"

namespace {

    TEST(Complex, add) {
        Complex a = (Complex) { 2, 3 },
                b = (Complex) { 4, 5 };
        EXPECT_EQ(add(a,b).real,6);
        EXPECT_EQ(add(a,b).im,8);
    
        Complex c = (Complex) { -2, 6 },
                d = (Complex) { -4, 5 };
        EXPECT_EQ(add(c,d).real,-6);
        EXPECT_EQ(add(c,d).im,11);

        Complex e = (Complex) { 0, 7 },
                f = (Complex) { 13, 7 };
        EXPECT_EQ(add(e,f).real,13);
        EXPECT_EQ(add(e,f).im,14);
    }

    TEST(Complex, negate) {
        Complex a = (Complex) { 2, 3 },
                b = (Complex) { 4, 5 };
        EXPECT_EQ(negate(a,b).real,-2);
        EXPECT_EQ(negate(a,b).im,-2);
    
        Complex c = (Complex) { -2, 6 },
                d = (Complex) { -4, 5 };
        EXPECT_EQ(negate(c,d).real,2);
        EXPECT_EQ(negate(c,d).im,1);

        Complex e = (Complex) { 0, 7 },
                f = (Complex) { 13, 7 };
        EXPECT_EQ(negate(e,f).real,-13);
        EXPECT_EQ(negate(e,f).im,0);
    }

    TEST(Complex, multiple) {
        Complex a = (Complex) { 3, 2 },
                b = (Complex) { 1, 7 };
        EXPECT_EQ(multiply(a,b).real,-11);
        EXPECT_EQ(multiply(a,b).im,23);
    
        Complex c = (Complex) { 1, 1 },
                d = (Complex) { 1, 1 };
        EXPECT_EQ(multiply(c,d).real,0);
        EXPECT_EQ(multiply(c,d).im,2);

        Complex e = (Complex) { 3, 4 },
                f = (Complex) { 0, 1 };
        EXPECT_EQ(multiply(e,f).real,-4);
        EXPECT_EQ(multiply(e,f).im,3);
    }
    
    TEST(Complex, magnitude) {
        Complex a = (Complex) { -4, -3 };
        EXPECT_EQ(magnitude(a),5);
    
        Complex b = (Complex) { 6, 8 };
        EXPECT_EQ(magnitude(b),10);
    }
}
