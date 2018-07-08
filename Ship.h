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
    float fuel , speed , consumption ,course;
    string destinationName;
    Point destination;
    Polar_vector deg;
    SimObject* sim_obj_dest;
    vector<string> missions;
    bool busy = false;
public:
    float getConsumption() const;
    const Point &getDestination() const;
    void setDestination(const Point &destination);
    virtual const string getCommandByPriority() = 0;
    void setDestinationName(const string &destination);
    Ship(const string& name ,const string& type,const Point& p);
    void stop();
    virtual void show_Status();
    void goToDestination(const string& command);
    void goOnCourse(const string& line);
    void movingToDestination(const Point &destination , float speed);
    void movingOnCourse(float angle, float speed);
    float getFuel() const;
    void setFuel(float fuel);
    double getSpeed() const;
    void setSpeed(float speed);
    void setLocation(const Point& newLoc);
    void setShip_status(status ship_status);
    virtual void playCommand()= 0;
    void insertMissionToVector(const string& command);
    bool isArrived();
    void dockAtPort();
    void goOnPoint(const string &line);
    void printMissions(){
        cout << getName() << "  missions:" << endl;
        auto iter = missions.begin();
        for(;iter!= missions.end();iter++){
            cout << iter.operator*() <<endl;
        }
    };
    int getMaxSpeed(const string& type);

};

#endif //HW3_SHIP_H
