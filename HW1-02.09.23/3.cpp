#include <iostream>
#include <cmath>

// Процедура, решающая квадратное уравнение
// Рассматриваются все случаи
void solveEquation(double coefficientA, double coefficientB, double coefficientC)
{
    // Рассматриваем первый коэффициент
    // В случае равенства перед нами не квадратное уравнение...
    if (coefficientA == 0)
    {
        if (coefficientB == 0)
        {
            if (coefficientC == 0)
            {
                std::cout << "Infinite solutions (0 = 0)" << std::endl;
            } else
            {
                std::cout << "No solutions (0 != " << coefficientC << ")" << std::endl;
            }
        } else
        {
            double x = (-1) * coefficientC / coefficientB;
            std::cout << "One real root: x = " << x << std::endl;
        }
    } else
    {
        double discriminant = coefficientB * coefficientB - 4 * coefficientA * coefficientC;
        
        if (discriminant > 0)
        {
            double root1 = ((-1) * coefficientB + sqrt(discriminant)) / (2 * coefficientA);
            double root2 = ((-1) * coefficientB - sqrt(discriminant)) / (2 * coefficientA);
            std::cout << "Two real and distinct roots: x1 = " << root1 << " and x2 = " << root2 << std::endl;
        } else if (discriminant == 0)
        {
            double root = (-1) * coefficientB / (2 * coefficientA);
            std::cout << "One real root: x = " << root << std::endl;
        } else
        {
            double realPart = (-1) * coefficientB / (2 * coefficientA);
            double imaginaryPart = sqrt(-discriminant) / (2 * coefficientA);
            std::cout << "Two complex roots: x1 = " << realPart << " + " << imaginaryPart << "i and x2 = " << realPart << " - " << imaginaryPart << "i" << std::endl;
        }
    }
}

int main()
{
    double coefficientA, coefficientB, coefficientC;

    // Считываем коэффициенты квадратного уравнения
    std::cout << "Enter coefficients a, b, and c quadratic equation: ";
    std::cin >> coefficientA >> coefficientB >> coefficientC;
    
    solveEquation(coefficientA, coefficientB, coefficientC);
    
    return 0;
}
