#include <iostream>
#include <vector>
#include <functional>

// Функция для вычисления на основе введънных данных и соответствующего лямбда выражения
// Решил не выносить объявление функции, т.к. она всего одна и занимает буквально 1 строку
double calculate(double x, double y, std::function<double(double, double)> func) { return func(x, y); }

int main()
{
    // Создаём вектор для хранения лямбда-выражений
    std::vector<std::function<double(double, double)>> lambdaExpressions;

    // Лямбда-выржание для сложения двух чисел
    auto addLambda = [](double x, double y) { return x + y; };
    lambdaExpressions.push_back(addLambda);

    // Лямбда-выржание для вычитания двух чисел
    auto subtractLambda = [](double x, double y) { return x - y; };
    lambdaExpressions.push_back(subtractLambda);

    // Лямбда-выржание для умножения двух чисел
    auto multiplyLambda = [](double x, double y) { return x * y; };
    lambdaExpressions.push_back(multiplyLambda);

    // Лямбда-выржание для деления двух чисел
    // Встроил проверку на деление на ноль
    // В случае ошибки вернёт 0.0 как значение по умолчанию
    auto divideLambda = [](double x, double y)
    {
        if (y != 0)
        {
            return x / y;
        } else
        {
            std::cerr << "Error: Division by zero!" << std::endl;
            return 0.0;
        }
    };
    lambdaExpressions.push_back(divideLambda);

    // Принимаем от пользователя два числа для проведения арифметичсеких операций
    double num1, num2;
    std::cout << "Enter the first number: ";
    std::cin >> num1;
    std::cout << "Enter the second number: ";
    std::cin >> num2;

    // Проходим по вектору лямбда-выражений и выводим результат вычислений
    for (const auto& func : lambdaExpressions)
    {
        double result = calculate(num1, num2, func);
        std::cout << "Result: " << result << std::endl;
    }

    return 0;
}
