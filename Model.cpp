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
    addPort(new Port("Nagoya" , "Port" , Point(50,5) , 1000000 , 1000));
}

void Model::addShip(Ship *toAdd) {//add a Ship to the objects vector
    shared_ptr<SimObject> enter(toAdd);
    simVector.push_back(enter);
}
void Model::addPort(Port *toAdd) {//add a Port to the objects vector
    shared_ptr<SimObject> enter(toAdd);
    simVector.push_back(enter);

}


void Model::showSimObjectStatus() {//show all simulator object status
    vector<shared_ptr<SimObject>>::iterator iter = simVector.begin();
    for(;iter != simVector.end() ; ++iter)
        iter.operator*().operator*().show_Status();
}

bool Model::thereIsSuchShip(const string &ship) {//checks if there is a ship named like the string argument return boolean YES-found NO-not found
    vector<shared_ptr<SimObject>>::iterator iter = simVector.begin();
    for(;iter != simVector.end();++iter){
        string tmp  = iter.operator*().operator*().getName();
        transform(tmp.begin(),tmp.end(),tmp.begin(),::tolower);
        if(tmp.compare(ship) == 0 && iter.operator*().operator*().getType().compare("Port") == 0 ){//if found but as a Port
            cout << "You Can't change a Port"<< endl;
            return false;
        }else if(tmp.compare(ship) == 0) return  true;
    }
    return false;
}

shared_ptr<SimObject> Model::getObjectByName(const string &name) {//returns a pointer to object by a string name return null if not found
    vector<shared_ptr<SimObject>>::iterator iter = simVector.begin();
    for(;iter != simVector.end();++iter){
        string tmp  = iter.operator*().operator*().getName();
        transform(tmp.begin(),tmp.end(),tmp.begin(),::tolower);
        if(tmp.compare(name) == 0) {//if found the name return the pointer
            return iter.operator*();
        }
    }
    return nullptr;//else return null
}

Ship * Model::getShipByName(const string &name) {// get ship object from simobject vector by name
    if(thereIsSuchShip(name)){
        Ship* ship = dynamic_cast<Ship*>(getObjectByName(name).get());
        if(ship){
            //shared_ptr<Ship> s(ship);
            return ship;
        }
    }
    return nullptr;
}

shared_ptr<Port> Model::getPortByName(const string &name) {
    Port* port = dynamic_cast<Port*>(getObjectByName(name).get());
    if(port){
        shared_ptr<Port> elm(port);
        return elm;
    }
    return nullptr;

}

void Model::go() {
    timer++;

    for( auto &s : simVector){
        s->update();
    }
}

int Model::getTimer() const {
    return timer;
}


