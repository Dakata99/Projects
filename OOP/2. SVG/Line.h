#pragma once
#include "Figure.h"

class Line:public Figure
{
private:
    double endX, endY;
    double strokeWidth;
public:
    Line(const double = 0.0, const double = 0.0, const double = 0.0, const double = 0.0, const double = 0.0, const std::string = "");

    double getEndX()const;
    double getEndY()const;
    double getStrokeWidth()const;

    const std::string getType()const override;
    const std::string getInfo()const override;
    double getStartX()const override;
    double getStartY()const override;
    void print()const override;
    void translate(const double, const double) override;
};
