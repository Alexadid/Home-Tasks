#include <iostream>



// Базовый класс 
class Shape
{
public:
    Shape(const std::string& name) : name(name) {}

    virtual ~Shape() {}

    virtual double area() const = 0;

    void printName() const
    {
        std::cout << "Name: " << name << std::endl;
    }

private:
    std::string name;
};

// Двухмерные фигуры, дочерний класс Shape
class TwoDimensionalShape : public Shape
{
public:
    TwoDimensionalShape(const std::string& name) : Shape(name) {}

    virtual double perimeter() const = 0;
};

// Трёхмерные фигуры, дочерний класс Shape
class ThreeDimensionalShape : public Shape
{
public:
    ThreeDimensionalShape(const std::string& name) : Shape(name) {}

    virtual double volume() const = 0;
};

// Лента Мёбиуса - объект, который в некотором роде и двумерный и трёхмерный
// Дочерний класс как TwoDimensionalShape, так и ThreeDimensionalShape
class MobiusStrip : public TwoDimensionalShape, public ThreeDimensionalShape
{
public:
    MobiusStrip() : TwoDimensionalShape("Mobius 2D"), ThreeDimensionalShape("Mobius 3D") {}

    double area() const override
    {
        return 0.0;
    }

    double perimeter() const override
    {
        return 0.0;
    }

    double volume() const override
    {
        return 0.0;
    }
};

int main()
{
    MobiusStrip mobius;

    // Неоднозначность, суть проблемы 'Алмаза Смерти', возникает из-за множественного наследования
    // Это вызовет ошибку компиляции, так как компилятор не знает, метод какого класса использовать
    // mobius.printName();

    // Явно указываем, метод какого класса вызвать
    // Проблемы больше нет, хотя в реальности нужно было бы делать класс Shape сугубо виртуальным
    mobius.TwoDimensionalShape::printName();
    mobius.ThreeDimensionalShape::printName();

    return 0;
}
