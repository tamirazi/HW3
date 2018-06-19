#include <string>
#include "Geometry.h"

#ifndef HW3_SIMOBJECT_H
#define HW3_SIMOBJECT_H

using namespace std;
class SimObject {
private:
    string name;
    Point location;

public:
    SimObject(const string& name ,const Point& point):name(name) , location(point){};

    const string &getName() const {
        return name;
    }

    const Point &getLocation() const {
        return location;
    }

    virtual void update() = 0;
};


#endif //HW3_SIMOBJECT_H
