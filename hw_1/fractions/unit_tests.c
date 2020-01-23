#include "fraction.h"
#include "gtest/gtest.h"

namespace {

    TEST(Fractions, Basics) {
        Fraction a = (Fraction) { 2, 3 },
                 b = (Fraction) { 4, 5 };
        EXPECT_EQ(add(a,b).num,22);
        EXPECT_EQ(add(a,b).den,15);
        EXPECT_EQ(multiply(a,b).num,8);
        EXPECT_EQ(multiply(a,b).den,15);
    }

    TEST(Fractions, Reduce) {
        Fraction a = (Fraction) { 21, 33 };
        EXPECT_EQ(reduce(a).num,7);
        EXPECT_EQ(reduce(a).den,11);

        Fraction b = (Fraction) { 111, 111 };
        EXPECT_EQ(reduce(b).num,1);
        EXPECT_EQ(reduce(b).den,1);

        Fraction c = (Fraction) { 0, 33 };
        EXPECT_EQ(reduce(c).num,0);
        EXPECT_EQ(reduce(c).den,33);

        Fraction d = (Fraction) { -100, 200 };
        EXPECT_EQ(reduce(d).num,-1);
        EXPECT_EQ(reduce(d).den,2);

        Fraction e = (Fraction) { -9, -81 };
        EXPECT_EQ(reduce(e).num,1);
        EXPECT_EQ(reduce(e).den,9);

        Fraction f = (Fraction) { 88, -880 };
        EXPECT_EQ(reduce(f).num,1);
        EXPECT_EQ(reduce(f).den,-10);
    }

}
