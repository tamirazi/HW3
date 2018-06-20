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
    Port(const string& name1,const string& type, Point point, int capacity, int make_per_hours);
    int getCapicity() const;
    int getMake_per_hours() const;
    void update() override;
    void show_Status();
    void insertCommandToQueue(const string& command){};

};


#endif //HW3_PORT_H
