#include "gtest/gtest.h"
#include <iostream>
#include <ratio>
#include <cctype>
#include <thread>
#include <robot.h>
#include <assert.h>
#include "elma/elma.h"

namespace {
    using namespace std;


    TEST(robot, 1) {
       Robot robot = Robot("What a very nice robot.");

        Manager m;
        m.schedule(robot, 10_ms)
        .init()
        .start()
        .emit(Event("start"));

        EXPECT_EQ(robot.current().name(), "Wander");
        m.emit(Event("intruder detected"));
        EXPECT_EQ(robot.current().name(), "Make Noise");
        m.emit(Event("proximity warning"));
        EXPECT_EQ(robot.current().name(), "Evade");
        m.emit(Event("battery full"));
        EXPECT_EQ(robot.current().name(), "Evade");      
        m.emit(Event("reset"));
        EXPECT_EQ(robot.current().name(), "Make Noise");   

    }

     TEST(Robot, 1) {

       //BetterStateMachine fsm("toggle switch");
       //json j = fsm.to_json();
        //ASSERT_EQ(j["name"],"toggle switch");
        //ASSERT_EQ(j["states"].size(),5);

       // count << j.dump() << "\n";
       //Robot robot = new robot("123");
       //json j = robot.to_json();
       // count << j.dump() << "\n";

    }

}