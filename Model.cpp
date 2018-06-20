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

bool Model::thereIsSuchShip(const string &ship) {
    vector<shared_ptr<SimObject>>::iterator iter = simVector.begin();
    for(;iter != simVector.end();++iter){
        string tmp  = iter.operator*().operator*().getName();
        transform(tmp.begin(),tmp.end(),tmp.begin(),::tolower);
        if(tmp.compare(ship) == 0 && iter.operator*().operator*().getType().compare("Port") == 0 ){
            cout << "You Can't change a Port"<< endl;
            return false;
        }else if(tmp.compare(ship) == 0) return  true;
    }
    return false;
}

shared_ptr<SimObject> Model::getObjectByName(const string &name) {
    vector<shared_ptr<SimObject>>::iterator iter = simVector.begin();
    for(;iter != simVector.end();++iter){
        string tmp  = iter.operator*().operator*().getName();
        transform(tmp.begin(),tmp.end(),tmp.begin(),::tolower);
        if(tmp.compare(name) == 0) {
            return iter.operator*();
        }
    }
    return nullptr;
}

