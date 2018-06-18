//
// Created by tamir on 6/18/18.
//

#ifndef HW3_FREIGHTER_H
#define HW3_FREIGHTER_H

#include "Ship.h"

enum { FUEL_CAPACITY = 500, MAXSPEED = 40};

class Freighter :public Ship{
public:
    Freighter(string name , Point p);
private:
    int resistance;
    int containers_capacity;

};


#endif //HW3_FREIGHTER_H
