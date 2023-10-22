#ifndef CIRCLE_HPP
#define CIRCLE_HPP
#include "Ellipse.hpp"
#include <iostream>



// Circle - производный класс Ellipse
class Circle : public Ellipse
{
public:
    Circle(double radius);
    void print() const override;
};

#endif
