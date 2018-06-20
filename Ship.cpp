//
// Created by tamir on 6/18/18.
//
#include "Ship.h"

Ship::Ship(const string& name ,const string& type,const Point& p ):SimObject(name,type,p),ship_status (Stopped),fuel(0),speed(0){}
void Ship::stop() {
    speed = 0;
    ship_status = Stopped;
}
void Ship::movingToDestintion(const Polar_vector &destination , double newSpeed) {
    ship_status = Moving_to;
    Ship::destination = destination;
    speed = newSpeed;
}
void Ship::movingOnCourse(const Cartesian_vector &angle , double newSpeed) {
    Ship::angle = angle;
    speed = newSpeed;
    ship_status = Moving_on_course;
}
double Ship::getFuel() const {
    return fuel;
}
void Ship::setFuel(double fuel) {
    Ship::fuel = fuel;
}
double Ship::getSpeed() const {
    return speed;
}
void Ship::setSpeed(double speed) {
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
            cout <<  "Moving to (" << destination.delta_x << " , " << destination.delta_y
                 << " ) " << "on course " << endl;
            break;
        case Moving_on_course:
            cout << "Moving to " << sim_obj_dest->getName() << " on course " << endl;
            break;
        case Docked:
            cout << "Docked at " << sim_obj_dest->getName() << endl;
    }
}

