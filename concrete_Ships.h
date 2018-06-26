//
// Created by bar on 6/19/2018.
//

#ifndef HW3_CONCRETE_SHIPS_H
#define HW3_CONCRETE_SHIPS_H

#include <queue>
#include "Ship.h"


enum { FREIGHTER_FUEL_CAPACITY = 500, FRIEGHTER_MAXSPEED = 40,PATROL_FUEL_CAPACITY = 900, PATROL_MAXSPEED = 15, CRUSIER_MAXSPEED = 75};//fuel and speed limits

class Freighter :public Ship{//types of ships
private:
    int resistance;//local variables
    int containers_capacity;
    int containers_to_load = 0;
    int containers_to_unload = 0;
    queue<string> tasks;
public:
    Freighter(const string& name ,const string& type, const Point& p , int resistance , int capacity):Ship(name ,type, p),resistance(resistance),containers_capacity(capacity) {
        Ship::setFuel(FREIGHTER_FUEL_CAPACITY);
        setSpeed(0);
    };

    void update(){
        cout << "Freighter update"<<endl;
        playCommand();
    }//update the ship missions
    void playCommand(); // plays another command from vector
    void show_Status() {//show freighter status
        cout << getType() << " "<< getName() <<   " at (" << getLocation().x << ", " << getLocation().y << "), fuel: " << getFuel() << " kl, resistance: " << resistance;
        Ship::show_Status();
    }

    int getResistance() const {
        return resistance;
    }

    int getContainers_to_load() const {
        return containers_to_load;
    }

    int getContainers_to_unload() const {
        return containers_to_unload;
    }

    void setContainers_capacity(int containers_capacity) {
        Freighter::containers_capacity = containers_capacity;
    }

    void setContainers_to_load(int containers_to_load) {
        Freighter::containers_to_load = containers_to_load;
    }

    void setContainers_to_unload(int containers_to_unload) {
        Freighter::containers_to_unload = containers_to_unload;
    }

    int getContainers_capacity() const {
        return containers_capacity;
    }

    const string& getRatedCommand();
};

class Patrol :public Ship{
private:
    int resistance;//local variables
    int containers_capacity;
    queue<string> tasks;
public:
    Patrol(const string& name ,const string& type, const Point& p , int resistance , int capacity):Ship(name ,type, p),resistance(resistance),containers_capacity(capacity) {
        setFuel(PATROL_FUEL_CAPACITY);
        setSpeed(0);
    };
    void update(){
        cout << "Patrol update"<<endl;
        playCommand();
    }//update the ship missions
    void playCommand();
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
    void update(){
        cout << "Cruiser update"<<endl;
    }//update the ship missions
    void playCommand();
    void show_Status() {//show cruiser status
        cout << getType() << " "<< getName() <<   " at (" << getLocation().x << ", " << getLocation().y << "), force: " << attacking_force;
        Ship::show_Status();
    }
};

#endif //HW3_CONCRETE_SHIPS_H
