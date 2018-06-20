


#ifndef HW3_SIMOBJECT_H
#define HW3_SIMOBJECT_H
#include "Geometry.h"
#include <string>
using namespace std;
class SimObject {
private:
    string name;
    string type;
    Point location;

public:
    SimObject(const string& name ,const string& type ,const Point& point):name(name) ,type(type), location(point){}
    virtual void show_Status() = 0 ;
    const string &getType() const {
        return type;
    };
    const string &getName() const {
        return name;
    }
    const Point &getLocation() const {
        return location;
    }
    virtual void update() = 0;
};


#endif //HW3_SIMOBJECT_H
