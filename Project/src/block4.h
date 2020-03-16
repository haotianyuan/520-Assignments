#ifndef __BLOCK4_AGENT__H
#define __BLOCK4_AGENT__H 

#include "enviro.h"

using namespace enviro;

class block4Controller : public Process, public AgentInterface {

    public:
    block4Controller() : Process(), AgentInterface() {}

    void init() {}
    void start() {}
    void update() {}
    void stop() {}

};

//Class inherit from Agent to set up the physics of the agent
class block4 : public Agent {
    public:
    block4(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    block4Controller c;
};

DECLARE_INTERFACE(block4)

#endif