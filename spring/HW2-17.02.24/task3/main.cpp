#include <array>
#include <vector>
#include <deque>
#include <list>
#include <forward_list>
#include <random>
#include <iomanip>
#include <string>
#include <utility>

#include "include/stopwatch.hpp"



// Количество элементов в контейнерах
const size_t numberOfElements = 1000000;

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
    // Создаём контейнеры
    std::array<int, numberOfElements> dataArray;
    std::vector<int> dataVector(numberOfElements);
    std::deque<int> dataDeque(numberOfElements);
    std::list<int> dataList(numberOfElements);
    std::forward_list<int> dataForwardList(numberOfElements);

    // Заполняем контейнеры случайными числами
    fillContainer(dataArray);
    fillContainer(dataVector);
    fillContainer(dataDeque);
    dataList.assign(dataVector.begin(), dataVector.end());
    dataForwardList.assign(dataVector.begin(), dataVector.end());

    // Вектор пар "название контейнера" и его "время сортировки"
    // Используется для дальнешего установления самого быстрого контейнера
    std::vector<std::pair<std::string, double>> sortingTimes;

    // Секундомер
    Stopwatch stopwatch;

    // Измеряем и записываем сортировочное время контейнеров
    // std::array
    stopwatch.reset();
    stopwatch.start();
    std::sort(dataArray.begin(), dataArray.end());
    stopwatch.pause();
    sortingTimes.emplace_back("Array", stopwatch.elapsed<std::chrono::milliseconds>());

    // std::vector
    stopwatch.reset();
    stopwatch.start();
    std::sort(dataVector.begin(), dataVector.end());
    stopwatch.pause();
    sortingTimes.emplace_back("Vector", stopwatch.elapsed<std::chrono::milliseconds>());

    // std::deque
    stopwatch.reset();
    stopwatch.start();
    std::sort(dataDeque.begin(), dataDeque.end());
    stopwatch.pause();
    sortingTimes.emplace_back("Deque", stopwatch.elapsed<std::chrono::milliseconds>());

    // std::list
    stopwatch.reset();
    stopwatch.start();
    dataList.sort();
    stopwatch.pause();
    sortingTimes.emplace_back("List", stopwatch.elapsed<std::chrono::milliseconds>());

    // std::forward_list
    stopwatch.reset();
    stopwatch.start();
    dataForwardList.sort();
    stopwatch.pause();
    sortingTimes.emplace_back("Forward List", stopwatch.elapsed<std::chrono::milliseconds>());

    // Сортируем контейнеры по их времени сортировки
    std::sort(sortingTimes.begin(), sortingTimes.end(), [](const auto& a, const auto& b) {
        return a.second < b.second;
    });

    // Выводим результаты измерений в консоль в виде таблицы
    std::cout << "+-------------------+--------------+\n";
    std::cout << "| Name of Container | Sorting time |\n";
    std::cout << "+-------------------+--------------+\n";
    for (const auto& sortingResult : sortingTimes) {
        std::cout << "| " << std::setw(17) << std::left << sortingResult.first << " | "
                  << std::setw(9) << std::right << sortingResult.second << " ms |\n";
    }
    std::cout << "+-------------------+--------------+\n";

    return 0;
}
