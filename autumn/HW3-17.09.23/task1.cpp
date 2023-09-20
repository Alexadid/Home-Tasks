#include <iostream>
#include <vector>

// Объявдение функции производим заранее
unsigned long long fibonacciNumber(int, std::vector<unsigned long long>&);

int main()
{
    int n;

    // Ожидаем получить от пользователя номер числа Фибоначчи, который будем затем вычислять
    std::cout << "Enter the position of the Fibonacci number to calculate: ";
    std::cin >> n;

    // Хотя числа Фибоначчи могут быть рекурсивно определены для отрицательных чисел,
    // в данном примере мы вычисляем классические числа Фибоначчи
    if (n < 0)
    {
        std::cout << "Please enter a non-negative integer.\n";
    } else
    {
        // Создаём вектор для хранения вычисленных чисел Фибоначчи
        std::vector<unsigned long long> memory(n + 1, 0);

        // Вычисляем и выводим n-ое число Фибоначчи
        unsigned long long result = fibonacciNumber(n, memory);
        std::cout << "Fibonacci number at position " << n << " is: " << result << std::endl;
    }

    return 0;
}

// Функция для вычилсения числе Фибоначчи, адаптирована для вычисления более крупных чисел Фибоначчи
// Вектор memory служит для зранения уже вычисленных чисел, что предотвращает перевчсиление одного
// и того же значения несколько разв ходе рекурсии
// Стоит отметить, что за счёт этой адаптации вычисляет маленькие числа несколько медленнее,
// ввиду обращений к вектору
unsigned long long fibonacciNumber(int n, std::vector<unsigned long long>& memory)
{
    // Базовый случай для чисел Фибоначчи
    if (n == 0)
    {
        return 0;
    } else if (n == 1)
    {
        return 1;
    }

    // Проверяем вычислено ли и сохранено ли данное число Фибоначчи в memory
    if (memory[n] != 0)
    {
        return memory[n];
    }

    // Если не вычислено, рекрусивно вычиляем его, суммирую два предыдущих числа...
    memory[n] = fibonacciNumber(n - 1, memory) + fibonacciNumber(n - 2, memory);
    return memory[n];
}
