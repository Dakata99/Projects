#ifndef _LINE_H_
#define _LINE_H_

#include <cmath>
#include <iostream>
#include <sstream>

#include "Figure.h"

class Line:public Figure
{
private:
    double end_x, end_y;
    double stroke_width;

public:
    Line(const double&, const double&, const double&, const double&, const double&, const std::string&);

    double get_end_x(void) const;
    double get_end_y(void) const;
    double get_stroke_width(void) const;

    const std::string get_type(void) const override;
    const std::string get_info(void) const override;
    double get_start_x(void) const override;
    double get_start_y(void) const override;
    void print(void) const override;
    void translate(const double&, const double&) override;
};

#endif