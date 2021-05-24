#pragma once
#include <string>

class Figure
{
protected:
    double startX, startY;
    std::string color;
public:
    Figure(const double = 0.0, const double = 0.0, const std::string = "");

    virtual const std::string getType()const = 0;
    virtual const std::string getInfo()const = 0;
    virtual double getStartX()const = 0;
    virtual double getStartY()const = 0;
    virtual void print()const = 0;
    virtual void translate(const double, const double) = 0;
};

