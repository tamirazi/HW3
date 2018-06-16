

#ifndef HW3_MODEL_H
#define HW3_MODEL_H

//Singleton object
class Model {
private:
    static Model* model;
    Model();
    ~Model(){delete model;};
    friend class ModelDestroyer;

public:
    static Model &getInstance();
    Model(const Model&) = delete;
    Model& operator= (const Model&) = delete;
    Model(const Model&&) = delete;
    Model& operator= (const Model&&) = delete;
};


#endif //HW3_MODEL_H
