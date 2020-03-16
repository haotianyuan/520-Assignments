#ifndef __BLOCK2_AGENT__H
#define __BLOCK2_AGENT__H 

#include "enviro.h"

using namespace enviro;

class block2Controller : public Process, public AgentInterface {

    public:
    block2Controller() : Process(), AgentInterface() {}

    void init() {}
    void start() {}
    void update() {}
    void stop() {}

};

//Class inherit from Agent to set up the physics of the agent
class block2 : public Agent {
    public:
    block2(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    block2Controller c;
};

DECLARE_INTERFACE(block2)

#endif