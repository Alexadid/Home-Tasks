#include "../include/Polygon.hpp"
#include <iostream>

// Конструктор для хранения сторон
Polygon::Polygon(const std::vector<double>& sides) : m_sides(sides) {}

// Деструктор для очистки аллоцированной памяти (не нужен в данном случае, так как используется вектор)
Polygon::~Polygon() {}

// Подсчитываем периметр
double Polygon::getPerimeter() const
{
    // Для прямоугольников нам нужно учесть, что две стороны соответственно равны, так что мы корректируем расчёт...
    if (m_sides.size() == 2)
    {
        return 2 * (m_sides[0] + m_sides[1]);
    } else
    {
        double perimeter = 0;
        for (double side : m_sides)
        {
            perimeter += side;
        }
        return perimeter;
    }
}

void Polygon::print(std::ostream& os) const
{
    os << "Polygon: Sides = ";

    for (size_t i = 0; i < m_sides.size(); ++i)
    {
        os << m_sides[i];
        if (i < m_sides.size() - 1) { os << ", "; }
    }
}
