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
            string command = getCommandByPriorety();
            goToDestination(command);
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
            float speed;
            ss  >> command;
            if(command == "destination"){
                ss >> portName;
                ss >> speed;
                Port* p = Model::getInstance().getPortByName(portName);
                if(p) {
                    this->setDestination(p->getLocation());
                    setLocation(prograss(getLocation(),p->getLocation(),speed));
                    setFuel(getFuel()-getConsumption());
                    movingToDestintion(p->getLocation(),speed);
                }else { cerr << "port null" << endl;}

            }

        } else return;
    }
}

const string &Patrol::getCommandByPriorety() {
    return missions.begin().operator*();
}

void Cruiser::playCommand() {

}

const string &Cruiser::getCommandByPriorety() {
    return missions.begin().operator*();
}


const string &Freighter::getCommandByPriorety() {
    vector<string>::iterator iter = missions.begin();
    for(;iter != missions.end() ; ++iter){
    }
    return missions.begin().operator*();
}
