#include "fraction.hpp"

int main()
{
    // Никаких магических чисел в main!
    // Знак дроби определяем по числителю и знаменателю
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
