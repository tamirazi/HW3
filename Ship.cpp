//
// Created by tamir on 6/18/18.
//
#include "Ship.h"
#include "Model.h"

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

void Ship::setSim_obj_dest(SimObject *sim_obj_dest) {
    Ship::sim_obj_dest = sim_obj_dest;
}

void Ship::pharseLineFromVec() {
    if(!missions.empty() && !busy){
        busy = true; //after pharse the command the ship will be busy
        string command , name;
        stringstream ss(missions.front());
        getline(ss , name , ' ');
        getline(ss , command , ' ');
        Ship* s = Model::getInstance().getShipByName(name);
        if(command == "course"){
            string args;
            getline(ss , args);
            stringstream ssargs(args);

            double angle, speed;
            ssargs >> angle;
            ssargs >> speed;
            Polar_vector* vec = new Polar_vector();
            vec->theta = angle;
            s->movingOnCourse(*vec , speed);
            s->setShip_status(Moving_on_course);

        }else if( command == "position"){
            string args;
            getline(ss,args);
            stringstream ssargs(args);
            double x , y , speed;
            ssargs >> x >> y >> speed;
            Cartesian_vector* vec = new Cartesian_vector();
            vec->delta_x = x;
            vec->delta_y = y;
            s->movingToDestintion(*vec , speed);
            s->setShip_status(Moving_to);
        }else if(command == "destination"){
            string args;
            getline(ss,args);
            stringstream ssargs(args);
            string portName;
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

        }
    }
}

