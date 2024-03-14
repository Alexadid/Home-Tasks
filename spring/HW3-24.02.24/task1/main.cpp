#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <algorithm>
#include <random>
#include "include/stopwatch.hpp"



// Шаблонная функция для заполнения произвольного контейнера случайными
template<typename Container>
void fillContainer(Container& container, int amountOfNumbers)
{
    // Равномерно распределённый генератор целочисленных случайных чисел
    // (за счёт равномерного распределения все контейнеры оказываются в одинаковых условиях)
    std::random_device randomDevice;
    // Псевдослучайный генератор 32-разрядных чисел Mersenne Twister
    std::mt19937 generator(randomDevice());
    // Распределение, которое генерирует целые числа в пределах заданного диапазона
    std::uniform_int_distribution<> distribution(1, amountOfNumbers * 10);
    // Заполняем контейнер
    std::set<int> uniqueInts;
    for (auto& element : container)
    {
        int randomInt;
        do
        {
            randomInt = distribution(generator);
        }
        while (!uniqueInts.insert(randomInt).second);

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
    for (int N = 25000; N <= 2500000; N += 25000)
    {
        // Генерируем последовательность чисел, которую будем исопльзовать для заполнения контейнеров
        std::vector<int> numbers(N);
        fillContainer(numbers, N);

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
        std::vector<int> numbersVector;
        stopwatch.start();
        for (int num : numbers)
        {
            numbersVector.push_back(num);
            //std::cout << num << std::endl;
        }
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