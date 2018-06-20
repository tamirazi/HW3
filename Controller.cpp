//
// Created by tamir on 6/15/18.
//

#include <fstream>
#include "Controller.h"

Controller::Controller() {
    view_ptr.reset(new View());
    //set this view_ptr to the model

}

Controller::~Controller() {
}



void Controller::run() {

    while(true){
        cout << "Time " << "t" << ": ";
        cout << "Enter command: ";
        getline(cin , line);
        stringstream ss(line);
        getline(ss , user_command , ' ');
        //---------------------------------------
        //View Commands
        if(user_command == "show"){
            view_ptr->getShips(Model::getInstance().returnShipVector());
            view_ptr->show();
        }else if(user_command == "default"){
            view_ptr->setDefault();
        }else if(user_command == "size"){
            int num;
            ss >> num;
            if(num > 6 && num <= 30){
                view_ptr->setSize(num);
            }else{
                //todo exception
            }
        }else if(user_command == "zoom"){
            int num;
            ss >> num;
            if(num > 0){
                view_ptr->zoom(num);
            }
        } else if(user_command == "pan"){
            double arg1 , arg2;
            ss >> arg1 >> arg2;
            view_ptr->setOrigins(arg1 , arg2);
        }
        //---------------------------------------
        //Model Commands
        if(user_command == "status"){
            Model::getInstance().showPortsStatus();
            Model::getInstance().showShipsStatus();
        }else if(user_command == "create"){
            double x=0,y=0;
            int resistance =0 , secondArg = 0;
            string name;
            string type;
            string point;
            getline(ss , name , ' ');
            getline(ss , type , ' ');
            getline(ss , point , ' ');
            point = point.substr(1,point.size());
            stringstream location(point);
            location >> x;
            getline(ss,point , ' ');
            location.str(point);
            location >> y;
            ss >> resistance;
            ss >> secondArg;
            Model::getInstance().addShip(shipFactory::getInstance().createNewShip(name,type,Point(x,y),secondArg));

        }
        //---------------------------------------
        if(user_command == "exit"){
            cout << "Exit..."<< endl;
            return;
            //check for memory leak
        }

    }


}

void Controller::Input(const string &portsFile) {
    ifstream in(portsFile);
    if(!in){
        cout << "Error cannot find such file";
        return;
    }
    string line;
    while(getline(in,line,'\n')){
        double x=0,y=0;
        int fuel =0 , produce = 0;
        string name;
        string type = "Port";
        string point;
        stringstream ss(line);
        getline(ss , name , ' ');
        getline(ss , point , ' ');
        point = point.substr(1,point.size());
        stringstream location(point);
        location >> x;
        getline(ss,point , ' ');
        location.str(point);
        location >> y;
        ss >> fuel;
        ss >> produce;
        Model::getInstance().addPort(new Port(name,type,Point(x,y),fuel,produce));
    }
}
