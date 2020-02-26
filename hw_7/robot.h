#ifndef _ROBOT_H
#define _ROBOT_H

#include <iostream>
#include <chrono>
#include <json/json.h>
#include "elma/elma.h"
#include <string>
#include <vector>

using namespace elma;
using nlohmann::json; 

class RobotState : public State {
    public:
        RobotState(std::string name) : State(name){}

        void entry(const Event& e) {}
        void during() {}
        void exit(const Event& e) {}
};

class Robot : public StateMachine {
    public:
        Robot(std::string name) : StateMachine(name){
            set_initial(closed_off);
            add_transition("start", closed_off, Wander);
            add_transition("intruder detected", Wander, Make_Noise);
            add_transition("reset", Evade, Make_Noise);
            add_transition("proximity warning", Make_Noise, Evade);
            add_transition("battery low", Evade, Find_Recharge_Station);
            add_transition("battery full", Recharge, Wander);
            add_transition("found recharge station", Find_Recharge_Station, Recharge);
            add_transition("reset", Make_Noise, Wander); 
            add_transition("battery low", Wander, Find_Recharge_Station);
        }
   
    private:
        RobotState closed_off = RobotState("closed_off");
        RobotState Wander = RobotState("Wander");
        RobotState Make_Noise = RobotState("Make Noise");
        RobotState Evade = RobotState("Evade");
        RobotState Find_Recharge_Station = RobotState("Find Recharge Station");
        RobotState Recharge = RobotState("Recharge");

};

class BetterStateMachine : public StateMachine {
    public:
        BetterStateMachine(std::string name) : StateMachine(name){
            //lname=name;
        }

        json to_json() const{
            json res;
            string name= const_cast<BetterStateMachine*>(this)->name();
            vector<string> states;
            vector<map<string, string>> trans;
            
            for(int i = 0 ; i < _transitions.size(); i++){
                map<string, string> temp;
                temp["from"] = _transitions[i].from().name();
                temp["to"] = _transitions[i].to().name();
                temp["when"] = _transitions[i].event_name();
                trans.push_back(temp);
                states.push_back(_transitions[i].from().name());
                states.push_back(_transitions[i].to().name());
            }
            res["name"] = name;
            res["states"] = states;
            res["transitions"] = trans;

            return res;
        };
   
    private:
        //std::string lname;
};



#endif