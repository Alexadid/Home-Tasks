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
    explicit operator double() const;

    unsigned int getNumerator() const;
    unsigned int getDenominator() const;
    bool isNegativeFraction() const;

    friend std::ostream& operator<<(std::ostream& out, const Fraction& fraction);
    friend std::istream& operator>>(std::istream& in, Fraction& fraction);

    Fraction operator+(const Fraction& other) const;
    Fraction operator-(const Fraction& other) const;
    Fraction operator*(const Fraction& other) const;
    Fraction operator/(const Fraction& other) const;

    bool operator==(const Fraction& other) const;
    bool operator!=(const Fraction& other) const;

    Fraction& operator++();
    Fraction& operator--();
    Fraction operator++(int);
    Fraction operator--(int);
};

#endif
