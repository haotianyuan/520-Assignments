#include "gtest/gtest.h"
#include <iostream>
#include <ratio>
#include <cctype>
#include "stopwatch.h"
#include "random_process.h"
#include "filter.h"
#include "elma/elma.h"
#include "integrator.h"
#include "derivative.h"
#include <thread>
#define SLEEP std::this_thread::sleep_for(std::chrono::milliseconds(1500))
namespace {
    using namespace std;


    TEST(stopwatch, start) {
        stopwatch w; // should set the stopwatch to 0 seconds
        w.start(); 
        SLEEP;
        w.stop();    
        std::cout << w.get_seconds() << "\n"; // about 1.5
        SLEEP;
        std::cout << w.get_seconds() << "\n"; // still about 1.5
        w.start(); 
        SLEEP;
        w.stop();    
        std::cout << w.get_seconds() << "\n"; // about 3.0
        w.reset();
        std::cout << w.get_seconds() << "\n"; // 0.0
        w.start(); 
        SLEEP;
        w.stop();    
        std::cout << w.get_minutes() << "\n"; // about 0.025
        SLEEP;
        std::cout << w.get_milliseconds() << "\n"; // about 1500
        w.start(); 
        SLEEP;
        w.stop();    
        std::cout << w.get_nanoseconds() << "\n"; // about 3e+9
        w.reset();//0
    }

    TEST(q2, random_process) {
        elma::Manager m;
        RandomProcess r("random numbers");
        Filter f("filter");
        elma::Channel link("link");
        m.schedule(r, 1_ms)
        .schedule(f, 1_ms)
        .add_channel(link)
        .init()
        .run(10_ms);
        std::cout << f.value() << "\n"; 
    }

    TEST(q3, integrator) {
        elma::Manager m;
        RandomProcess r("random numbers");
        Integrator f("integrator");
        elma::Channel link("link");
        m.schedule(r, 1_ms)
        .schedule(f, 1_ms)
        .add_channel(link)
        .init()
        .run(10_ms);
        std::cout << f.value() << "\n"; 
    }

    TEST(q4, derivative) {
        elma::Manager m;
        RandomProcess r("random numbers");
        Derivative f("derivative");
        elma::Channel link("link");
        m.schedule(r, 1_ms)
        .schedule(f, 1_ms)
        .add_channel(link)
        .init()
        .run(10_ms);
        std::cout << f.value() << "\n"; 
    }


}
