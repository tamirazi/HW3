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
        string command = tasks.front();
        tasks.pop();
        if(command == "refuel"){
            Port *p = dynamic_cast<Port*>(Model::getInstance().getPortByName(destinationName));
            if(p){
                setFuel(getFuel() + p->getMake_per_hours());
            } else
                cerr << "Patrol playCommand Error to get port pointer" << endl;

        }

    }else{
        if(!missions.empty()){//there is another mission
            //get the highest priority from vector
            string command = getCommandByPriority();
            goToDestination(command);
        } else return;
    }
}

void Patrol::update() {
    cout << "Patrol update"<<endl;
    playCommand();
    if(ship_status == Docked) {//arrive in Port
        //if the ship visited all the ports

        int t = timer % 3;
        switch (t) {
            //1st step the ship gas in port--------------------------------------------------------------------
            case 0: {
                Port *p = Model::getInstance().getPortByName(destinationName);
                if (p) {
                    tasks.push("refuel");
                } else
                    cout << "Patrol update : Port dynamic cast failed" << endl;
                timer++;
                break;
            }

                //2nd step no activity-----------------------------------------------------------------------------
            case 1:
                timer++;
                break;
                //3rd step calculate the nearst port from this location (check if the ship visited that port before)
            case 2:
                //building command for mission vector
                stringstream ss;
                //string portName = find_the_nearst_port(location , ports);
                ss << "destination " << "portName" << " " << getSpeed();
                missions.push_back(ss.str());
                timer++;
                break;
        }
    }
}//update the ship missions

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
