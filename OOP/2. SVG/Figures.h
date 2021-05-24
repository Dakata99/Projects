#pragma once
#include <vector>
#include "Figure.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Line.h"

class Menu;

class Figures
{
private:
    friend Menu;
    std::vector<Figure*> figures;

private:
    void print()const;
    void within(const Figure*)const;
    void translate(const size_t, const double, const double);

    bool inside(const Figure*&, const Figure*)const;
    Figure* createRectangle(const std::string&, const std::string&, const std::string&, const std::string&, const std::string&);
    Figure* createCircle(const std::string&, const std::string&, const std::string&, const std::string&);
    Figure* createLine(const std::string&, const std::string&, const std::string&, const std::string&, const std::string&, const std::string&);
};
