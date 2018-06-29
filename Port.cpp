//
// Created by tamir on 6/16/18.
//

#include "Port.h"


Port::Port(const string& name1,const string& type, Point point, int capacity, int make_per_hours)
        : SimObject(name1,type, point), capacity(capacity), make_per_hours(make_per_hours) {
}

int Port::getCapicity() const {
    return capacity;
}

int Port::getMake_per_hours() const {
    return make_per_hours;
}

void Port::update() {}

void Port::show_Status() {
    cout << fixed <<setprecision(2);
    cout << getType() << " " << getName() << " at position ";
    getLocation().print();
    cout << ", Fuel available: " << getCapicity() << " kl" << endl;
}
