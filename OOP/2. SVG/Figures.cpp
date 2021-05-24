#include "Menu.h"
#include "Figures.h"

void Figures::print()const
{
    for (size_t i = 0; i < figures.size(); i++)
    {
        std::cout << i + 1 << ". "; 
        figures[i]->print();
    }
}

void Figures::translate(const size_t index, const double vertical, const double horizontal)
{    
    if (index >= 1 && index <= figures.size())
        figures[index - 1]->translate(vertical, horizontal);
    else
        for (size_t i = 0; i < figures.size(); i++)
            figures[i]->translate(vertical, horizontal);
}

//TO CHECK ALL
bool Figures::inside(const Figure*& fig1, const Figure* fig2)const //check if fig2 is in fig1
{
    if (fig1->getType() == "rectangle" && fig2->getType() == "rectangle")
    {
        bool startX = (((Rectangle*)fig2)->getStartX()) >= (((Rectangle*)fig1)->getStartX()),
             startY = ((Rectangle*)fig2)->getStartY() >= (((Rectangle*)fig1)->getStartY()),
             endX = (((Rectangle*)fig2)->getEndX()) <= (((Rectangle*)fig1)->getEndX()),
             endY = (((Rectangle*)fig2)->getEndY()) <= (((Rectangle*)fig1)->getEndY());

        return (startX && startY) && (endX && endY); //if one point is out then the rectangle is out
    }
    else if (fig1->getType() == "rectangle" && fig2->getType() == "circle")
    {
        double startX = fabs(((Circle*)fig2)->getStartX()  - ((Circle*)fig2)->getRadius()),
               startY = fabs(((Circle*)fig2)->getStartY()  - ((Circle*)fig2)->getRadius()),
               endX = ((Circle*)fig2)->getStartX() + ((Circle*)fig2)->getRadius(), 
               endY = ((Circle*)fig2)->getStartY() + ((Circle*)fig2)->getRadius();

        bool top = startX >= ((Rectangle*)fig1)->getStartX(), 
             left = startY >= ((Rectangle*)fig1)->getStartY(),
             bottom = endX <= ((Rectangle*)fig1)->getEndX(),
             right = endY <= ((Rectangle*)fig1)->getEndY();

        return  top && left && bottom && right;
    }
    else if (fig1->getType() == "rectangle" && fig2->getType() == "line")
    {
        //TO CHECK
        bool startX = (((Line*)fig2)->getStartX()) >= (((Rectangle*)fig1)->getStartX()),
             startY = ((Line*)fig2)->getStartY() >= (((Rectangle*)fig1)->getStartY()),
             endX = (((Line*)fig2)->getEndX()) <= (((Rectangle*)fig1)->getEndX()),
             endY = (((Line*)fig2)->getEndY()) <= (((Rectangle*)fig1)->getEndY());

        return (startX && startY) && (endX && endY); //if one point of the line is out then the line is out of rectangle
    }
    else if (fig1->getType() == "circle" && fig2->getType() == "rectangle")
    {
        double startX = fig2->getStartX(),
               startY = fig2->getStartY(),
               endX = ((Rectangle*)fig2)->getEndX(),
               endY = ((Rectangle*)fig2)->getEndY();

        double dist1 = sqrt(pow(fig1->getStartX() - startX, 2) + pow(fig1->getStartY() - startY, 2)),
               dist2 = sqrt(pow(fig1->getStartX() - endX, 2) + pow(fig1->getStartY() - endY, 2));
        
        double radius = ((Circle*)fig1)->getRadius();
        if (dist1 <= radius && dist2 < radius || dist1 < radius && dist2 <= radius)
            return true;
        
        return false;
    }
    else if (fig1->getType() == "circle" && fig2->getType() == "circle")
    {
        double distance = sqrt(pow(fig1->getStartX() - fig2->getStartX(), 2) + pow(fig1->getStartY() - fig2->getStartY(), 2));
        if (distance <= ((Circle*)fig1)->getRadius() - ((Circle*)fig2)->getRadius())
            return true;
        
        return false;
    }
    else if (fig1->getType() == "circle" && fig2->getType() == "line")
    {
        double dist1 = sqrt(pow(fig1->getStartX() - fig2->getStartX(), 2) + pow(fig1->getStartY() - fig2->getStartY(), 2)),
               dist2 = sqrt(pow(fig1->getStartX() - ((Line*)fig2)->getEndX(), 2) + pow(fig1->getStartY() - ((Line*)fig2)->getEndY(), 2));
      
        if (dist1 <= ((Circle*)fig1)->getRadius() && dist2 <= ((Circle*)fig1)->getRadius())
            return true;
        
        return false;
    }

    return false;
}
void Figures::within(const Figure* figure)const 
{
    bool flag = false; //if there are no inside -> print the massage
    for (size_t i = 0, j = 1; i < figures.size(); i++)
    {
        if (inside(figure, figures[i]))
        {
            std::cout << j++ << ". ";
            figures[i]->print();
            flag = true;
        }
    }
    if (flag == false)
    { 
        std::cout << "No figures are located within "; figure->print();
    }
}

Figure* Figures::createRectangle(const std::string& x, const std::string& y, const std::string& width, const std::string& height, const std::string& color)
{
    return (new Rectangle(std::stod(x), std::stod(y), std::stod(width), std::stod(height), color));
}
Figure* Figures::createCircle(const std::string& x, const std::string& y, const std::string& radius, const std::string& color)
{
    return (new Circle(std::stod(x), std::stod(y), std::stod(radius), color));
}
Figure* Figures::createLine(const std::string& startX, const std::string& startY, const std::string& endX, const std::string& endY, const std::string& strokeWidth, const std::string& color)
{
    return (new Line(std::stod(startX), std::stod(startY), std::stod(endX), std::stod(endY), std::stod(strokeWidth), color));
}