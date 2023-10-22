#ifndef SHAPE_HPP
#define SHAPE_HPP



// Абстрактный базовый класс для всех фигур
class Shape
{
public:
    // Чисто вирульные функции расчёта площади, периметра и печати информации о фигуре
    virtual double getArea() const = 0;
    virtual double getPerimeter() const = 0;
    virtual void print() const = 0;
};

#endif
