//
// Created by bar on 6/19/2018.
//

#ifndef HW3_CONCRETE_SHIPS_H
#define HW3_CONCRETE_SHIPS_H

#include <deque>
#include <map>
#include <algorithm>
#include <iomanip>
#include "Ship.h"


enum { FREIGHTER_FUEL_CAPACITY = 500, FRIEGHTER_MAXSPEED = 40,PATROL_FUEL_CAPACITY = 900, PATROL_MAXSPEED = 15, CRUSIER_MAXSPEED = 75};//fuel and speed limits
//---------------------------------------------------------------------------------------Freighter
class Freighter :public Ship{//types of ships
private:
    int resistance;//local variables
    int containers_capacity;
    int containers_to_load ;
    int containers_to_unload ;
    queue<string> tasks;
public:
    Freighter(const string& name ,const string& type, const Point& p , int resistance , int capacity):Ship(name ,type, p),resistance(resistance),containers_capacity(capacity),containers_to_load(0) ,containers_to_unload(0) {
        Ship::setFuel(FREIGHTER_FUEL_CAPACITY);
        setSpeed(0);
        consumption = 10;
    };
    void update() override{
        cout << "Freighter update"<<endl;
        playCommand();
    }//update the ship missions
    void playCommand() override; // plays another command from vector
    void show_Status() override {//show freighter status
        std::cout << std::fixed;
        std::cout << std::setprecision(2);
        cout << getType() << " "<< getName() <<   " at ";
        getLocation().print();
        cout <<", fuel: " << getFuel() << " kl, resistance: " << resistance;
        Ship::show_Status();
        cout << ", containers: " << containers_capacity <<  endl;
    }
    const string getCommandByPriority() override;
    bool thereIsErgentRequest();
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
};
//---------------------------------------------------------------------------------------Patrol
class Patrol :public Ship{
private:
    int resistance;//local variables
    deque<string> tasks;
public:
    Patrol(const string& name ,const string& type, const Point& p , int resistance , int capacity):Ship(name ,type, p),resistance(resistance) {
        setFuel(PATROL_FUEL_CAPACITY);
        setSpeed(0);
        consumption = 20;
    };
    void update() override;
    void playCommand() override;
    const string getCommandByPriority() override;
    void show_Status() override{//show patrol status
        cout << fixed;
        cout << setprecision(2);
        cout <<getType() << " "<< getName() <<   " at " ;
        getLocation().print();
        cout << ", fuel: " << getFuel() << " kl, resistance: " << resistance <<  ", ";
        Ship::show_Status();
        cout <<  endl;
    }
    int getResistance() const {
        return resistance;
    }
    void setResistance(int resis)  {
        resistance = resis;
    }
    void calculateTasks();
    string findNextPort(vector<string>& ports);
};
//---------------------------------------------------------------------------------------Cruiser
class Cruiser :public Ship{
private:
    int attacking_force;//local variables
    int attacking_range;
public:
    Cruiser(const string& name ,const string& type, const Point& p , int force ,int range ):Ship(name ,type, p) , attacking_force(force),attacking_range(range) {};
    void update() override{
        cout << getName() << " Cruiser update"<<endl;
        attackShips();
        playCommand();
    }//update the ship missions
    void playCommand() override;
    void attackShips();
    const string getCommandByPriority() override;
    void show_Status() override{//show cruiser status
        cout << fixed;
        cout << setprecision(2);
        cout << getType() << " "<< getName() <<   " at ";
        getLocation().print();
        cout << ", force: " << attacking_force;
        Ship::show_Status();
        cout << endl;
    }
};

#endif //HW3_CONCRETE_SHIPS_H
