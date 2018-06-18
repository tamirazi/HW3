//
// Created by tamir on 6/16/18.
//

#ifndef HW3_PORT_H
#define HW3_PORT_H
#include "SimObject.h"

class Port :public SimObject{
private:
    int capacity;
    int make_per_hours;

public:
    Port(string name1, Point point, int capacity, int make_per_hours);
    int getCapicity() const;
    int getMake_per_hours() const;
    void update() override;


};


#endif //HW3_PORT_H
