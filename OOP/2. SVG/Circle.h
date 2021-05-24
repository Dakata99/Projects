#pragma once
#include "Figure.h"

class Circle:public Figure
{
private:
    double radius;
public:
    Circle(const double = 0.0, const double = 0.0, const double = 0.0, const std::string = "");


    const std::string getType()const override;
    double getStartX()const override;
    double getStartY()const override;
    double getRadius()const;

    const std::string getInfo()const override;
    void print()const override;
    void translate(const double, const double)override;
};
