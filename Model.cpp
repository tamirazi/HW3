//
// Created by tamir on 6/15/18.
//

#include "Model.h"

Model *Model::model = nullptr;

Model & Model::getInstance() {
    if (model == nullptr)
        model = new Model();
    return *model;
}

Model::Model() {
    //initialize all Model objects here
}

void Model::addShip(Ship *toAdd) {
    shared_ptr<SimObject> enter(toAdd);
    simVector.push_back(enter);
}
void Model::addPort(Port *toAdd) {
    shared_ptr<SimObject> enter(toAdd);
    simVector.push_back(enter);
}


void Model::showSimObjectStatus() {
    vector<shared_ptr<SimObject>>::iterator iter = simVector.begin();
    for(;iter != simVector.end() ; ++iter)
        iter.operator*().operator*().show_Status();
}

