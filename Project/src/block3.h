#ifndef __BLOCK3_AGENT__H
#define __BLOCK3_AGENT__H 

#include "enviro.h"

using namespace enviro;

class block3Controller : public Process, public AgentInterface {

    public:
    block3Controller() : Process(), AgentInterface() {}

    void init() {}
    void start() {}
    void update() {}
    void stop() {}

};

//Class inherit from Agent to set up the physics of the agent
class block3 : public Agent {
    public:
    block3(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    block3Controller c;
};

DECLARE_INTERFACE(block3)

#endif