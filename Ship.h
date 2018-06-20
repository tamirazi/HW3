//
// Created by bar on 6/18/2018.
//


#ifndef HW3_SHIP_H
#define HW3_SHIP_H
#include "SimObject.h"
enum status {Stopped , Docked , Dead_in_the_water ,
    Moving_to , Moving_on_course} ;
class Ship : public SimObject{
protected:
    status ship_status;
    double fuel , speed , consumption;
    Polar_vector angle;
    Cartesian_vector destination;
    SimObject* sim_obj_dest;
public:

    Ship(const string& name ,const string& type,const Point& p);
    void stop();
    virtual void show_Status() = 0 ;
    void setDestination(const Polar_vector &destination , double speed);
    void setAngle(const Cartesian_vector &angle, double speed);
    double getFuel() const;
    void setFuel(double fuel);
    double getSpeed() const;
    void setSpeed(double speed);
    status getShip_status() const;
    void setShip_status(status ship_status);

};

#endif //HW3_SHIP_H
