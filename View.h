#include <iostream>
#include <string>
#include <vector>

#ifndef HW3_VIEW_H
#define HW3_VIEW_H


using namespace std;
class View {

private:
    int size , scale , xorigin , yorigin;
    vector<vector<string>>* map;


public:
    View();
    void show();
    void setOrigins(int x , int y);
    void zoom(int num);
    void setDefault();
    void setSize(int num);

};


#endif //HW3_VIEW_H
