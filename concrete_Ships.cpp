//
// Created by bar on 6/26/2018.
//
#include "Model.h"

void Freighter::playCommand() {
    if(!tasks.empty()){
        //do the task
    }else{
        if(!missions.empty()){//there is another mission
            //get the highest priority from vector
            string line = missions.begin().operator*().c_str();
            cout << line << endl;
            stringstream ss(line);
            string command;
            string portName;
            int speed;
            ss  >> command;
            if(command == "destination"){
                ss >> portName;
                ss >> speed;
                Port* p = Model::getInstance().getPortByName(portName);
                if(p) {
                    this->setDestination(p->getLocation());
                    setLocation(prograss(getLocation(),p->getLocation(),speed));
                }else { cerr << "port null" << endl;}

            }

        } else return;
    }
}

void Patrol::playCommand() {
    if(!tasks.empty()){
        //do the task
    }else{
        if(!missions.empty()){//there is another mission
            //get the highest priority from vector
            string line = missions.begin().operator*().c_str();
            cout << line << endl;
            stringstream ss(line);
            string command;
            string portName;
            double speed;
            ss  >> command;
            if(command == "destination"){
                ss >> portName;
                ss >> speed;
                Port* p = Model::getInstance().getPortByName(portName);
                if(p) {
                    this->setDestination(p->getLocation());
                    setLocation(prograss(getLocation(),p->getLocation(),speed));
                }else { cerr << "port null" << endl;}

            }

        } else return;
    }
}

void Cruiser::playCommand() {

}

const string& Freighter::getRatedCommand() {
    return missions.begin().operator*();
}
