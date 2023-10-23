#include "../include/Rectangle.hpp"



// Конструктор для создания прямоугольника с длиной и шириной
Rectangle::Rectangle(double length, double width) : Polygon(new double[2] {length, width}, 4) {}

// Рассчитываем площадь, как произедение длины на ширину
double Rectangle::getArea() const
{
    return m_sides[0] * m_sides[1];
}

// Печатаем информацию о прямоугольнике
void Rectangle::print() const
{
    std::cout << "Rectangle: Length = " << m_sides[0] << ", Width = " << m_sides[1] << std::endl;
}
