//
// Created by tamir on 6/16/18.
//

#include "Port.h"


Port::Port(string name1, Point point, int capacity, int make_per_hours)
        : SimObject(name1, point), capacity(capacity), make_per_hours(make_per_hours) {
}

int Port::getCapicity() const {
    return capacity;
}

int Port::getMake_per_hours() const {
    return make_per_hours;
}

void Port::update() {

}
