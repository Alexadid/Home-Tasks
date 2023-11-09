#include "../include/Fraction.hpp"
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
Fraction::Fraction(int num, int denom) : isNegative(false)
{
    // Добавил проверку на потенциальное деление на ноль
    if (denom == 0)
    {
        throw std::runtime_error("Division by zero is not allowed.");
    }

    isNegative = num * denom < 0 ? true : false;
    num = num > 0 ? num : -num;
    denom = denom > 0 ? denom : -denom;

    numerator = static_cast<unsigned int>(num);
    denominator = static_cast<unsigned int>(denom);

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

    if (!in)
    {
        // Обработка сбоя ввода
        throw std::runtime_error("Invalid input for numerator");
    }

    if (in.peek() == '/')
    {
        in.get();
        in >> denom;

        if (!in || denom == 0)
        {
            // Опять обработка сбоя ввода или ввода знаменателя, равного 0
            throw std::runtime_error("Invalid input for denominator or division by zero");
        }
    }
    else
    {
        denom = 1;
    }

    fraction = Fraction(num, denom);

    return in;
}


// Тут находится секция арифметических оперторов
// Сложение
Fraction Fraction::operator+(const Fraction& other) const
{
    Fraction result;
    result.numerator = numerator * other.denominator + other.numerator * denominator;
    result.denominator = denominator * other.denominator;
    result.isNegative = isNegative || other.isNegative;
    result.reduce();
    return result;
}

// Вычитание
Fraction Fraction::operator-(const Fraction& other) const
{
    Fraction result;
    result.numerator = numerator * other.denominator - other.numerator * denominator;
    result.denominator = denominator * other.denominator;
    result.isNegative = isNegative || other.isNegative;
    result.reduce();
    return result;
}

// Умножение
// Умножение
Fraction Fraction::operator*(const Fraction& other) const
{
    Fraction result;
    // Проверка на потенциальное переполнение
    if (other.numerator != 0 && (numerator > std::numeric_limits<unsigned int>::max() / other.numerator ||
        denominator > std::numeric_limits<unsigned int>::max() / other.denominator))
    {
        throw std::overflow_error("Multiplication would result in overflow");
    }

    result.numerator = numerator * other.numerator;
    result.denominator = denominator * other.denominator;
    result.isNegative = isNegative || other.isNegative;
    result.reduce();
    return result;
}


// Деление
// Здесь также добавлена обработка ошибки деления на 0
Fraction Fraction::operator/(const Fraction& other) const
{
    // Добавил проверку на потенциальное деление на ноль
    if (other.numerator == 0)
    {
        throw std::runtime_error("Division by zero is not allowed.");
    }

    Fraction result;
    result.numerator = numerator * other.denominator;
    result.denominator = denominator * other.numerator;
    result.isNegative = isNegative || other.isNegative;
        
    result.reduce();
    return result;
}


// Операторы сравнения...
bool Fraction::operator==(const Fraction& other) const
{
    return numerator == other.numerator && denominator == other.denominator && isNegative == other.isNegative;
}

bool Fraction::operator!=(const Fraction& other) const { return !(*this == other); }

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
