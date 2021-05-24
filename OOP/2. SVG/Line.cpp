#include "Line.h"

Line::Line(const double sX, const double sY, const double eX, const double eY, const double strWidth, const std::string col)
            :Figure(sX, sY, col), endX(fabs(eX)), endY(fabs(eY)), strokeWidth(fabs(strWidth)){}

double Line::getEndX()const
{
    return endX;
}
double Line::getEndY()const
{
    return endY;
}
double Line::getStrokeWidth()const
{
    return strokeWidth;
}

const std::string Line::getType()const
{
    return "line";
}
const std::string Line::getInfo()const
{
    std::stringstream s;
    s << "\t<line x1=\"" <<startX << "\" y1=\"" << startY <<
            "\" x2=\"" << endX << "\" y2=\"" << endY <<
            "\" stroke-width=\"" << strokeWidth <<  
            "\" stroke=\"" + color + "\" />\n";

    return s.str();
}
double Line::getStartX()const
{
    return startX;
}
double Line::getStartY()const
{
    return startY;
}

void Line::print()const
{
    std::cout << "line " << startX << " " << startY << " " << endX << " " << endY << " " << strokeWidth << " " << color << std::endl;
}
void Line::translate(const double x, const double y)
{

    startX += x;
    startY += y;
    endX += x;
    endY += y;
}