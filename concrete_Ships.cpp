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
            string command = getCommandByPriority();
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
                    setLocation(prograssByDestination(getLocation(),p->getLocation(),speed));
                    setFuel(getFuel()-getConsumption());
                    movingToDestintion(p->getLocation(),speed);
                }else { cerr << "port null" << endl;}

            }

        } else return;
    }
}

const string Patrol::getCommandByPriority() {
    return missions.begin().operator*();
}

void Cruiser::playCommand() {
    if(!missions.empty()){
        string line = getCommandByPriority();
        goOnCourse(line);
    }else { return;}
}

const string Cruiser::getCommandByPriority() {
    vector<string>::iterator iter = missions.end();
    bool gotACommand = false;
    string line = "";

    while(iter != missions.begin()){
        --iter;
        stringstream ss(iter.operator*());
        string command;
        ss >> command;
        if(!gotACommand && command == "course"){
            gotACommand =true;
            line = iter.operator*().c_str();
        }else{
            iter = missions.erase(iter);
        }
    }
    return line.c_str();
}

void Cruiser::attackShips() {
    vector<string>::iterator iter = missions.begin();
    for(;iter != missions.end() ; ++iter){
        stringstream ss(iter.operator*());
        string command;
        ss >>command;
        if(command == "attack"){
            string shipName;
            ss >> shipName;
            Ship* ship = Model::getInstance().getShipByName(shipName);
            if(PossibleToAttacck(getLocation(),ship->getLocation(),attacking_range)){
                cout << " it's possible know to attack " << ship->getName() << endl;
                if(ship->getType() == "Freighter"){
                    Freighter* freig = Model::getInstance().getFreighterShipByName(shipName);
                    freig->getResistance();
                }
            }

        }
    }
}


const string Freighter::getCommandByPriority() {
    vector<string>::iterator iter = missions.begin();
    for(;iter != missions.end() ; ++iter){
    }
    return missions.begin().operator*();
}
