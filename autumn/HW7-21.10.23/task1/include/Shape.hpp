#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <iostream>

// Абстрактный базовый класс для всех фигур
class Shape
{
public:
    // Чисто виртуальные функции расчёта площади, периметра и печати информации о фигуре
    virtual double getArea() const = 0;
    virtual double getPerimeter() const = 0;
    virtual void print(std::ostream& os) const = 0;
};

// Перегрузка оператора вывода '<<' для Shape
inline std::ostream& operator<<(std::ostream& os, const Shape& shape)
{
    shape.print(os);
    return os;
}

#endif
