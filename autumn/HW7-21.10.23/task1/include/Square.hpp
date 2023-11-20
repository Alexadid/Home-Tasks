#ifndef SQUARE_HPP
#define SQUARE_HPP
#include "Rectangle.hpp"
#include <iostream>



// Square - производный класс Rectangle
class Square : public Rectangle
{
public:
    Square(double side);
    // Явно переопределяем виртуальную функцию из Shape
    void print(std::ostream& os) const override;
};

#endif
