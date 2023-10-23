#include "../include/Polygon.hpp"



// Конструктор для хранения сторон и их количества
Polygon::Polygon(double* sides, int numSides) : m_sides(new double[numSides]), m_numSides(numSides)
{
    for (int i = 0; i < numSides; i++)
    {
        this->m_sides[i] = sides[i];
    }
}

// Деструктор для очистки аллоцированной памяти
Polygon::~Polygon()
{
    delete[] m_sides;
}

// Подсчитываем периметр суммирую длины сторон
double Polygon::getPerimeter() const
{
    double perimeter = 0;
    for (int i = 0; i < m_numSides; i++)
    {
        perimeter += m_sides[i];
    }
    return perimeter;
}
