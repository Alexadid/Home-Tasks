#include <iostream>
#include <stdexcept>

// Функция деления для демонстрации ошибки деления на ноль
int divide(int numerator, int denominator)
{
    if (denominator == 0)
    {
        throw std::invalid_argument("Division by zero is not allowed.");
    }

    return numerator / denominator;
}

// Функция для демонстрации возникновения ошибки обращению к индексу вне диапазона
void accessOutOfRangeElement()
{
    int numbers[] = {1, 2, 3};
    // Массив длины 3, а пытаемся обратиться к 5-ому элементу
    size_t index = 5;
    if (index < 0 || index >= std::size(numbers))
    {
        throw std::out_of_range("Array index is out of range.");
    }
    int value = numbers[index];
}

// Фукнция для демонстрации ошибки времени выполнения (nullptr в данном случае)
void triggerRuntimeError()
{
    int* ptr = nullptr;
    if (ptr)
    {
        throw std::runtime_error("Pointer is null.");
    }
}

int main()
{
    try
    {
        // Выбрасывает std::invalid_argument, т.к. пытаемся делить на ноль
        divide(10, 0);
    } catch (const std::invalid_argument& e)
    {
        std::cerr << "std::invalid_argument Exception: " << e.what() << std::endl;
    }

    try
    {
        // Выбрасывает std::out_of_range
        accessOutOfRangeElement();
    } catch (const std::out_of_range& e)
    {
        std::cerr << "std::out_of_range Exception: " << e.what() << std::endl;
    }

    try
    {
        // Выбрасываетstd::runtime_error
        triggerRuntimeError();
    } catch (const std::runtime_error& e)
    {
        std::cerr << "std::runtime_error Exception: " << e.what() << std::endl;
    }

    return 0;
}
