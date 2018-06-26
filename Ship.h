//
// Created by bar on 6/18/2018.
//


#ifndef HW3_SHIP_H
#define HW3_SHIP_H
#include "SimObject.h"
#include "Port.h"
#include <sstream>
#include <queue>
enum status {Stopped , Docked , Dead_in_the_water ,
    Moving_to , Moving_on_course} ;
class Ship : public SimObject{
protected:
    status ship_status;
    double fuel , speed , consumption;
    Polar_vector angle;
    Point destination;
public:
    const Point &getDestination() const;

    void setDestination(const Point &destination);

protected:
    SimObject* sim_obj_dest;
    vector<string> missions;
    bool busy = false;
public:

    Ship(const string& name ,const string& type,const Point& p);
    void stop();
    virtual void show_Status();
   // void movingToDestintion(const Polar_vector &destination , double speed);
    void movingOnCourse(const Cartesian_vector &angle, double speed);
    double getFuel() const;
    void setSim_obj_dest(SimObject *sim_obj_dest);
    void setFuel(double fuel);
    double getSpeed() const;
    void setSpeed(double speed);
    void setLocation(const Point& newLoc);
    status getShip_status() const;
    void setShip_status(status ship_status);
    virtual void playCommand()= 0;
    void printMissions();
    void insertMissionToVector(const string& command);

};

#endif //HW3_SHIP_H
