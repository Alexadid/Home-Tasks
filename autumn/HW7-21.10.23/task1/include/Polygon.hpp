#ifndef POLYGON_HPP
#define POLYGON_HPP
#include "Shape.hpp"
#include <vector>



// Базовый класс для многоугольников
class Polygon : public Shape
{
public:
    Polygon(const std::vector<double>& sides);
    ~Polygon();
    double getPerimeter() const override;
    // Явно переопределяем виртуальную функцию из Shape
    void print(std::ostream& os) const override;

protected:
    std::vector<double> m_sides;
};

#endif
