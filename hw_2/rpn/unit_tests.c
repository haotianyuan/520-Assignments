#include "gtest/gtest.h"
#include "rpn.h"

namespace {

    TEST(HW2,RPN_BASICS) {
        rpn_init();
        rpn_push(0.5);
        rpn_push(2.0);
        rpn_push(1.0);
        rpn_add();
        rpn_multiply();
        rpn_negate();
        ASSERT_EQ(rpn_pop(),-1.5);
        ASSERT_EQ(rpn_error(), OK);
        rpn_free();
    }

    TEST(HW2,RPN_ERRORS) {
        
        rpn_push(0.5);
        ASSERT_EQ(rpn_error(), NOT_INITIALIZED_ERROR);
        rpn_free();

        rpn_pop();
        ASSERT_EQ(rpn_error(), NOT_INITIALIZED_ERROR);
        rpn_free();

        rpn_add();
        ASSERT_EQ(rpn_error(), NOT_INITIALIZED_ERROR);
        rpn_free();

        rpn_multiply();
        ASSERT_EQ(rpn_error(), NOT_INITIALIZED_ERROR);
        rpn_free();

        rpn_negate();
        ASSERT_EQ(rpn_error(), NOT_INITIALIZED_ERROR);                                
        rpn_free();

        rpn_init();
        rpn_pop();
        ASSERT_EQ(rpn_error(), POP_ERROR);
        rpn_free();

        rpn_init();
        rpn_negate();
        ASSERT_EQ(rpn_error(), UNARY_ERROR);
        rpn_free();

        rpn_init();
        rpn_push(1);
        rpn_add();
        ASSERT_EQ(rpn_error(), BINARY_ERROR);
        rpn_free();

        rpn_init();
        rpn_push(1);
        rpn_multiply();
        ASSERT_EQ(rpn_error(), BINARY_ERROR);  
        rpn_free();

        rpn_init();
        rpn_push(DBL_MAX);
        rpn_push(DBL_MAX);
        rpn_add();
        ASSERT_EQ(rpn_error(), OVERFLOW_ERROR);
        rpn_free();

        rpn_init();
        rpn_push(DBL_MAX);
        rpn_push(DBL_MAX);
        rpn_negate();
        rpn_multiply();
        ASSERT_EQ(rpn_error(), OVERFLOW_ERROR);
        rpn_free();        

    }    

    TEST(HW2,RPN_ADVANCED1) {
        rpn_init();
        rpn_push(0.5);
        rpn_push(1.0);
        rpn_push(0.0);  
        rpn_div();
        ASSERT_EQ(rpn_error(), DIVIDE_BY_ZERO_ERROR);
        rpn_free();
    }

    TEST(HW2,RPN_ADVANCED2) {
        rpn_init();
        rpn_push(6.4);
        rpn_push(1.6);
        rpn_push(0.8);  
        rpn_div();
        rpn_div();
        ASSERT_EQ(rpn_pop(),3.2);
        ASSERT_EQ(rpn_error(), OK);
        rpn_free();
    }

    TEST(HW2,RPN_SIZE) {
        rpn_init();
        for(int i=0;i<150;i++){
            rpn_push(1.0);
        }
        //rpn_show();
        /*rpn_push(1.0);
        rpn_push(2.0);
        
        for(int i=0;i<120;i++){
            rpn_pop();
        }
        ASSERT_EQ(rpn_pop(), 1.0);

        ASSERT_EQ(rpn_error(),OK);*/


        rpn_free();
    }




}
