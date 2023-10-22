#include "../include/Square.hpp"



// Конструктор для создания квадрата с стороной
Square::Square(double side) : Rectangle(side, side) {}

// Печатаем информацию о квадрате
void Square::print() const
{
    std::cout << "Square: Side = " << sides[0] << std::endl;
}
