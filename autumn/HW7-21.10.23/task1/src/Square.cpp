#include "../include/Square.hpp"



// Конструктор для создания квадрата с стороной
Square::Square(double side) : Rectangle(side, side) {}

// Печатаем информацию о квадрате
void Square::print(std::ostream& os) const
{
    os << "Square: Side = " << m_sides[0];
}
