

#ifndef HW3_MODEL_H
#define HW3_MODEL_H

#include "Ship.h"
#include "shipFactory.h"
#include "SimObject.h"
#include "Port.h"
#include <vector>
#include <memory>
#include <algorithm>
//Singleton object
class Model {
private:
    static Model* model;
    Model();
    ~Model(){};
    friend class ModelDestroyer;
    vector<shared_ptr<SimObject>> simVector;

public:
    static Model &getInstance();
    Model(const Model&) = delete;
    Model& operator= (const Model&) = delete;
    Model(const Model&&) = delete;
    Model& operator= (const Model&&) = delete;
    void addShip(Ship* toAdd);
    void addPort(Port *toAdd);
    void showSimObjectStatus();
    void go();
    vector<shared_ptr<SimObject>>& returnObjectsVector(){return simVector;};
    bool thereIsSuchShip(const string& ship);
    shared_ptr<SimObject> getObjectByName(const string& name);
    shared_ptr<Ship> getShipByName(const string &name);
    shared_ptr<Port> getPortByName(const string& name);
};


#endif //HW3_MODEL_H
