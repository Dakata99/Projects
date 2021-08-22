#ifndef _RECTANGLE_H_
#define _RECTANGLE_H_

#include <iostream>
#include <sstream>
#include <cmath>

#include "Figure.h"

class Rectangle : public Figure
{
private:
    double width, height;

public:
    Rectangle(const double&, const double&, const double&, const double&, const std::string&);
    
    const std::string get_type(void) const override;

    double get_start_x(void) const override;
    double get_start_y(void) const override;
    
    double get_end_x(void) const;
    double get_end_y(void) const;
    double get_width(void) const;
    double get_height(void) const;

    const std::string get_info(void) const override;
    void print(void) const override;
    void translate(const double&, const double&) override;
};

#endif