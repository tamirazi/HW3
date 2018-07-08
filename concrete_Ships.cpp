//
// Created by bar on 6/26/2018.
//
#include "Model.h"
//---------------------------------------------------------------------------------------Freighter
void Freighter::playCommand() {
    if(!missions.empty()){
        //do the task
        if(thereIsErgentRequest()){
            rightKnowMission = getCommandByPriority();
            stringstream ss(rightKnowMission);
            string command;
            ss >> command;
            if(command == "destination"){
                tasks.clear();
                string portName;
                ss >> portName;
                insertSubMissionsToTasks(portName);
            }
        }else{
            //keep doing what you are doing
        }
    }
}
const string Freighter::getCommandByPriority() {
    auto iter = missions.begin();
    string line;
    for(;iter != missions.end(); ++iter){
        stringstream ss(iter.operator*());
        string command;
        ss >> command;
        if(command == "position" ||  command == "course" ||  command == "destination"){
            line = iter.operator*();
            iter = missions.erase(iter);
            return line.c_str();
        }
    }
    return line;
}
bool Freighter::thereIsErgentRequest() {

    auto iter = missions.end();
    bool gotACommand = false;
    string line;

    while(iter != missions.begin()){
        --iter;
        stringstream ss(iter.operator*());
        string command;
        ss >> command;
        if(!gotACommand && (command == "position" ||  command == "course" ||  command == "destination")){
            gotACommand =true;
        }else if(command == "position" ||  command == "course" ||  command == "destination"){
            iter = missions.erase(iter);
        }
    }
    return gotACommand;
}


void Freighter::insertSubMissionsToTasks(const string & name) {

    auto iter = missions.begin();
    for(;iter != missions.end() ; ++iter){
        stringstream ss(iter.operator*());
        string tmp;
        ss>> tmp;
        ss>> tmp;
        if(tmp == name || tmp == "refuel")
            tasks.push_back(iter.operator*());
    }
}

bool Freighter::thereIsDock() {
    auto iter = tasks.begin();
    bool ans = false;
    for(;iter != tasks.end();++iter){
        stringstream ss(iter.operator*());
        string tmp;
        ss>> tmp;
        if(tmp == "dock_at"){
            iter = tasks.erase(iter);
            ans = true;
        }
    }
    return ans;
}

void Freighter::dockedMissions() {
    auto iter = tasks.begin();
    stringstream ss(iter.operator*());
    string mission;
    ss >> mission;
    if(mission == "load_at"){
        containers_on = containers_capacity;
    }
    if(mission == "unload_at"){
        int howMany;
        ss >> howMany;
        containers_on = containers_on-howMany;
    }
    if(mission == "refuel"){
        int howMany;
        ss >> howMany;
        Port* port = Model::getInstance().getPortByName(destinationName);
        if( port->getCapicity() > FREIGHTER_FUEL_CAPACITY - fuel){
            fuel = FREIGHTER_FUEL_CAPACITY;
            port->setCapacity(FREIGHTER_FUEL_CAPACITY - fuel);
        }else{
            fuel = fuel+port->getCapicity();
            port->setCapacity(0);
        }
    }
    tasks.erase(iter);
}

//---------------------------------------------------------------------------------------Patrol
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
    }else if(!tasks.empty()){
        string command = tasks.back().c_str();
        if(command == "refuel"){
            Port *p = (Model::getInstance().getPortByName(destinationName));
            if(p){
                setFuel(getFuel() + p->getMake_per_hours());
                tasks.pop_back();
            } else
                cerr << "Patrol playCommand Error to get port pointer" << endl;

        }else if(command != "nothing"){
            goToDestination(command);
            if(isArrived()){
                tasks.pop_back();
            }
        }else if(command == "nothing")
            tasks.pop_back();

    }else if(tasks.empty() && destinationName != "" ){
        cout << getName() << " " << "just finish full circle patrol in all ports" << endl;
    }

}
void Patrol::update() {
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
    string lastPort = allPorts.front().c_str();
    allPorts.clear();
    stringstream ss;
    ss << "destination " << lastPort << " " << getSpeed();
    tasks.push_front(ss.str());




}
string Patrol::findNextPort(vector<string>& portsLeft) {

    map<double , string , greater<double> > distances;

    for(unsigned int i = 0; i <portsLeft.size() ; ++i) {
        if(portsLeft[i] != destinationName){
            Port *p = Model::getInstance().getPortByName(portsLeft[i]);
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
//---------------------------------------------------------------------------------------Cruiser
void Cruiser::playCommand() {//play Cruiser command
    if(!missions.empty()){
        string line = getCommandByPriority();
        if(line != ""){
            goOnCourse(line);
        }

    }else { return;}
}
const string Cruiser::getCommandByPriority() {//get the most highest priority from queue
    //the only command to do is an on course command and the last one from them
    //if there is no such command the ship will do as before... if there is one the ship started to sail on a new course/
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
        }else if(command != "attack"){
            iter = missions.erase(iter);
        }
    }
    return line.c_str();
}
void Cruiser::attackShips() {//attack all ships in cruiser vector if there is any
    //the attack succed if the attacking force is greater than the resistance of the defender
    //otherwise the attack fails in any cae the defender will stop sailing.
    vector<string>::iterator iter = missions.begin();
    for(;iter != missions.end() ; ++iter){
        stringstream ss(iter.operator*());
        string command;
        ss >>command;
        if(command == "attack"){
            cout << iter.operator*() << endl;
            string shipName;
            ss >> shipName;
            Ship* ship = Model::getInstance().getShipByName(shipName);
            if(!ship){
                cout << "the Ship was not allocated" << endl;
                exit(1);
            }
            if(PossibleToAttack(getLocation(),ship->getLocation(),attacking_range)){
                if(ship->getType() == "Freighter"){
                    Freighter* freig = Model::getInstance().getFreighterShipByName(shipName);
                    if(!freig){
                        cout << "the Freighter was not allocated" << endl;
                        exit(1);
                    }
                    if(attacking_force > freig->getResistance()){
                        cout << "succeed attacking Freighter" << endl;
                        attacking_force += 1;
                        freig->setContainers_capacity(0);
                        freig->stop();
                    }else{
                        cout << "the Freighter Wins" << endl;
                        attacking_force -= 1;
                        freig->stop();
                    }
                }
                if(ship->getType() == "Patrol"){
                    Patrol* patrol = Model::getInstance().getPatrolShipByName(shipName);
                    if(!patrol){
                        cout << "the Patrol was not allocated" << endl;
                        exit(1);
                    }
                    if(attacking_force > patrol->getResistance()){
                        cout << "succeed attacking Patrol" << endl;
                        attacking_force += 1;
                        patrol->setResistance(patrol->getResistance() -1);
                        patrol->stop();
                    }else{
                        cout << "the Patrol Wins" << endl;
                        attacking_force -= 1;
                        patrol->setResistance(patrol->getResistance() +1);
                        patrol->stop();
                    }
                }
                iter = missions.erase(iter);
                --iter;
            }
        }
    }
}