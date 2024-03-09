#include <fstream>
#include <random>
#include <chrono>
#include <iostream>
#include <vector>
#include "include/stopwatch.hpp"

int main()
{
    // Аналогично предыдщему заданию изучим временную зависимость от количества сгенерированных чисел
    std::vector<size_t> iterationSteps = {10000, 50000, 100000, 500000, 1000000, 5000000, 10000000};
    std::ofstream timeFile("timing_data.csv");

    // Заголовки для файла, измеряющего время для каждого из способов генерации (решил измерять сразу для всех трёх)
    timeFile << "Method,Iterations,Time (ms)" << std::endl;

    const int lowerBoundOfRange = 0;
    const int upperBoundOfRange = 250;

    for (auto& iterations : iterationSteps)
    {
        // Измерения проводим для rand (тут, правда, для него ничего не делается), Вихря Мерсена и random_device
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<int> dist(lowerBoundOfRange, upperBoundOfRange);
        Stopwatch stopWatch;

        // Открываем файлы и именуем их соттветственно
        std::string randFileName = "rand_numbers_" + std::to_string(iterations) + ".csv";
        std::string mtFileName = "mt19937_numbers_" + std::to_string(iterations) + ".csv";
        std::string rdFileName = "random_device_numbers_" + std::to_string(iterations) + ".csv";

        std::ofstream randFile(randFileName), mtFile(mtFileName), rdFile(rdFileName);

        // Генерируемые числа и измеряем время для rand
        stopWatch.start();
        for(size_t i = 0; i < iterations; ++i)
        {
            stopWatch.start();
            int number = std::rand() % (upperBoundOfRange + 1);
            stopWatch.pause();
            randFile << number << std::endl;
        }
        stopWatch.pause();
        timeFile << "rand," << iterations << "," << stopWatch.elapsed<std::chrono::milliseconds>() << std::endl;
        stopWatch.reset();
        randFile.close();

        // Генерируемые числа и измеряем время для Вихря Мерсена
        stopWatch.start();
        for(size_t i = 0; i < iterations; ++i)
        {
            stopWatch.start();
            int number = dist(mt);
            stopWatch.pause();
            mtFile << number << std::endl;
        }
        stopWatch.pause();
        timeFile << "mt19937," << iterations << "," << stopWatch.elapsed<std::chrono::milliseconds>() << std::endl;
        stopWatch.reset();
        mtFile.close();

        // Генерируемые числа и измеряем время для random_device
        stopWatch.start();
        for(size_t i = 0; i < iterations; ++i)
        {
            stopWatch.start();
            int number = dist(rd);
            stopWatch.pause();
            rdFile << number << std::endl;
        }
        stopWatch.pause();
        timeFile << "random_device," << iterations << "," << stopWatch.elapsed<std::chrono::milliseconds>() << std::endl;
        rdFile.close();
    }

    // Закрываем файл с таблицей
    timeFile.close();

    // Информаируем пользователя об окончании измерений
    std::cout << "Random numbers and timing data have been written to files." << std::endl;

    return 0;
}
