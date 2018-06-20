

#ifndef HW3_MODEL_H
#define HW3_MODEL_H

#include "ShipFactory.h"
#include "Port.h"
#include <vector>
#include <memory>
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
    vector<shared_ptr<SimObject>>& returnObjectsVector(){return simVector;};

};


#endif //HW3_MODEL_H
