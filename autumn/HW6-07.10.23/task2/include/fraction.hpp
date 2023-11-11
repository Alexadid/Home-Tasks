#ifndef FRACTION_HPP
#define FRACTION_HPP

#include <iostream>

class Fraction
{
private:
    unsigned int numerator;
    unsigned int denominator;
    bool isNegative;

    void reduce();

public:
    Fraction();
    Fraction(int num, int denom);
    Fraction(double value);
    explicit operator double() const;

    unsigned int getNumerator() const;
    unsigned int getDenominator() const;
    bool isNegativeFraction() const;

    friend std::ostream& operator<<(std::ostream& out, const Fraction& fraction);
    friend std::istream& operator>>(std::istream& in, Fraction& fraction);

    Fraction& operator++();
    Fraction& operator--();
    Fraction operator++(int);
    Fraction operator--(int);
};

// Свободные функции для арифметических операторов и операторов сравнения 
Fraction operator+(const Fraction& lhs, const Fraction& rhs);
Fraction operator-(const Fraction& lhs, const Fraction& rhs);
Fraction operator*(const Fraction& lhs, const Fraction& rhs);
Fraction operator/(const Fraction& lhs, const Fraction& rhs);

bool operator==(const Fraction& lhs, const Fraction& rhs);
bool operator!=(const Fraction& lhs, const Fraction& rhs);
bool operator<(const Fraction& lhs, const Fraction& rhs);
bool operator>(const Fraction& lhs, const Fraction& rhs);
bool operator<=(const Fraction& lhs, const Fraction& rhs);
bool operator>=(const Fraction& lhs, const Fraction& rhs);

#endif
