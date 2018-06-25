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
            Ship* s = Model::getInstance().getShipByName(user_command); //test to downcast Simobj to ship
            if(command == "stop"){
                s->stop();
            }else if(pharseLineForErrors(ss.str())){
                ship->insertCommandToQueue(ss.str());//insert the command into ship queue

            }

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

bool Controller::pharseLineForErrors(const string &usrLine) {
    //this function pharsing the line from the user for checking errors
    //if the command are good
    //add the command to specipic ship queue

    string command , name;
    stringstream ss(usrLine);
    getline(ss , name , ' ');
    getline(ss , command , ' ');
    string args;
    getline(ss , args);
    stringstream ssargs(args);
    Ship* s = Model::getInstance().getShipByName(name);
//course-----------------------------------------------------------------------
    if(command == "course"){
        if(wordsCounter(args) == 2) {//2 args after course
            double angle, speed;
            ssargs >> angle;
            ssargs >> speed;
            if(speed <= 0){
                cerr << "speed argument illegal" << endl;
                return false;
            }else{
                return  true;
            }
        }
//position-----------------------------------------------------------------------
    }else if( command == "position"){

        if(wordsCounter(args) == 3){
            double speed , x , y;
            ssargs >> x >> y >> speed;
            if(speed <= 0){
                cerr << "speed argument illegal" << endl;
                return false;
            }
            else{
                return true;
            }
        }else {
            cerr << "need more arguments " << endl;
            //todo exceptopn
            return false;
        }
//destination-----------------------------------------------------------------------
    }else if(command == "destination"){

        if(wordsCounter(args) == 2){
            string portName;
            double speed;
            ssargs >> portName >> speed;
            Port* p = Model::getInstance().getPortByName(portName);
            if(p){
                if(speed > 0){
                    return true;
                } else
                    cerr << "speed argument illegal" << endl;
                return false;
            }
            else{
                cerr << "port name ERROR";
                //todo exception
                return false;
            }

        }else{
            cerr << "nedd more arguments " << endl;
            //todo exceptopn
            return false;
        }
//loat_at-----------------------------------------------------------------------
    }else if(command == "load_at"){
        string portName;

        if(s->getType() == "Freighter"){
            if(wordsCounter(args) == 1){
                ssargs >> portName;
                Port* p = Model::getInstance().getPortByName(portName);
                if(p){
                    return  true;
                }else{
                    cerr << "port name ERROR";
                    //todo exception
                    return false;
                }
            }else{
                cerr << "need more arguments " << endl;
                //todo exception
                return false;
            }

        } else{
            //todo exception
            cerr << "'load_at' command is only for Freighter ship" << endl;
            return false;
        }
//unloat_at-----------------------------------------------------------------------
    }else if(command == "unload_at"){
        string portName;
        int containers_to_load;
        if(s->getType() == "Freighter"){
            if(wordsCounter(args) == 2){
                ssargs >> portName;
                ssargs >> containers_to_load;
                Port* p = Model::getInstance().getPortByName(portName);
                if(p){
                    if(containers_to_load >= 0)
                        return  true;
                }else{
                    cerr << "port name ERROR";
                    //todo exception
                    return false;
                }
            }
        }else{
            //todo exception
            cerr << "'unload_at' command is only for Freighter ship" << endl;
            return false;
        }
    }


    return false;


}

int Controller::wordsCounter(const string &line) {

    int counter = 0;

    stringstream ss(line);
    string tmp;
    while (ss >> tmp) counter++;

    return counter;
}



