
#ifndef HW3_CONTROLLER_H
#define HW3_CONTROLLER_H


/* Controller
This class is responsible for controlling the Model and View according to interactions
with the user.
*/
#include "View.h"
#include <sstream>
#include "Model.h"
#include <memory>
class Controller {
public:
    Controller();
    ~Controller();

    // creates View object, runs the program by accepting user commands, then destroys View object
    void run();
    void Input(const string& portsFile);
private:
    shared_ptr<View> view_ptr;
    string user_command;
    string line;
};


#endif //HW3_CONTROLLER_H
