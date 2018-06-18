#include <iostream>
#include "Model.h"
#include "View.h"
class ModelDestroyer {
public:
    ~ModelDestroyer(){delete Model::model;}
} md;

int main() {
    View v;

    v.zoom(2);
    v.setOrigins(-10.3 , -10.3);
    v.setSize(25);
    v.show();

    v.zoom(5);
    v.setOrigins(-20.5 , -20.5);
    v.setSize(15);
    v.show();
    return 0;
}