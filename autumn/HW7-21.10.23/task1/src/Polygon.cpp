#include "../include/Polygon.hpp"



// Конструктор для хранения сторон и их количества
Polygon::Polygon(double* sides, int numSides) : sides(new double[numSides]), numSides(numSides)
{
    for (int i = 0; i < numSides; i++)
    {
        this->sides[i] = sides[i];
    }
}

// Деструктор для очистки аллоцированной памяти
Polygon::~Polygon()
{
    delete[] sides;
}

// Подсчитываем периметр суммирую длины сторон
double Polygon::getPerimeter() const
{
    double perimeter = 0;
    for (int i = 0; i < numSides; i++)
    {
        perimeter += sides[i];
    }
    return perimeter;
}
