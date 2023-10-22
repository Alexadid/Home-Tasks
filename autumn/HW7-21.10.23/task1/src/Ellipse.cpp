#include "../include/Ellipse.hpp"
#include <cmath>



//  Конструктор для создания эллипса с большой (semi-major) и малой (semi-minor) осями
Ellipse::Ellipse(double semiMajor, double semiMinor) : semiMajor(semiMajor), semiMinor(semiMinor) {}

// Рассчитываем площадь эллипса
double Ellipse::getArea() const
{
    return M_PI * semiMajor * semiMinor;
}

// Рассчитываем приблизительный периметр
double Ellipse::getPerimeter() const
{
    return 2 * M_PI * sqrt((semiMajor * semiMajor + semiMinor * semiMinor) / 2);
}

// Печатаем информацию об эллипсе
void Ellipse::print() const
{
    std::cout << "Ellipse: Semi-Major Axis = " << semiMajor << ", Semi-Minor Axis = " << semiMinor << std::endl;
}
