//
// Created by tamir on 6/18/18.
//
#include "Ship.h"

Ship::Ship(string name, Point p):SimObject(name,p) , ship_status (Stopped){}


void Ship::stop() {
    speed = 0;
    ship_status = Stopped;
}

void Ship::show_Status() {
    switch(ship_status){
        case Stopped:
            cout << "Stopped ";
            break;

        case Dead_in_the_water:
            cout << "Dead in the water";
            break;
        case Moving_to:
            cout << "Moving to (" << destination.delta_x << " , " << destination.delta_y
                                                                  << " ) " << "on course ";
            break;
        case Moving_on_course:
            cout << "Moving to " << sim_obj_dest->getName() << " on course ";
            break;

        case Docked:
            cout << "Docked at " << sim_obj_dest->getName();

    }
}

void Ship::setDestination(const Polar_vector &destination , double newSpeed) {
    ship_status = Moving_to;
    Ship::destination = destination;
    speed = newSpeed;
}

void Ship::setAngle(const Cartesian_vector &angle , double newSpeed) {
    Ship::angle = angle;
    speed = newSpeed;
    ship_status = Moving_on_course;
}
