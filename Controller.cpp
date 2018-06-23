//
// Created by tamir on 6/15/18.
//

#include <fstream>
#include "Controller.h"
#include <algorithm>


Controller::Controller() {
    view_ptr.reset(new View());
    //set this view_ptr to the model

}

Controller::~Controller() {
}



void Controller::run() {

    while(true){
        cout << "Time " << Model::getInstance().getTimer() << ": ";
        cout << "Enter command: ";
        getline(cin , line);
        stringstream ss(line);
        getline(ss , user_command , ' ');
        transform(user_command.begin(),user_command.end(),user_command.begin(),::tolower);
        //---------------------------------------
        //View Commands
        if(user_command == "show"){//updating the view and show the board
            view_ptr->setObjects(Model::getInstance().returnObjectsVector());
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
        if(user_command == "status"){//print status for all simulator objects existing in board
            Model::getInstance().showSimObjectStatus();
        }else if(user_command == "create"){//create new ship by command
            double x=0,y=0;//for parsing the command
            int resistance =0 , secondArg = 0;
            string name;
            string type;
            string point;
            getline(ss , name , ' ');   //get name from command
            getline(ss , type , ' ');   //get type from command
            getline(ss , point , ' ');  //get point from command
            point = point.substr(1,point.size());
            stringstream location(point);
            location >> x;
            getline(ss,point , ' ');
            location.str(point);
            location >> y;
            ss >> resistance;
            ss >> secondArg;
            Model::getInstance().addShip(shipFactory::getInstance().createNewShip(name,type,Point(x,y),secondArg));//creating the ship with ship factory and adding it into the model
        }else if(user_command == "go"){
            // up timer + 1

            //call update for every SimObj
            Model::getInstance().go();
        }
        //---------------------------------------
        //Ships Command
        if(Model::getInstance().thereIsSuchShip(user_command)){//if there is such ship
            //if user command = ship name;
            shared_ptr<SimObject> ship = Model::getInstance().getObjectByName(user_command);//get reference to ship
            string command;
            ss >> command;
            //Ship* s = Model::getInstance().getShipByName(user_command).get(); //test to downcast Simobj to ship
            pharseLineForShip(ss.str());
           // ship->insertCommandToQueue(command);//insert the command into ship queue
            //ship->update();
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

void Controller::pharseLineForShip(const string &usrLine) {

    string command , name;
    stringstream ss(usrLine);
    getline(ss , name , ' ');
    getline(ss , command , ' ');
    Ship* s = Model::getInstance().getShipByName(name);
    if(command == "course"){
        string args;
        getline(ss , args);
        stringstream ssargs(args);
        if(wordsCounter(args) == 2) {//2 args after course
            double angle, speed;
            ssargs >> angle;
            ssargs >> speed;
            Polar_vector* vec = new Polar_vector();
            vec->theta = angle;
            s->movingOnCourse(*vec , speed);
            s->setShip_status(Moving_on_course);
        }

    }else if( command == "position"){
        string args;
        getline(ss,args);
        stringstream ssargs(args);
        if(wordsCounter(args) == 3){
            double x , y , speed;
            ssargs >> x >> y >> speed;
            Cartesian_vector* vec = new Cartesian_vector();
            vec->delta_x = x;
            vec->delta_y = y;
            s->movingToDestintion(*vec , speed);
            s->setShip_status(Moving_to);
        }
    }



}

int Controller::wordsCounter(const string &line) {

    int counter = 0;

    stringstream ss(line);
    string tmp;
    while (ss >> tmp) counter++;

    return counter;
}



