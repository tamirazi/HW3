#include "Geometry.h"
#include <cmath>
#include <ctgmath>
#define PI 3.14159265
const double pi = 2. * atan2(1., 0.);
double to_radians(double theta_d)
{
    return theta_d * pi / 180.0;
}

double to_degrees(double theta_r)
{
    return theta_r * 180.0 / pi;
}
// construct a Cartesian_vector from a Polar_vector
Cartesian_vector::Cartesian_vector(const Polar_vector& pv) {
    delta_x = pv.r * cos(pv.theta);
    delta_y = pv.r * sin(pv.theta);
}
Cartesian_vector::Cartesian_vector()
{
    delta_x = 0.0;
    delta_y = 0.0;
}
void Cartesian_vector::operator=(const Polar_vector& pv)
{
    delta_x = pv.r * cos(pv.theta);
    delta_y = pv.r * sin(pv.theta);
}
// construct a Polar_vector from a Cartesian_vector
Polar_vector::Polar_vector(const Cartesian_vector& cv) {
    r = sqrt((cv.delta_x * cv.delta_x) + (cv.delta_y * cv.delta_y));
    /* atan2 will return a negative angle for Quadrant III, IV, must translate to I, II */
    theta = atan2(cv.delta_x, cv.delta_y);
    if (theta < 0.)
        theta = 2. * pi + theta; // normalize theta positive
}
Polar_vector::Polar_vector()
{
    r = 0.0;
    theta = 0.0;
}
void Polar_vector::operator=(const Cartesian_vector& cv)
{
    r = sqrt((cv.delta_x * cv.delta_x) + (cv.delta_y * cv.delta_y));
    /* atan2 will return a negative angle for Quadrant III, IV, must translate to I, II */
    theta = atan2(cv.delta_x, cv.delta_y);
    if (theta < 0.)
        theta = 2. * pi + theta; // normalize theta positive
}

Point::Point(double x, double y) : x(x), y(y)
{
}

Point::Point()
{
    x = 0.0;
    y = 0.0;
}

void Point::print() const
{
    cout << setprecision(2) << "(" << x << ", " << y << ")";
}

bool Point::operator==(const Point & rhs)
{
    return x == rhs.x && y == rhs.y;
}

const Point prograssByDestination(const Point& from,const Point& to , float speed){
    Point ans(0,0);
    Cartesian_vector cv;
    cv.delta_x = to.x - from.x;
    cv.delta_y = to.y - from.y;
    Polar_vector pv(cv);
    double direction = to_degrees(pv.theta);
    ans.x = from.x + sin(direction*pi/180)*speed;
    ans.y = from.y + cos(direction*pi/180)*speed;
    Cartesian_vector check;
    check.delta_x = to.x - ans.x;
    check.delta_y = to.y - ans.y;
    Polar_vector pcheck(check);
    if((float)to_degrees(pv.theta) != (float )to_degrees(pcheck.theta))
        return to;
    return Point(ans.x,ans.y);
}

const Point prograssByCourse(const Point& from,double direction , float speed){
    Point ans(0,0);
    ans.x = from.x + sin(direction*pi/180)*speed;
    ans.y = from.y + cos(direction*pi/180)*speed;
    return Point(ans.x,ans.y);
}

bool PossibleToAttacck(const Point& attacker,const Point& defender , float area){
    Cartesian_vector cv;
    cv.delta_x = attacker.x - defender.x;
    cv.delta_y = attacker.y - defender.y;
    Polar_vector pv(cv);
    return pv.r <= area;
}

double distance(const Point& from , const Point& to){
    double x , y;
    x = from.x - to.x;
    y = from.y - to.y;
    return sqrt( pow(x,2) + pow (y,2));

}