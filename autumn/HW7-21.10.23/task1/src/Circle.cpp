#include "../include/Circle.hpp"



// Конструктор для создания круга с радиусом
Circle::Circle(double radius) : Ellipse(radius, radius) {}

// Печатаем информацию о круге
void Circle::print() const
{
    std::cout << "Circle: Radius = " << semiMajor << std::endl;
}
