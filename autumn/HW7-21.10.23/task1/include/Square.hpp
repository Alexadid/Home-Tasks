#ifndef SQUARE_HPP
#define SQUARE_HPP
#include "Rectangle.hpp"
#include <iostream>



// Square - производный класс Rectangle
class Square : public Rectangle
{
public:
    Square(double side);
    void print() const override;
};

#endif
