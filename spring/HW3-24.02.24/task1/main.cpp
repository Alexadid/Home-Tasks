#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <algorithm>
#include <random>
#include "include/stopwatch.hpp"



// Шаблонная функция для заполнения произвольного контейнера случайными
template<typename Container>
void fillContainer(Container& container)
{
    // Равномерно распределённый генератор целочисленных случайных чисел
    // (за счёт равномерного распределения все контейнеры оказываются в одинаковых условиях)
    std::random_device randomDevice;
    // Псевдослучайный генератор 32-разрядных чисел Mersenne Twister
    std::mt19937 generator(randomDevice());
    // Распределение, которое генерирует целые числа в пределах заданного диапазона
    std::uniform_int_distribution<> distribution(1, 1000000);
    // Заполняем контейнер
    for (auto& element : container)
    {
        element = distribution(generator);
    }
}

int main()
{
    // Данные будем записывать в csv файл, открываем его
    std::ofstream outputFile("timing_results.csv");

    // Пометим, что есть что
    outputFile << "N,Set Insertion Time (μs),Vector Insert + Sort Time (μs)\n";

    // Слишком много значений не стал брать, чтобы расчёт не шёл слишком долго
    for (int N = 5000; N <= 200000; N += 5000)
    {
        // Генерируем последовательность чисел, которую будем исопльзовать для заполнения контейнеров
        std::vector<int> numbers(N);
        fillContainer(numbers);

        // Измеряем время вставки в std::set, используем для этого таймер в микросекундах
        Stopwatch stopwatch;
        std::set<int> numbersSet;
        for (int num : numbers)
        {
            numbersSet.insert(num);
        }
        auto setInsertTime = stopwatch.elapsed<std::chrono::microseconds>();
        stopwatch.reset();



        // Измеряем время сортировки для std::vector
        std::vector<int> numbersVector = numbers;
        stopwatch.start();
        std::sort(numbersVector.begin(), numbersVector.end());
        auto vectorSortTime = stopwatch.elapsed<std::chrono::microseconds>();

        // Записываем построчно данные...
        outputFile << N << "," << setInsertTime << "," << vectorSortTime << "\n";
    }

    // Закрываем файл
    outputFile.close();
    // Информируем ползователя об окончании записи
    std::cout << "Data has been written to timing_results.csv\n";

    return 0;
}
