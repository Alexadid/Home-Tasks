#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP
#include "Polygon.hpp"
#include <iostream>
#include <cmath>



// Triangle - производный класс Polygon
class Triangle : public Polygon
{
public:
    Triangle(double side1, double side2, double side3);
    double getArea() const override;
    // Явно переопределяем виртуальную функцию из Shape
    void print(std::ostream& os) const override;
};

#endif
