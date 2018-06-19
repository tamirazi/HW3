//
// Created by bar on 6/18/2018.
//
#include "SimObject.h"

#ifndef HW3_SHIP_H
#define HW3_SHIP_H

enum status {Stopped , Docked , Dead_in_the_water ,
    Moving_to , Moving_on_course} ;
class Ship : public SimObject{
public:
    Ship(const string& name ,const Point& p);
    void stop();
    void show_Status();
    void setDestination(const Polar_vector &destination , double speed);
    void setAngle(const Cartesian_vector &angle, double speed);

protected:
    status ship_status;
    double fuel , speed , consumption;
    Polar_vector angle;
    Cartesian_vector destination;
    SimObject* sim_obj_dest;
};

#endif //HW3_SHIP_H
