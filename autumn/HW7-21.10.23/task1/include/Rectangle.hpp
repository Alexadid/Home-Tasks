#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP
#include "Polygon.hpp"
#include <iostream>



// Rectangle - производный класс Polygon
class Rectangle : public Polygon
{
public:
    Rectangle(double length, double width);
    double getArea() const override;
    // Явно переопределяем виртуальную функцию из Shape
    void print(std::ostream& os) const override;
};

#endif
