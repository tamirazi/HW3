//
// Created by tamir on 6/15/18.
//

#include "Model.h"

Model *Model::model = nullptr;

Model & Model::getInstance() {
    if (model == nullptr)
        model = new Model();
    return *model;
}

Model::Model() {
    //initialize all Model objects here
}

