//
// Created by bar on 6/29/2018.
//

#ifndef HW3_MYEXCEPTION_H
#define HW3_MYEXCEPTION_H
#include <iostream>
#include <exception>
using namespace std;
class shipNotFoundException: public exception{//ship not found in program exception
public:
    const char* what()const noexcept override{ return  "such ship Name does not exist in the current network";}
};
class negativeSpeedException: public exception{//the speed is negative
public:
    const char* what()const noexcept override{ return  "Error - your command contains Negative speed for transport";}
};
class noPortInNameException: public exception{//the input name port is incorrect
public:
    const char* what()const noexcept override{ return  "Error - your Name isn't  a port Name in the Map";}
};
class formatErrorException: public exception{//the input for the program was incorrect ,prints replay how to run it properly
public:
    const char* what()const noexcept override{ return  "FORMAT ERROR: needed ./<prog> -i <Ports.data> , Try again and do it correct this Time";}
};
class noSuchCommandException: public exception{//if the command is not defined throw exception
public:
    const char* what()const noexcept override { return  "THERE is no such Command";}
};
class fileNotFoundException: public exception{//if file not found
public:
    const char* what()const noexcept override { return  "cannot open file";}
};
class viewException: public exception{
public:
    const char* what()const noexcept override{ return  "view size scale is 3 - 60";}
};
class zoomException: public exception{
public:
    const char* what()const noexcept override{ return  "zoom must be bigger than 0";}
};
class cruiserException: public exception{
public:
    const char* what()const noexcept override{ return  "Cruiser cannot attack Cruiser";}
};



class commandErrorException: public exception{//if runtime input occurred  missing or wrong input statement

    string s;
public:
    explicit commandErrorException(const string& where,int num){
        if(num == 1){
            s = "Error: using " + where + " the input must have one name argument. ";
        }
        if(num == 2){
             s = "Error: using " + where + " the input must have two name argument. ";
        }
        if(num == 3){
             s = "Error: using " + where + " the input must have three name argument. ";
        }
        if(num == 0){
             s = "Error: using " + where + " not enough arguments. ";
        }
    };

    const char* what()const noexcept override {
        return s.c_str();
    }

};

class wrongCommandToShip: public exception{
    string t , c , error ;

public:
    explicit wrongCommandToShip(const string& type , const string& command):t(type) , c(command){
        error = "Error: using " +  c  + " in ship of type " + t + ". ";
    };

    const char* what()const noexcept override{ return  error.c_str();}
};

class maxSpeedException: public exception{
    string error;
public:
    explicit maxSpeedException(const string& type){
        error = "Error: speed is over the maximum speed of " +  type ;
    };
    const char* what()const noexcept override{ return  error.c_str();}
};

#endif //HW3_MYEXCEPTION_H
