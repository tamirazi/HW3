#include <iostream>
#include "Model.h"


class ModelDestroyer {
public:
    ~ModelDestroyer() {delete Model::model;}
} md;

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}