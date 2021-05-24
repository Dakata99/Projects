#include "Rectangle.h"
#include <sstream>

Rectangle::Rectangle(const double x, const double y, const double wid, const double hei, const std::string color)
                :Figure(x, y, color), width(fabs(wid)), height(fabs(hei)){}

const std::string Rectangle::getType()const
{
    return "rectangle";
}

double Rectangle::getStartX()const
{
    return startX;
}
double Rectangle::getStartY()const
{
    return startY;
}
double Rectangle::getEndX()const
{
    return startX + width;
}
double Rectangle::getEndY()const
{
    return startY + height;
}
double Rectangle::getWidth()const
{
    return width;
}
double Rectangle::getHeight()const
{
    return height;
}
const std::string Rectangle::getInfo()const
{
    std::stringstream s;
    s << "\t<rect x=\"" << startX << "\" y=\"" << startY << 
           "\" width=\"" << width  << "\" height=\"" << height <<
           "\" fill=\"" + color + "\" />\n";

    return s.str();
}

void Rectangle::print()const
{
    std::cout << "rectangle " << startX << " " << startY << " " << width << " " << height << " " << color << std::endl;
}
void Rectangle::translate(const double x, const double y)
{
    startX += x;
    startY += y;
}