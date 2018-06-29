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
    const char* what()const noexcept override{ return  "such Name does not exist in the current network";}
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
class commandErrorException: public exception{//if runtime input occurred  missing or wrong input statement
    int whatToPrint = 0;
    string where;
public:
    explicit commandErrorException(const string& where,int num = 0){commandErrorException::where = where; commandErrorException::whatToPrint = num;}

    const char* what()const noexcept override {
        if(!whatToPrint){
            string s = "Error: using " + where + " the input must have at least one name argument. ";
            return s.c_str();
        }
        else {
            string s = "Error: using " + where + " the input must have at least two name argument. ";
            return  s.c_str();}
    }

};

#endif //HW3_MYEXCEPTION_H
