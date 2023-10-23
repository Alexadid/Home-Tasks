#include "../include/Ellipse.hpp"
#include <cmath>



//  Конструктор для создания эллипса с большой (semi-major) и малой (semi-minor) осями
Ellipse::Ellipse(double semiMajor, double semiMinor) : m_semiMajor(semiMajor), m_semiMinor(semiMinor) {}

// Рассчитываем площадь эллипса
double Ellipse::getArea() const
{
    return M_PI * m_semiMajor * m_semiMinor;
}

// Рассчитываем приблизительный периметр
double Ellipse::getPerimeter() const
{
    return 2 * M_PI * sqrt((m_semiMajor * m_semiMajor + m_semiMinor * m_semiMinor) / 2);
}

// Печатаем информацию об эллипсе
void Ellipse::print() const
{
    std::cout << "Ellipse: Semi-Major Axis = " << m_semiMajor << ", Semi-Minor Axis = " << m_semiMinor << std::endl;
}
