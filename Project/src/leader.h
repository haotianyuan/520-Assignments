#ifndef __LEADER_AGENT__H
#define __LEADER_AGENT__H 

#include "enviro.h"
#include <string>
#include <math.h>

namespace {

    using namespace enviro;

    class MovingForward : public State, public AgentInterface {
        public:
        void entry(const Event& e) {}

        //go forward with the given velocity
        void during() { 
            track_velocity(4,0);
            if ( sensor_value(0) < 10 ) {
                emit(Event(tick_name));
            }            
        }
        void exit(const Event& e) {}
        void set_tick_name(std::string s) { tick_name = s; }
        std::string tick_name;
    };

    class Rotating : public State, public AgentInterface {
        public:
        void entry(const Event& e) { rate = rand() % 2 == 0 ? 2 : -2; }

        //once the robot get stuck, rotate the robot with the random direction
        void during() { 
            track_velocity(0,rate); 
            if ( sensor_value(0) > 10 ) {
                emit(Event(tick_name));
            }
        }
        void exit(const Event& e) {}
        double rate;
        void set_tick_name(std::string s) { tick_name = s; }
        std::string tick_name;        
    };

    class LeaderController : public StateMachine, public AgentInterface {

        public:
        LeaderController() : StateMachine() {

            set_initial(moving_forward);
            tick_name = "tick_" + std::to_string(rand()%1000); // use an agent specific generated 
                                                               // event name in case there are 
                                                               // multiple instances of this class
            add_transition(tick_name, moving_forward, rotating);
            add_transition(tick_name, rotating, moving_forward);
            moving_forward.set_tick_name(tick_name);
            rotating.set_tick_name(tick_name);

        }

        MovingForward moving_forward;
        Rotating rotating;
        std::string tick_name;

    };

    class Leader : public Agent {

        public:
        Leader(json spec, World& world) : Agent(spec, world) {
            add_process(wc);
        }

        LeaderController wc;

    };

    DECLARE_INTERFACE(Leader);

}

#endif