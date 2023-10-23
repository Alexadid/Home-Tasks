#include "../include/Triangle.hpp"



// Конструктор для создания триугольника с 3 сторонами
Triangle::Triangle(double side1, double side2, double side3) : Polygon(new double[3] {side1, side2, side3}, 3) {}

// Рассчитываем площадь, используя формулу Герона
double Triangle::getArea() const
{
    double s = getPerimeter() / 2;
    return sqrt(s * (s - m_sides[0]) * (s - m_sides[1]) * (s - m_sides[2]));
}

// Печатаем информацию о треугольнике
void Triangle::print() const
{
    std::cout << "Triangle: Side1 = " << m_sides[0] << ", Side2 = " << m_sides[1] << ", Side3 = " << m_sides[2] << std::endl;
}
