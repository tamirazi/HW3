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

    int mod;
    int x = xorigin;
    int max_x = (size * scale + xorigin) - scale;
    int max_y = size * scale + yorigin - scale;
    int max_print = yorigin;

    while((max_print + (scale * 3)) <= max_y){
        max_print += scale * 3;
    }

    mod = (max_y - max_print) / scale;

    for (int i = max_y , c = 0; i >= yorigin ; i -= scale , c++) {

        if((c % 3) == mod){
            cout << setw(4) << i << " ";


        }else{
            cout << setw(7);
        }

        for (int j = x; j <= max_x; j += scale) {
            //todo: if in (j , i) there is a ship print it
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

void View::setOrigins(int newXOrigin, int newYOrigin) {
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
