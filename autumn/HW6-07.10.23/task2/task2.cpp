#include <iostream>
#include <numeric>

class Fraction
{
private:
    unsigned int numerator;
    unsigned int denominator;
    bool isNegative;

    // Функция-член для упрощения дроби
    // Писать собственный gcd не решился - и так много времени потратил
    // Функция приватна, т.к. её вызов предполагается только изнутри
    void reduce()
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

public:
    // Конструктор по умолчанию
    Fraction() : numerator(0), denominator(1), isNegative(false) {}

    // Параметризованный конструктор
    Fraction(int num, int denom) : isNegative(false)
    {
        if (num < 0)
        {
            isNegative = true;
            num = -num;
        }

        numerator = static_cast<unsigned int>(num);
        denominator = static_cast<unsigned int>(denom);
        reduce();
    }

    // Оператор преобразования дроби к типу double
    explicit operator double() const
    {
        double result = static_cast<double>(numerator) / denominator;
        return isNegative ? -result : result;
    }

    // Геттеры, тут всё стандартно...
    // Для числителя
    unsigned int getNumerator() const { return numerator; }

    // Для знаменателя
    unsigned int getDenominator() const { return denominator; }

    // Отрицательна ли дробь
    bool isNegativeFraction() const { return isNegative; }

    // Опертаор вывода
    friend std::ostream& operator<<(std::ostream& out, const Fraction& fraction)
    {
        if (fraction.isNegative) out << '-';
        out << fraction.numerator << '/' << fraction.denominator;
        return out;
    }

    // Оператор ввода
    friend std::istream& operator>>(std::istream& in, Fraction& fraction)
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
    Fraction operator+(const Fraction& other) const
    {
        Fraction result;
        result.numerator = numerator * other.denominator + other.numerator * denominator;
        result.denominator = denominator * other.denominator;
        result.isNegative = isNegative || other.isNegative;
        result.reduce();
        return result;
    }

    // Вычитание
    Fraction operator-(const Fraction& other) const
    {
        Fraction result;
        result.numerator = numerator * other.denominator - other.numerator * denominator;
        result.denominator = denominator * other.denominator;
        result.isNegative = isNegative || other.isNegative;
        result.reduce();
        return result;
    }

    // Умножение
    Fraction operator*(const Fraction& other) const
    {
        Fraction result;
        result.numerator = numerator * other.numerator;
        result.denominator = denominator * other.denominator;
        result.isNegative = isNegative || other.isNegative;
        result.reduce();
        return result;
    }

    // Деление
    // Здесь также добавлена обработка ошибки деления на ноль
    Fraction operator/(const Fraction& other) const
    {
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
    bool operator==(const Fraction& other) const
    {
        return numerator == other.numerator && denominator == other.denominator && isNegative == other.isNegative;
    }

    bool operator!=(const Fraction& other) const
    {
        return !(*this == other);
    }

    // Префиксный инкремент
    Fraction& operator++()
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
    Fraction& operator--()
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
    Fraction operator++(int)
    {
        Fraction temp = *this;
        ++(*this);
        return temp;
    }

    // И даже постфиксный декремент
    Fraction operator--(int)
    {
        Fraction temp = *this;
        --(*this);
        return temp;
    }
};

int main()
{
    // Никаких магических чисел в main!
    int numenatorOfFirstFraction = 3;
    int denumenatorOfFirstFraction = 4;
    int numenatorOfSecondFraction = -2;
    int denumenatorOfSecondFraction = 5;

    // Создаём 2 дроби:
    //
    //                          3            2
    //                         ---    и   - ---
    //                          4            5
    //

    Fraction firstFraction(numenatorOfFirstFraction, denumenatorOfFirstFraction);
    Fraction secondFraction(numenatorOfSecondFraction, denumenatorOfSecondFraction);

    // Для начала выводим дроби в коноль
    std::cout << "a = " << firstFraction << std::endl;
    std::cout << "b = " << secondFraction << std::endl;

    // Теперь складываем 2 дроби, а резульат записываем и затем выводим.
    // Получили:
    //
    //                         7
    //                        ----
    //                         20
    //

    Fraction resultC = firstFraction + secondFraction;
    std::cout << "a + b = " << resultC << std::endl;

    // Теперь вычитаем и повторяем тоже самое.
    // Получили:
    //
    //                         23
    //                        ----
    //                         20
    //

    Fraction resultD = firstFraction - secondFraction;
    std::cout << "a - b = " << resultD << std::endl;

    // Умножаем.
    // Получили:
    //
    //                         3
    //                      - ----
    //                         10
    //

    Fraction resultE = firstFraction * secondFraction;
    std::cout << "a * b = " << resultE << std::endl;

    // Делим...
    // Получили:
    //
    //                         15
    //                      - ----
    //                         8
    //
    
    Fraction resultF = firstFraction / secondFraction;
    std::cout << "a / b = " << resultF << std::endl;

    // Тут я, пожалуй перестану записывать резльтаты каждой арифместичекой операции

    // Теперь покажем работоспособность постфиксных и перфиксных инкрементов и декрементов
    // Префиксный инкремент
    Fraction resultG = ++firstFraction;
    std::cout << "++a = " << resultG << std::endl;

    // Постфиксный инкремент
    Fraction resultH = firstFraction++;
    std::cout << "a++ = " << resultH << std::endl;
    std::cout << "a after a++ = " << firstFraction << std::endl;

    // Префиксный декремент
    Fraction resultI = --secondFraction;
    std::cout << "--b = " << resultI << std::endl;

    // Постфиксный декремент
    Fraction resultJ = secondFraction--;
    std::cout << "b-- = " << resultJ << std::endl;
    std::cout << "b after b-- = " << secondFraction << std::endl;

    // Здесь попробуем сравнить дроби
    // Включил boolalpha, чтобы было понятнее, какой резульат
    std::cout << std::boolalpha << "a == b: " << (firstFraction == secondFraction) << std::endl;
    std::cout << std::boolalpha << "a != b: " << (firstFraction != secondFraction) << std::endl;

    // Перевод в double
    std::cout << "a as a double is " << double(firstFraction);

    return 0;
}
