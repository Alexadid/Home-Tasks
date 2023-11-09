#include "include/Fraction.hpp"
#include <sstream>

int main()
{
    const int numerator1 = 3;
    const int numerator2 = 5;
    const int denominator1 = 1;
    const int denominator2 = 2;
    const int zeroNum = 0;

    // Проверка на деление на ноль в конструкторе
    try
    {
        Fraction fraction(numerator1, zeroNum);
    }
    catch (const std::runtime_error& error)
    {
        std::cerr << "Error: " << error.what() << std::endl;
    }

    // Проверка на деление на ноль при делении дробей
    try
    {
        Fraction fraction1(numerator1, denominator1);
        Fraction fraction2(zeroNum, denominator1);
        Fraction result = fraction1 / fraction2;
    }
    catch (const std::runtime_error& error)
    {
        std::cerr << "Error: " << error.what() << std::endl;
    }

    const unsigned int nearOverflowNominator = std::numeric_limits<int>::max() - 1;

    // Проверка на переполнение при умножении
    try
    {
        Fraction fraction3(nearOverflowNominator, denominator2);
        Fraction result = fraction3 * fraction3;
    }
    catch (const std::runtime_error& error)
    {
        std::cerr << "Error: " << error.what() << std::endl;
    }

    const std::string incorrectNumeratorFraction = "abc/2";

    // Проверка на некорректный ввод через оператор '<<' числителя
    try
    {
        Fraction fraction4;
        std::istringstream invalidInput(incorrectNumeratorFraction);
        invalidInput >> fraction4;
    }
    catch (const std::runtime_error& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    const std::string incorrectDenominatorFraction = "2/abc";

    // Проверка на некорректный ввод через оператор '<<' знаменателя
    try
    {
        Fraction fraction5;
        std::istringstream divisionByZeroInput(incorrectDenominatorFraction);
        divisionByZeroInput >> fraction5;
    }
    catch (const std::runtime_error& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    const std::string zeroDenominatorFraction = "2/0";

    // Проверка на ввод 0 вместо знаменателя
    try
    {
        Fraction fraction6;
        std::istringstream divisionByZeroInput(zeroDenominatorFraction);
        divisionByZeroInput >> fraction6;
    }
    catch (const std::runtime_error& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
