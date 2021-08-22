#ifndef _CIRCLE_H_
#define _CIRCLE_H_

#include <cmath>
#include <iostream>
#include <sstream>

#include "Figure.h"

class Circle : public Figure
{
private:
    double radius;

public:
    Circle(const double&, const double&, const double&, const std::string&);


    const std::string get_type(void) const override;
    double get_start_x(void) const override;
    double get_start_y(void) const override;
    double getRadius(void) const;

    const std::string get_info(void) const override;
    void print(void) const override;
    void translate(const double&, const double&) override;
};

#endif