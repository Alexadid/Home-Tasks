#include "../include/fraction.hpp"
#include <stdexcept>
#include <numeric>


// Функция-член для упрощения дроби
// Писать собственный gcd не решился - и так много времени потратил
// Функция приватна, т.к. её вызов предполагается только изнутри
void Fraction::reduce()
{
    if (numerator == 0)
    {
        denominator = 1;
        isNegative = false;
    } else
    {
        unsigned int gcd = std::gcd(numerator, denominator);
        numerator /= gcd;
        denominator /= gcd;
    }
}

// Конструктор по умолчанию
Fraction::Fraction() : numerator(0), denominator(1), isNegative(false) {}

// Параметризованный конструктор
// Добавил сюда проверку на "деление на 0" в случае, если ползователь укажет его в качестве знаменателя
Fraction::Fraction(int num, int denom) : isNegative(false)
{
    if (denom == 0)
    {
        throw std::runtime_error("Division by zero is not allowed.");
    }

    isNegative = num * denom < 0 ? true : false;
    num = abs(num);
    denom = abs(denom);

    numerator = static_cast<unsigned int>(num);
    denominator = static_cast<unsigned int>(denom);

    reduce();
}

// Конструктор для преобразования double к Fraction
Fraction::Fraction(double value)
{
    isNegative = value < 0;
    double absValue = std::abs(value);
    
    // Достаточно хорошая точность для значения double
    const double epsilon = 1e-9;

    double diff = std::abs(static_cast<double>(static_cast<unsigned int>(absValue)) - absValue);

    denominator = 1;

    while (diff > epsilon)
    {
        absValue *= 10;
        denominator *= 10;
        diff = std::abs(static_cast<double>(static_cast<unsigned int>(absValue)) - absValue);
    }

    numerator = static_cast<unsigned int>(absValue);

    reduce();
}


// Оператор преобразования дроби к типу double
Fraction::operator double() const
{
    double result = static_cast<double>(numerator) / denominator;
    return isNegative ? -result : result;
}

// Геттеры, тут всё стандартно...
// Для числителя
unsigned int Fraction::getNumerator() const { return numerator; }

// Для знаменателя
unsigned int Fraction::getDenominator() const { return denominator; }

// Знак дроби
bool Fraction::isNegativeFraction() const { return isNegative; }

// Опертаор вывода
std::ostream& operator<<(std::ostream& out, const Fraction& fraction)
{
    if (fraction.isNegative) out << '-';
    out << fraction.numerator << '/' << fraction.denominator;
    return out;
}

// Оператор ввода
std::istream& operator>>(std::istream& in, Fraction& fraction)
{
    int num, denom;
    in >> num;

    if (in.peek() == '/')
    {
        in.get();
        in >> denom;
    } else
    {
        denom = 1;
    }

    fraction = Fraction(num, denom);

    return in;
}

// Тут находится секция арифметических оперторов
// Сложение
Fraction operator+(const Fraction& lhs, const Fraction& rhs)
{
    return static_cast<double>(lhs) + static_cast<double>(rhs);
}

// Вычитание
Fraction operator-(const Fraction& lhs, const Fraction& rhs)
{
    return static_cast<double>(lhs) - static_cast<double>(rhs);
}

// Умножение
Fraction operator*(const Fraction& lhs, const Fraction& rhs)
{
    return static_cast<double>(lhs) * static_cast<double>(rhs);
}

// Деление
Fraction operator/(const Fraction& lhs, const Fraction& rhs)
{
    return static_cast<double>(lhs) / static_cast<double>(rhs);
}

// Операторы сравнения...
bool operator==(const Fraction& lhs, const Fraction& rhs)
{
    return  static_cast<double>(lhs) == static_cast<double>(rhs);
}

bool operator!=(const Fraction& lhs, const Fraction& rhs)
{
    return  static_cast<double>(lhs) != static_cast<double>(rhs);
}

bool operator>(const Fraction& lhs, const Fraction& rhs)
{
    return  static_cast<double>(lhs) > static_cast<double>(rhs);
}

bool operator>=(const Fraction& lhs, const Fraction& rhs)
{
    return  static_cast<double>(lhs) >= static_cast<double>(rhs);
}

bool operator<(const Fraction& lhs, const Fraction& rhs)
{
    return  static_cast<double>(lhs) < static_cast<double>(rhs);
}

bool operator<=(const Fraction& lhs, const Fraction& rhs)
{
    return  static_cast<double>(lhs) <= static_cast<double>(rhs);
}

// Префиксный инкремент
Fraction& Fraction::operator++()
{
    if (isNegative)
    {
        if (numerator >= denominator)
        {
            numerator -= denominator;
        } else
        {
            isNegative = !isNegative;
            numerator = denominator - numerator;
        }
    }
    else
    {
        numerator += denominator;
    }
        
    reduce();
    return *this;
}

// Префиксный декремент
Fraction& Fraction::operator--()
{
    if (!isNegative)
    {
        if (numerator >= denominator)
        {
            numerator -= denominator;
        } else
        {
            isNegative = !isNegative;
            numerator = denominator - numerator;
        }
    }
    else
    {
        numerator = numerator + denominator; 
    }
        
    reduce();
    return *this;
}

// Постфиксный инкремент
Fraction Fraction::operator++(int)
{
    Fraction temp = *this;
    ++(*this);
    return temp;
}

// И даже постфиксный декремент
Fraction Fraction::operator--(int)
{
    Fraction temp = *this;
    --(*this);
    return temp;
}
