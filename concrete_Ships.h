//
// Created by bar on 6/19/2018.
//

#ifndef HW3_CONCRETE_SHIPS_H
#define HW3_CONCRETE_SHIPS_H

#include "Ship.h"

enum { FUEL_CAPACITY = 500, MAXSPEED = 40};

class freighter :public Ship{
public:
    freighter(const string& name , const Point& p):Ship(name , p) , speed(40) , consumption(1000) ,
                                                        fuel(FUEL_CAPACITY) {};
private:
    int resistance;
    int containers_capacity;

};
class patrol :public Ship{
public:
    patrol(const string& name , const Point& p):Ship(name , p) , speed(40) , consumption(1000) ,
                                                   fuel(FUEL_CAPACITY) {};
private:
    int resistance;
    int containers_capacity;

};
class crusier :public Ship{
public:
    crusier(const string& name , const Point& p):Ship(name , p) , speed(40) , consumption(1000) ,
                                                   fuel(FUEL_CAPACITY) {};
private:
    int resistance;
    int containers_capacity;

};

#endif //HW3_CONCRETE_SHIPS_H
