//
// Created by tamir on 6/15/18.
//

#include "Controller.h"

Controller::Controller() {
    view_ptr = new View();
    //set this view_ptr to the model

}

Controller::~Controller() {
    delete(view_ptr);
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
        if(user_command == "exit"){
            return;
            //check for memory leak
        }

    }


}
