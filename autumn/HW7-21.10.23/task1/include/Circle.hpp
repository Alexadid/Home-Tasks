#ifndef CIRCLE_HPP
#define CIRCLE_HPP
#include "Ellipse.hpp"
#include <iostream>



// Circle - производный класс Ellipse
class Circle : public Ellipse
{
public:
    Circle(double radius);
    double getPerimeter() const override;
    // Явно переопределяем виртуальную функцию из Shape
    void print(std::ostream& os) const override;
};

#endif
