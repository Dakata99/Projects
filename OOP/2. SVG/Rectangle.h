#pragma once
#include "Figure.h"

class Rectangle:public Figure
{
private:
    double width, height;
public:
    Rectangle(const double = 0.0, const double = 0.0, const double = 0.0, const double = 0.0, const std::string = "");
    
    const std::string getType()const override;

    double getStartX()const override;
    double getStartY()const override;
    
    double getEndX()const;
    double getEndY()const;
    double getWidth()const;
    double getHeight()const;

    const std::string getInfo()const override;
    void print()const override;
    void translate(const double, const double) override;
};
