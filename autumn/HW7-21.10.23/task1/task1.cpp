#include "include/Shape.hpp"
#include "include/Rectangle.hpp"
#include "include/Square.hpp"
#include "include/Ellipse.hpp"
#include "include/Circle.hpp"
#include "include/Triangle.hpp"



int main()
{
    std::vector<Shape*> shapes;

    // Создаём различные фигуры и зраним из в массива указателей типа Shape
    shapes.push_back(new Rectangle(5.0, 3.0));
    shapes.push_back(new Square(4.0));
    shapes.push_back(new Ellipse(6.0, 4.0));
    shapes.push_back(new Circle(3.0));
    // Египетский треугольник - для упрощения проверки правильности вычислений
    shapes.push_back(new Triangle(3.0, 4.0, 5.0));

    // Отображаем информацию о каждой фигуре
    for (Shape* shape : shapes)
    {
        std::cout << *shape << std::endl;
        std::cout << "Area: " << shape->getArea() << ", Perimeter: " << shape->getPerimeter() << std::endl;
        std::cout << std::endl;
    }

    return 0;
}
