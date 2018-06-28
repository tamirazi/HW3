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

    if(!missions.empty()){//
        //get the highest priority from vector
        string command = getCommandByPriority();
        goToDestination(command);
        if(isArrived()){
            tasks.clear();
            calculateTasks();
            missions.pop_back();
        }
    }else if(!tasks.empty() && ship_status == Docked){
        string command = tasks.back();
        tasks.pop_back();
        if(command == "refuel"){
            Port *p = dynamic_cast<Port*>(Model::getInstance().getPortByName(destinationName));
            if(p){
                setFuel(getFuel() + p->getMake_per_hours());
            } else
                cerr << "Patrol playCommand Error to get port pointer" << endl;

        }else if(command != "nothing"){
            goToDestination(command);
        }

    }

}

void Patrol::update() {
    cout << "Patrol update"<<endl;
    playCommand();
    if(isArrived()){
        dockAtPort();
    }
}//update the ship missions

void Patrol::calculateTasks() {
    //get the first port here we calculate all the task to do next
    vector<string> allPorts = Model::getInstance().getAllPorts();

    while(allPorts.size() > 1){
        //calculate next port by distance
        string nextPort = findNextPort(allPorts);
        auto iter = find(allPorts.begin() , allPorts.end() , nextPort);
        allPorts.erase(iter);
        stringstream ss;

        //building command to next destination
        ss << "destination " << nextPort << " " << getSpeed();

        tasks.push_front("refuel");
        tasks.push_front("nothing");
        tasks.push_front(ss.str());
    }

    //now allPorts vector left with the starting port only
    string lastPort = allPorts.front();
    allPorts.clear();
    stringstream ss;
    ss << "destination " << lastPort << " " << getSpeed();
    tasks.push_front(ss.str());




}

string Patrol::findNextPort(vector<string>& portsLeft) {

    map<double , string , greater<double> > distances;

    for (int i = 0; i <portsLeft.size() ; ++i) {
        if(portsLeft[i] != destinationName){
            Port *p = dynamic_cast<Port*>(Model::getInstance().getPortByName(portsLeft[i]));
            double  dis = distance(getLocation() , p->getLocation());
            distances.insert(make_pair(dis , p->getName()));
        }
    }
    auto it = distances.end();
    it--;
    string ans = it->second;
    return ans;


}

const string Patrol::getCommandByPriority() {
    return missions.begin().operator*();
}

bool Patrol::isArrived() {
    if(getLocation().x == getDestination().x && getLocation().y == getDestination().y)
        return true;
    return false;
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
