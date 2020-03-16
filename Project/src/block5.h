#ifndef __BLOCK5_AGENT__H
#define __BLOCK5_AGENT__H 

#include "enviro.h"

using namespace enviro;

class block5Controller : public Process, public AgentInterface {

    public:
    block5Controller() : Process(), AgentInterface() {}

    void init() {}
    void start() {}
    void update() {}
    void stop() {}

};

//Class inherit from Agent to set up the physics of the agent
class block5 : public Agent {
    public:
    block5(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    block5Controller c;
};

DECLARE_INTERFACE(block5)

#endif