#include "../include/Circle.hpp"
#include <cmath>



// Конструктор для создания круга с радиусом
Circle::Circle(double radius) : Ellipse(radius, radius) {}

// Рассчитываем периметр круга
double Circle::getPerimeter() const
{
    return 2 * M_PI * m_semiMajor;
}

// Печатаем информацию о круге
void Circle::print(std::ostream& os) const
{
    os << "Circle: Radius = " << m_semiMajor;
}
