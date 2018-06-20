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
    shared_ptr<Ship> enter(toAdd);
    shipsVector.push_back(enter);
}
void Model::addPort(Port *toAdd) {
    shared_ptr<Port> enter(toAdd);
    portsVector.push_back(enter);
}

void Model::showShipsStatus() {
    vector<shared_ptr<Ship>>::iterator iter = shipsVector.begin();
    for(;iter != shipsVector.end() ; ++iter)
        iter.operator*().operator*().show_Status();
}

void Model::showPortsStatus() {
    vector<shared_ptr<Port>>::iterator iter = portsVector.begin();
    for(;iter != portsVector.end() ; ++iter)
        iter.operator*().operator*().show_Status();
}

