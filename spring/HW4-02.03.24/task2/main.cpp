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
    const int upperBoundOfRange = 10000;

    for (auto& iterations : iterationSteps)
    {
        // Измерения проводим для rand (тут, правда, для него ничего не делается), Вихря Мерсена и random_device
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<int> dist(lowerBoundOfRange, upperBoundOfRange);
        Stopwatch sw;

        // Открываем файлы и именуем их соттветственно
        std::string randFileName = "rand_numbers_" + std::to_string(iterations) + ".csv";
        std::string mtFileName = "mt19937_numbers_" + std::to_string(iterations) + ".csv";
        std::string rdFileName = "random_device_numbers_" + std::to_string(iterations) + ".csv";

        std::ofstream randFile(randFileName), mtFile(mtFileName), rdFile(rdFileName);

        // Генерируемые числа и измеряем время для rand
        sw.start();
        for(size_t i = 0; i < iterations; ++i)
        {
            int number = std::rand() % (upperBoundOfRange + 1);
            randFile << number << std::endl;
        }
        sw.pause();
        timeFile << "rand," << iterations << "," << sw.elapsed<std::chrono::milliseconds>() << std::endl;
        sw.reset();
        randFile.close();

        // Генерируемые числа и измеряем время для Вихря Мерсена
        sw.start();
        for(size_t i = 0; i < iterations; ++i)
        {
            int number = dist(mt);
            mtFile << number << std::endl;
        }
        sw.pause();
        timeFile << "mt19937," << iterations << "," << sw.elapsed<std::chrono::milliseconds>() << std::endl;
        sw.reset();
        mtFile.close();

        // Генерируемые числа и измеряем время для random_device
        sw.start();
        for(size_t i = 0; i < iterations; ++i)
        {
            int number = dist(rd);
            rdFile << number << std::endl;
        }
        sw.pause();
        timeFile << "random_device," << iterations << "," << sw.elapsed<std::chrono::milliseconds>() << std::endl;
        rdFile.close();
    }

    // Закрываем файл с таблицей
    timeFile.close();

    // Информаируем пользователя об окончании измерений
    std::cout << "Random numbers and timing data have been written to files." << std::endl;

    return 0;
}
