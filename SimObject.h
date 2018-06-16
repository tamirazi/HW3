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

    const string &getName() const;
    const Point &getLocation() const;
    virtual void update();
};


#endif //HW3_SIMOBJECT_H
