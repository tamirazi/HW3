#include <iostream>
#include "Controller.h"
#include "shipFactory.h"
shipFactory* shipFactory::factory = nullptr;
class ModelDestroyer {
public:
    ~ModelDestroyer(){delete Model::model;}
} md;

int main(int argc,char* argv[]) {
//    View v;
//
//    v.zoom(2);
//    v.setOrigins(-10.3 , -10.3);
//    v.setSize(25);
//    v.show();
//
//    v.zoom(5);
//    v.setOrigins(-20.5 , -20.5);
//    v.setSize(15);
//    v.show();
//    Time 0: Enter command: create Ajax Cruiser (15.00, 15.00) 6 1
//    Time 0: Enter command: create Emma Freighter (30.00, 30.00) 1000 8
//    Time 0: Enter command: create Xerxes Cruiser (25.00, 25.00) 6 2
//    Time 0: Enter command: create Shikishima Patrol_boat (0.0 0.0) 10
    if(argc != 2){
        cout << "Error: Usage needed ./<Prog> <Ports_Input_File> " << endl;
        return 1;
    }else{
        Controller c;
        c.Input(argv[1]);
        Model::getInstance().addShip(shipFactory::getInstance().createNewShip("Ajax","Cruiser",Point(15.00, 15.00),6,1));
        Model::getInstance().addShip(shipFactory::getInstance().createNewShip("Emma","Freighter",Point(30.00, 30.00),8,1000));
        Model::getInstance().addShip(shipFactory::getInstance().createNewShip("Xerxes","Cruiser",Point(25.00, 25.00) ,6,2));
        Model::getInstance().addShip(shipFactory::getInstance().createNewShip("Shikishima","Patrol",Point(0.0,0.0),10));
       // Model::getInstance().addShip(shipFactory::getInstance().createNewShip("Azizovitch","Patrol",Point(1,1),10));
        c.run();

    }

    return 0;
}