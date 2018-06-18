//
// Created by tamir on 6/18/18.
//

#include "Freighter.h"

Freighter::Freighter(string name , Point point):Ship(name , point) , speed(40) , consumption(1000) ,
                                                fuel(FUEL_CAPACITY) {};
