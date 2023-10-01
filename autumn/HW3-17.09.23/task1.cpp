#include <iostream>
#include <vector>

std::vector<std::vector<unsigned long long>> matrixMultiply(
    const std::vector<std::vector<unsigned long long>>&,
    const std::vector<std::vector<unsigned long long>>&);

std::vector<std::vector<unsigned long long>> matrixPower(
    const std::vector<std::vector<unsigned long long>>&,
    unsigned long long);

unsigned long long calculateNthFibonacci(int);

// Провёл оптимизацию вычисления чисел Фибоначчи
// Вместо вычисления за O(2^N) - рекурсия
// Вычисляет за O(log N)
// Подробности в комментариях к самим функциям...

int main()
{
    int nthPosition;

    // Ожидаем получить от пользователя номер числа Фибоначчи, который будем затем вычислять
    std::cout << "Enter the position of the Fibonacci number to calculate: ";
    std::cin >> nthPosition;

    // Хотя числа Фибоначчи могут быть рекурсивно определены для отрицательных чисел,
    // в данном примере мы вычисляем классические числа Фибоначчи
    if (nthPosition < 0)
    {
        std::cout << "Please enter a non-negative integer.\n";
    } else if (nthPosition > 92)
    {
        // Так как при реализации матричного умножения прибегнул к использованию вычислений по модулю,
        // то полученное число Фибоначчи должно состоять из не более 20 цифр
        std::cout << "Sorry, but this program cannot compute such a large Fibonacci numer.\n";
    } else
    {
        // Вычисляем и выводим n-ое число Фибоначчи
        unsigned long long nthFibonacci = calculateNthFibonacci(nthPosition);
        std::cout << "Fibonacci number at position " << nthPosition << " is: " << nthFibonacci << std::endl;
    }

    return 0;
}

// Функция для перемножения матриц 2x2
std::vector<std::vector<unsigned long long>> matrixMultiply(
    const std::vector<std::vector<unsigned long long>>& matrixA,
    const std::vector<std::vector<unsigned long long>>& matrixB)
{
    unsigned long int mod = 10089886811898868001; // наименьшее 21-значное простое число
    int size = matrixA.size();
    std::vector<std::vector<unsigned long long>> result(size, std::vector<unsigned long long>(size, 0));
    
    // Выполняем матричное умножение
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            for (int k = 0; k < size; ++k)
            {
                // Выполняем операции по модулю, чтобы избежать переполнения
                result[i][j] = (result[i][j] + (matrixA[i][k] * matrixB[k][j]) % mod) % mod;
            }
        }
    }
    return result;
}

// Функция для возведения матрицы в степень
std::vector<std::vector<unsigned long long>> matrixPower(
    const std::vector<std::vector<unsigned long long>>& matrix,
    unsigned long long exponent)
{
    int size = matrix.size();
    std::vector<std::vector<unsigned long long>> result(size, std::vector<unsigned long long>(size, 0));
    
    // Инициализируем результирующую матрицу как единичную матрицу
    for (int i = 0; i < size; ++i) {
        result[i][i] = 1;
    }
    
    std::vector<std::vector<unsigned long long>> base = matrix;
    
    // Выполняем возведение матрицы в степень с использованием
    // двоичного возведения в степень
    while (exponent > 0)
    {
        if (exponent % 2 == 1)
        {
            result = matrixMultiply(result, base);
        }
        base = matrixMultiply(base, base);
        exponent /= 2;
    }
    
    return result;
}

// Function to calculate the nth Fibonacci number
// Функция для вычилсения n-ого числа Фибоначчи (не более чем 92-ого)
// с использованием возведения матриц в степень
// вычисляет заданное число за O(log N)
unsigned long long calculateNthFibonacci(int n)
{
    std::vector<std::vector<unsigned long long>> baseMatrix = {{1, 1}, {1, 0}};
    
    // Compute the (n-1)th power of the base matrix
    // Вычисляем n-1 степень базовой матрицы, т.к. согласно тождеству
    
    // ┌         ┐ n   ┌                 ┐
    // │ 1     1 │     │ F_(n+1)     F_n │
    // │         │  =  │                 │
    // │ 1     0 │     │ F_n     F_(n-1) │
    // └         ┘     └                 ┘

    std::vector<std::vector<unsigned long long>> resultMatrix = matrixPower(baseMatrix, n - 1);
    
    return resultMatrix[0][0];
}