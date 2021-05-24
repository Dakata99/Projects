#include "Figure.h"

Figure::Figure(const double x, const double y, const std::string col)
{
    startX = fabs(x);
    startY = fabs(y);
    color = col;    
}