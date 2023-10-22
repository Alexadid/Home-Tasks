#include "include/Shape.hpp"
#include "include/Rectangle.hpp"
#include "include/Square.hpp"
#include "include/Ellipse.hpp"
#include "include/Circle.hpp"
#include "include/Triangle.hpp"



int main()
{
    const int numShapes = 5;
    Shape* shapes[numShapes];

    // Создаём различные фигуры и зраним из в массива указателей типа Shape
    shapes[0] = new Rectangle(5.0, 3.0);
    shapes[1] = new Square(4.0);
    shapes[2] = new Ellipse(6.0, 4.0);
    shapes[3] = new Circle(3.0);
    shapes[4] = new Triangle(3.0, 4.0, 5.0);

    // Отображаем информацию о каждой фигуре
    for (int i = 0; i <= numShapes; i++)
    {
        shapes[i]->print();
        std::cout << "Area: " << shapes[i]->getArea() << ", Perimeter: " << shapes[i]->getPerimeter() << "\n";
        std::cout << std::endl;
    }

    // Очистка динамически аллоцированной памяти
    for (int i = 0; i < numShapes; i++)
    {
        delete shapes[i];
    }

    return 0;
}
