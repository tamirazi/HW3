//
// Created by tamir on 6/18/18.
//
#include "Ship.h"
#include "Model.h"

Ship::Ship(const string& name ,const string& type,const Point& p ):SimObject(name,type,p),ship_status (Stopped),fuel(0),speed(0){}
void Ship::stop() {//stop the ship and clear the missions vector
    speed = 0;
    ship_status = Stopped;
    missions.clear();
}
void Ship::movingToDestintion(const Point &destination , float newSpeed) {
    ship_status = Moving_to;
    Ship::destination = destination;
    Cartesian_vector cv;
    cv.delta_x = destination.x - getLocation().x;
    cv.delta_y = destination.y - getLocation().y;
    deg = cv;
    speed = newSpeed;
}
//void Ship::movingOnCourse(const Cartesian_vector &angle , float newSpeed) {
//    Ship::angle = angle;
//    speed = newSpeed;
//    ship_status = Moving_on_course;
//}
float Ship::getFuel() const {
    return fuel;
}
void Ship::setFuel(float fuel) {
    Ship::fuel = fuel;
}
double Ship::getSpeed() const {
    return speed;
}
void Ship::setSpeed(float speed) {
    Ship::speed = speed;
}
status Ship::getShip_status() const {
    return ship_status;
}
void Ship::setShip_status(status ship_status) {
    Ship::ship_status = ship_status;
}
void Ship::show_Status() {
    switch(ship_status){
        case Stopped:
            cout << ", Stopped " << endl;
            break;
        case Dead_in_the_water:
            cout <<" Dead in the water"<< endl;
            break;
        case Moving_to:
            cout << ", Moving to " <<getDestinationName() << " on course " << to_degrees(deg.theta) << " deg," << getSpeed() <<  " nm/hr" ;
            break;
        case Moving_on_course:
            cout << " Moving to " << destinationName << " on course " << endl;
            break;
        case Docked:
            cout << " Docked at " << destinationName << endl;
    }
}

void Ship::setSim_obj_dest(SimObject *sim_obj_dest) {
    Ship::sim_obj_dest = sim_obj_dest;
}

void Ship::printMissions(){
    vector<string>::iterator iter = missions.begin();
    for(;iter!= missions.end();++iter){
        cout << iter.operator*() << endl;
    }
}

void Ship::insertMissionToVector(const string &command) {//insert a string that represent a command into a specific ship queue
    missions.push_back(command);
}

void Ship::setLocation(const Point &newLoc) {
    SimObject::location = newLoc;
}

const Point &Ship::getDestination() const {
    return destination;
}

void Ship::setDestination(const Point &destination) {
    Ship::destination = destination;
}

float Ship::getConsumption() const {
    return consumption;
}

const string &Ship::getDestinationName() const {
    return destinationName;
}

void Ship::setDestinationName(const string &destination) {
    destinationName = destination;
}

void Ship::goToDestination(const string& line) {
    cout << line << endl;
    stringstream ss(line);
    string command;
    string portName;
    float speed;
    ss  >> command;
    if(command == "destination") {
        ss >> portName;
        ss >> speed;
        Port *p = Model::getInstance().getPortByName(portName);
        if (p) {
            this->setDestination(p->getLocation());
            setLocation(prograssByDestination(getLocation(), p->getLocation(), speed));
            setDestinationName(p->getName());
            setFuel(getFuel() - getConsumption());
            movingToDestintion(p->getLocation(), speed);
            if(getLocation().x == getDestination().x && getLocation().y == getDestination().y){
                dockAtPort();
            }
        } else { cerr << "port null" << endl; }
    }
}

void Ship::goOnCourse(const string &line) {
    cout << line << endl;
    stringstream ss(line);
    string command;
    double degree;
    float speed;
    ss  >> command;
    if(command == "course") {
        ss >> degree;
        ss >> speed;
        setLocation(prograssByCourse(getLocation(),degree,speed));
    }
}

void Ship::dockAtPort() {
    setShip_status(Docked);
    setSpeed(0);
}

/*void Ship::pharseLineFromVec() {
    string args , portName;
    if(!missions.empty() && !busy){
        busy = true; //after pharse the command the ship will be busy
        string command , name;
        stringstream ss(missions.front());
        missions.pop_front();
        getline(ss , name , ' ');
        getline(ss , command , ' ');
        Ship* s = Model::getInstance().getShipByName(name); //downcast from simObj to Ship
//course-----------------------------------------------------------------------
        if(command == "course"){
            getline(ss , args);
            stringstream ssargs(args);
            double angle, speed;
            ssargs >> angle;
            ssargs >> speed;
            Polar_vector* vec = new Polar_vector();
            vec->theta = angle;
            s->movingOnCourse(*vec , speed);
            s->setShip_status(Moving_on_course);
//position-----------------------------------------------------------------------
        }else if( command == "position"){
            getline(ss,args);
            stringstream ssargs(args);
            double x , y , speed;
            ssargs >> x >> y >> speed;
            Cartesian_vector* vec = new Cartesian_vector();
            vec->delta_x = x;
            vec->delta_y = y;
            s->movingToDestintion(*vec , speed);
            s->setShip_status(Moving_to);
//destination-----------------------------------------------------------------------
        }else if(command == "destination"){
            getline(ss,args);
            stringstream ssargs(args);
            double speed;
            ssargs >> portName >> speed;
            Port* p = Model::getInstance().getPortByName(portName);
            if(p){
                Cartesian_vector* vec = new Cartesian_vector();
                vec->delta_x = p->getLocation().x;
                vec->delta_y = p->getLocation().y;
                s->movingToDestintion(*vec , speed);
                s->setShip_status(Moving_on_course);
                s->setSim_obj_dest(p);
            }//there is a port with that name
//loat_at-----------------------------------------------------------------------
        }else if(command == "load_at"){
            getline(ss,args);
            stringstream ssargs(args);
            ssargs >> portName;
            Port* p = Model::getInstance().getPortByName(portName);
            if(p){
                Freighter* f = dynamic_cast<Freighter*>(Model::getInstance().getShipByName(name));
                if(f){
                    //
                }

            }


        }
    }
}
 */

