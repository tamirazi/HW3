//
// Created by tamir on 6/15/18.
//

#include <fstream>
#include "Controller.h"

enum { MIN_SCALE = 3  ,MAX_SCALE = 60};

Controller::Controller() {
    view_ptr.reset(new View());
}

Controller::~Controller() {
}

void Controller::run() {

    while(true){
        try {
            cout << "Time " << Model::getInstance().getTimer() << ": ";
            cout << "Enter command: ";
            getline(cin, line);
            stringstream ss(line);
            getline(ss, user_command, ' ');
            transform(user_command.begin(), user_command.end(), user_command.begin(), ::tolower);
            //---------------------------------------
            //View Commands
            if (user_command == "show") {//updating the view and show the board
                view_ptr->setObjects(Model::getInstance().returnObjectsVector());
                view_ptr->show();
            } else if (user_command == "default") {
                view_ptr->setDefault();
            } else if (user_command == "size") {
                int num;
                ss >> num;
                if (num > MIN_SCALE && num <= MAX_SCALE) {
                    view_ptr->setSize(num);
                } else {
                    throw viewException();
                }
            } else if (user_command == "zoom") {
                int num;
                ss >> num;
                if (num > 0) {
                    view_ptr->zoom(num);
                }else throw zoomException();
            } else if (user_command == "pan") {
                double arg1, arg2;
                ss >> arg1 >> arg2;
                view_ptr->setOrigins(arg1, arg2);
                //---------------------------------------
                //Model Commands
            } else if (user_command == "status") {//print status for all simulator objects existing in board
                Model::getInstance().showSimObjectStatus();
            } else if (user_command == "create") {//create new ship by command
                double x = 0, y = 0;//for parsing the command
                int resistance = 0, secondArg = 0;
                string name;
                string type;
                string point;
                getline(ss, name, ' ');   //get name from command
                getline(ss, type, ' ');   //get type from command
                getline(ss, point, ' ');  //get point from command
                point = point.substr(1, point.size());
                stringstream location(point);
                location >> x;
                getline(ss, point, ')');
                stringstream location2(point);
                location2 >> y;
                ss >> resistance;
                ss >> secondArg;
                Model::getInstance().addShip(
                        shipFactory::getInstance().createNewShip(name, type, Point(x, y), resistance,
                                                                 secondArg));//creating the ship with ship factory and adding it into the model
            } else if (user_command == "go") {

                //call update for every SimObj
                Model::getInstance().go();
                //---------------------------------------
                //Ships Command
            } else if (Model::getInstance().thereIsSuchShip(user_command)) {//if there is such ship
                //if user command = ship name;
                string command;
                ss >> command;
                Ship *s = Model::getInstance().getShipByName(user_command); //get the ship by his name from user command
                if (!s) {
                    throw shipNotFoundException();
                }
                if (command == "stop") {
                    s->stop();
                } else if (parseLineForErrors(ss.str())) {
                    string mission = line.erase(0, user_command.size() + 1).c_str();
                    s->insertMissionToVector(mission);//insert the command into ship queue
                } else { cerr << "There has been some problem the command didn't insert into queue" << endl; }
                //---------------------------------------
            } else if (user_command == "exit") {
                cout << "Exit..." << endl;
                return;
            } else {
                throw noSuchCommandException();
            }
        }catch (exception& e){//catch any exception and continue
            cerr << e.what() << endl << endl;
        }
    }
}

void Controller::Input(const string &portsFile) {
    ifstream in(portsFile);
    if(!in){
        cout << "Error cannot find such file";
        throw fileNotFoundException();
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

bool Controller::parseLineForErrors(const string &usrLine) {
    //this function pharsing the line from the user for checking errors
    //if the command are good
    //add the command to specific ship queue
    string command , name;
    stringstream ss(usrLine);
    getline(ss , name , ' ');
    getline(ss , command , ' ');
    string args;
    getline(ss , args);
    stringstream ssargs(args);
    Ship* s = Model::getInstance().getShipByName(name);
    if(!s){
        throw shipNotFoundException();
    }
//course-----------------------------------------------------------------------
    if(command == "course"){
        if(wordsCounter(args) == 2) {//2 args after course
            double angle, speed;
            ssargs >> angle;
            ssargs >> speed;
            if(speed <= 0){
                throw negativeSpeedException();
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
                throw negativeSpeedException();
            }
            else{
                return true;
            }
        }else {
            throw commandErrorException("position");
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
                    throw negativeSpeedException();
            }
            else{
                throw noPortInNameException();
            }
        }else{
            throw commandErrorException("destination");
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
                    cerr << "port name ERROR"<<endl;
                    //todo exception
                    return false;
                }
            }else{
                cerr << "Wrong list of arguments " << endl;
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
                    cerr << "port name ERROR"<< endl;
                    //todo exception
                    return false;
                }
            }
        }else{
            //todo exception
            cerr << "'unload_at' command is only for Freighter ship" << endl;
            return false;
        }
    }else if( command == "attack"){
        string shipToAttack;
        if(s->getType() == "Cruiser"){
            if(wordsCounter(args) == 1){
                ssargs >> shipToAttack;
                Ship* toAttack = Model::getInstance().getShipByName(shipToAttack);
                if(toAttack){
                    if(toAttack->getType() == "Freighter" || toAttack->getType() == "Patrol" ){
                        return  true;
                    }else{
                        cerr << "you cant attack a Cruiser"<< endl;
                        //todo exception
                        return false;
                    }

                }else{
                    cerr << "ship name ERROR"<< endl;
                    //todo exception
                    return false;
                }
            }
        }else{
            //todo exception
            cerr << "'attack' command is only for Cruiser ship" << endl;
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



