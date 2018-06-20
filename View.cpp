//
// Created by tamir on 6/15/18.
//

#include "View.h"
#include <iomanip>

View::View():size(25) , scale(2) , xorigin(-10) , yorigin(-10) {


}

void View::show() {
    cout << "Display size: " << size << ", ";
    cout << "scale: " << scale << ", ";
    cout << "origin: (" << xorigin << " , " << yorigin << ")" << endl;

    double x = xorigin;
    double max_x = (size * scale + xorigin) - scale;
    double max_y = size * scale + yorigin - scale;
    double enterY = yorigin + (size-1)/3*(scale*3);

    for (double i = max_y , c = 0; i >= yorigin ; i -= scale , c++) {

        double thisScale = max_y-scale*c;
        if(thisScale == enterY){
            cout << setw(5)<< thisScale <<" ";
            enterY -= 3*scale;
        }else { cout << setw(8);}

        for (double j = x; j <= max_x; j += scale) {
            //todo: if in (j , i) there is a ship print it
            vector<shared_ptr<SimObject>>::iterator iter = objects.begin();
            for(;iter != objects.end() ; ++iter){
                double dirX = iter.operator*().operator*().getLocation().x;
                double dirY = iter.operator*().operator*().getLocation().y;
                if(dirX >= j && dirX < j+scale && dirY >= i && dirY < i+scale ){
                    cout << iter.operator*().operator*().getName().substr(0,2);
                    break;
                }
            }
            if(iter == objects.end())
                cout << ". ";
        }

        cout << endl;
    }

    for (int k = 0; k < size ; ++k) {
        if((k % 3) == 0){
            cout << setw(6) << x ;
            x += (3 * scale);

        }else{
            cout << setw(7);
        }

    }

    cout << endl << endl;

}

void View::setDefault() {
    size = 25;
    scale = 2;
    xorigin = 0;
    yorigin = 0;
}

void View::setOrigins(double newXOrigin, double newYOrigin) {
    xorigin = newXOrigin;
    yorigin = newYOrigin;
}

void View::setSize(int newSize) {
    if(newSize > 6 && newSize <= 30){
        size = newSize;
    }
    else
        cerr << "setSize function: " << "illegal argument" << endl;

    //the controller need to handle error this is extra test
}

void View::zoom(int num) {
    if(num >= 1){
        scale = num;
    }else
        cerr << "zoom function: " << "illegal argument" << endl;

}

void View::getObjects(const vector<shared_ptr<SimObject>> &objVector) {
    objects = objVector;
}
