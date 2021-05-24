#include "Circle.h"

Circle::Circle(const double cx, const double cy, const double r, const std::string col)
    :Figure(cx, cy, col), radius(fabs(r)){}

const std::string Circle::getType()const
{
    return "circle";
}
const std::string Circle::getInfo()const
{
    std::stringstream s;
    s << "\t<circle cx=\"" << startX << "\" cy=\"" << startY <<
           "\" r=\"" << radius << "\" fill=\"" + color + "\" />\n";

    return s.str();
}
double Circle::getStartX()const
{
    return startX;
}
double Circle::getStartY()const
{
    return startY;
}
double Circle::getRadius()const
{
    return radius;
}

void Circle::print()const
{
    std::cout << "circle " << startX << " " << startY << " " << radius << " " << color << std::endl;
}
void Circle::translate(const double x, const double y)
{
    startX += x;
    startY += y;
}