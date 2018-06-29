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
void Ship::movingOnCourse(float angle , float newSpeed) {
    course = angle;
    speed = newSpeed;
    ship_status = Moving_on_course;
}
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
void Ship::setShip_status(status ship_status) {
    Ship::ship_status = ship_status;
}
void Ship::show_Status() {
    switch(ship_status){
        case Stopped:
            cout << ", Stopped ";
            break;
        case Dead_in_the_water:
            cout <<", Dead in the water";
            break;
        case Moving_to:
            cout << ", Moving to " <<destinationName<< " on course " << to_degrees(deg.theta) << " deg, speed " << speed <<  " nm/hr" ;
            break;
        case Moving_on_course:
            cout << " Moving on course " << course << " deg, speed " << speed << " nm/hr ";
            break;
        case Docked:
            cout << " Docked at " << destinationName ;
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
        } else { cerr << "port null" << endl; }
    }
}

void Ship::goOnCourse(const string &line) {
    cout << line << endl;
    stringstream ss(line);
    string command;
    float degree;
    float speed;
    ss  >> command;
    if(command == "course") {
        ss >> degree;
        ss >> speed;
        setLocation(prograssByCourse(getLocation(),degree,speed));
        movingOnCourse(degree,speed);
    }
}

void Ship::dockAtPort() {
    setShip_status(Docked);
    setSpeed(0);
}

bool Ship::isArrived() {
    return getLocation().x == getDestination().x && getLocation().y == getDestination().y;
}

