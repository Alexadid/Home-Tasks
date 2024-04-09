#include <algorithm>
#include <iostream>
#include <numeric>
#include <thread>
#include <vector>
#include <fstream>
#include <string>
#include <functional>
#include "include/stopwatch.hpp"



// Определение функтора, который накапливает значения в диапазоне [first, last) в result
// Идентичен примеру коду из семинара
template <typename Iterator, typename T>
struct accumulate_block
{
    void operator()(Iterator first, Iterator last, T& result)
    {
        result = std::accumulate(first, last, result);
    }
};

// Функция для выполнения параллельного накопления с использованием нескольких потоков
template <typename Iterator, typename T>
T parallel_accumulate(Iterator first, Iterator last, T init, std::size_t num_threads)
{
    // Общее количество элементов
    const std::size_t length = std::distance(first, last);

    // Если по какой-то причине нет элементов или потоков, возвращаем начальном значение
    if (!length || num_threads == 0)
    {
        return init;
    }

    // Определяем количество элементов, обрабатываемых каждым потоком
    const std::size_t min_per_thread = 25;
    const std::size_t max_threads = (length + min_per_thread - 1) / min_per_thread;

    // Отрегулируйте возможное количество потоков, чтобы избежать простоев
    //num_threads = std::min(num_threads, max_threads);

    const std::size_t block_size = length / num_threads; 

    // Вычисляем размер блока для каждого потока
    std::vector<T> results(num_threads);
    // Вектор потоков
    // На один меньше, потому что главный поток также работает
    std::vector<std::thread> threads(num_threads - 1);

    // Старт первого блока
    Iterator block_start = first;

    // Запускаем потоки для параллельного вычисления
    for (std::size_t i = 0; i < (num_threads - 1); ++i)
    {
        Iterator block_end = block_start;
        // Перемещаем block_end итератор
        std::advance(block_end, block_size);

        // Создаём и стартуем новый поток
        threads[i] = std::thread(accumulate_block<Iterator, T>(), block_start, block_end, std::ref(results[i]));

        // Переходим к следующему блоку
        block_start = block_end;
    }

    // Накапливаем последний блок в основном потоке
    accumulate_block<Iterator, T>()(block_start, last, results[num_threads - 1]);

    // Дожидаемся завершения работы всех потоков
    std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));

    // Собираем результаты из всех потоков
    return std::accumulate(results.begin(), results.end(), init);
}

int main()
{
    // 
    const size_t vectorSize = 1000000000;
    std::vector<int> vec(vectorSize);
    std::iota(vec.begin(), vec.end(), 1);

    //std::cout << v.at(10) << std::endl;

    // Открываем файл и записываем загловок таблицы
    std::ofstream dataFile("thread_timing_data.csv");
    dataFile << "Threads,Time(ns)\n";

    // Измеряем и записываем данные о времени в зависимости от количества задействованных потоков
    for (std::size_t threads = 1; threads <= std::thread::hardware_concurrency(); ++threads)
    {
        Stopwatch stopwatch;
        stopwatch.start();

        auto result = parallel_accumulate(vec.begin(), vec.end(), 0, threads);

        stopwatch.pause();

        auto time = stopwatch.elapsed<std::chrono::nanoseconds>();
        dataFile << threads << "," << time << "\n";
    }

    // Закрываем файл
    dataFile.close();

    // Информаируем пользователя об окончании измерений
    std::cout << "Timing data has been written to a file." << std::endl;

    return 0;
}
