#include "View.h"
#include <sstream>
#ifndef HW3_CONTROLLER_H
#define HW3_CONTROLLER_H


/* Controller
This class is responsible for controlling the Model and View according to interactions
with the user.
*/

class Controller {
public:
    Controller();
    ~Controller();

    // creates View object, runs the program by accepting user commands, then destroys View object
    void run();

private:
    View* view_ptr;
    string user_command;
    string line;
};


#endif //HW3_CONTROLLER_H
