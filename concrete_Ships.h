//
// Created by bar on 6/19/2018.
//

#ifndef HW3_CONCRETE_SHIPS_H
#define HW3_CONCRETE_SHIPS_H

#include <queue>

enum { FREIGHTER_FUEL_CAPACITY = 500, FRIEGHTER_MAXSPEED = 40,PATROL_FUEL_CAPACITY = 900, PATROL_MAXSPEED = 15, CRUSIER_MAXSPEED = 75};//fuel and speed limits

class Freighter :public Ship{//types of ships
private:
    int resistance;//local variables
    int containers_capacity;
public:
    Freighter(const string& name ,const string& type, const Point& p , int resistance , int capacity):Ship(name ,type, p),resistance(resistance),containers_capacity(capacity) {
        setFuel(FREIGHTER_FUEL_CAPACITY);
        setSpeed(0);
    };
    void insertCommandToQueue(const string& command){//insert string to queue
        missions.push_back(command);
        vector<string>::iterator iter = missions.begin();
        for(;iter != missions.end();++iter){
            cout << iter.operator*() << endl;
        }
    }
    void update(){
        cout << "Freighter update"<<endl;
        pharseLineFromVec();
    }//update the ship missions
    void show_Status() {//show freighter status
        cout << getType() << " "<< getName() <<   " at (" << getLocation().x << ", " << getLocation().y << "), fuel: " << getFuel() << " kl, resistance: " << resistance;
        Ship::show_Status();
    }

    int getResistance() const {
        return resistance;
    }

    int getContainers_capacity() const {
        return containers_capacity;
    }
};
class Patrol :public Ship{
private:
    int resistance;//local variables
    int containers_capacity;
public:
    Patrol(const string& name ,const string& type, const Point& p , int resistance , int capacity):Ship(name ,type, p),resistance(resistance),containers_capacity(capacity) {
        setFuel(PATROL_FUEL_CAPACITY);
        setSpeed(0);
    };
    void insertCommandToQueue(const string& command){//insert string to queue
        missions.push_back(command);
        vector<string>::iterator iter = missions.begin();
        for(;iter != missions.end();++iter){
            cout << iter.operator*() << endl;
        }
    }
    void update(){}//update the ship missions
    void show_Status() {//show patrol status
        cout <<getType() << " "<< getName() <<   " at (" << getLocation().x << ", " << getLocation().y << "), fuel: " << getFuel() << " kl, resistance: " << resistance;
        Ship::show_Status();
    }

    int getResistance() const {
        return resistance;
    }

    int getContainers_capacity() const {
        return containers_capacity;
    }
};
class Cruiser :public Ship{
private:
    int attacking_force;//local variables
public:
    Cruiser(const string& name ,const string& type, const Point& p , int force  ):Ship(name ,type, p) , attacking_force(force) {};
    void insertCommandToQueue(const string& command){//insert string to queue
        missions.push_back(command);
        vector<string>::iterator iter = missions.begin();
        for(;iter != missions.end();++iter){
            cout << iter.operator*() << endl;
        }
    }
    void update(){}//update the ship missions
    void show_Status() {//show cruiser status
        cout << getType() << " "<< getName() <<   " at (" << getLocation().x << ", " << getLocation().y << "), force: " << attacking_force;
        Ship::show_Status();
    }
};

#endif //HW3_CONCRETE_SHIPS_H
