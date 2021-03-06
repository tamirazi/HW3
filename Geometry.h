#include <iostream>
#include <iomanip>
using namespace std;


//----------------------------------------------------
// angle units conversion functions
double to_radians(double theta_d);
double to_degrees(double theta_r);
// class declarations
//----------------------------------------------------
typedef struct Point {
    double x;
    double y;
    Point(double x, double y);
    Point();
    void print() const;
    bool operator==(const Point& rhs);
} Point;
//----------------------------------------------------

struct Polar_vector;
typedef struct Cartesian_vector {
    Cartesian_vector(const struct Polar_vector & pv);
    Cartesian_vector();
    void operator=(const struct Polar_vector & pv);
    double delta_x;
    double delta_y;
} Cartesian_vector;

//----------------------------------------------------
typedef struct Polar_vector {
    Polar_vector(const Cartesian_vector & cv);
    Polar_vector();
    void operator=(const Cartesian_vector & cv);
    double r;
    double theta;
} Polar_vector;
//----------------------------------------------------
// prograss from one point to another
const Point progressByDestination(const Point& from,const Point& to, float speed);
const Point progressByCourse(const Point& from,double direction , float speed);
//----------------------------------------------------
// check the distance to attack... if possible return true if to fare return false
bool PossibleToAttack(const Point& attacker,const Point& defender , float range);
//regular distance between two points
double distance(const Point& from , const Point& to);