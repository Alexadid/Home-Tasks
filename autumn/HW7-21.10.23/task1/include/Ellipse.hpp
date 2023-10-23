#ifndef ELLIPSE_HPP
#define ELLIPSE_HPP
#include "Shape.hpp"
#include <iostream>



// Ellipse - производный класс Shape
class Ellipse : public Shape
{
public:
    Ellipse(double semiMajor, double semiMinor);
    double getArea() const override;
    double getPerimeter() const override;
    void print() const override;

protected:
    double m_semiMajor;
    double m_semiMinor;
};

#endif
