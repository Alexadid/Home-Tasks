#ifndef POLYGON_HPP
#define POLYGON_HPP
#include "Shape.hpp"



// Базовый класс для многоульников
class Polygon : public Shape
{
public:
    Polygon(double* sides, int numSides);
    ~Polygon();
    double getPerimeter() const override;

protected:
    double* sides;
    int numSides;
};

#endif
