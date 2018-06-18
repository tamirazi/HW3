//
// Created by tamir on 6/16/18.
//

#include "SimObject.h"

SimObject::SimObject(string name, Point point):name(name) , location(point) {};

const string &SimObject::getName() const {
    return name;
}

const Point &SimObject::getLocation() const {
    return location;
}
