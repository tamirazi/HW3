//
// Created by bar on 6/19/2018.
//

#ifndef HW3_SHIPFACTORY_H
#define HW3_SHIPFACTORY_H

#include "concrete_Ships.h"
class shipFactory{
private:
    static shipFactory* factory;
    shipFactory(){}
    ~shipFactory(){}

public:
    static shipFactory& getInstance(){
        if(factory == nullptr)
            factory = new shipFactory();
        return *factory;
    }
    Ship* createNewShip(const string& name,const string& type , const Point& loctaion, int resistance , int capacity_range =0){
        if(type.compare("Freighter") == 0 ){
            return new Freighter(name,type,loctaion,resistance,capacity_range);
        }else if(type.compare("Patrol") == 0){
            return new Patrol(name,type,loctaion,resistance,capacity_range);
        }else if(type.compare("Cruiser") == 0){
            return new Cruiser(name,type,loctaion,resistance,capacity_range);
        }else{ cout << "Do NOT know this kind of ship."<< endl ; exit(1);}
    }
};
#endif //HW3_SHIPFACTORY_H
