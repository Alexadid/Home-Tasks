#include "../include/Triangle.hpp"

// Конструктор для создания треугольника с 3 сторонами
Triangle::Triangle(double side1, double side2, double side3) : Polygon({side1, side2, side3}) {}

// Рассчитываем площадь, используя формулу Герона
double Triangle::getArea() const
{
    double area = getPerimeter() / 2;
    return sqrt(area * (area - m_sides[0]) * (area - m_sides[1]) * (area - m_sides[2]));
}

// Печатаем информацию о треугольнике
void Triangle::print(std::ostream& os) const
{
    os << "Triangle: Side1 = " << m_sides[0] << ", Side2 = " << m_sides[1] << ", Side3 = " << m_sides[2];
}
