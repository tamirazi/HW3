
#ifndef HW3_VIEW_H
#define HW3_VIEW_H
#include <iostream>
#include <string>
#include <vector>
#include "Ship.h"
#include <memory>
using namespace std;
class View {

private:
    int size , scale;
    double xorigin , yorigin;
    vector<shared_ptr<SimObject>> objects;

public:
    View();
    void show();
    void setOrigins(double x , double y);
    void zoom(int num);
    void setDefault();
    void setSize(int num);
    void getObjects(const vector<shared_ptr<SimObject>> &objVector);

};


#endif //HW3_VIEW_H
