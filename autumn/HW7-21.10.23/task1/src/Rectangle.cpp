#include "../include/Rectangle.hpp"

// Конструктор для создания прямоугольника с длиной и шириной
Rectangle::Rectangle(double length, double width) : Polygon({length, width}) {}

// Рассчитываем площадь, как произведение длины на ширину
double Rectangle::getArea() const
{
    return m_sides[0] * m_sides[1];
}

// Печатаем информацию о прямоугольнике
void Rectangle::print(std::ostream& os) const
{
    os << "Rectangle: Length = " << m_sides[0] << ", Width = " << m_sides[1];
}
