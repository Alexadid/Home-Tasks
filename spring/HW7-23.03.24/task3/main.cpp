#include <algorithm>
#include <future>
#include <iterator>
#include <vector>
#include <functional>
#include <thread>
#include <iostream>



// Функция для оценки начального значения min_per_thread
// Изначально я задумывался о том, чтобы просто записать константу и успокоиться на этом...
std::ptrdiff_t estimate_min_per_thread(std::ptrdiff_t total_elements)
{
    auto num_cores = std::thread::hardware_concurrency();
    // Запасной вариант на случай, если hardware_concurrency не определен должным образом
    if (num_cores == 0) num_cores = 1;
    // Начинаем с произвольного выбора минимального количества задач для каждого ядра
    std::ptrdiff_t min_per_core = 1000;
    std::ptrdiff_t calculated_min = total_elements / (num_cores * min_per_core);
    // Убеждаемся, что в каждом потоке есть хотя бы один элемент
    return calculated_min > 0 ? calculated_min : 1;
}

// Функция выполняющая фукнции параллельной версии for_each
template<typename Iterator, typename Func>
void parallel_for_each(Iterator first, Iterator last, Func func)
{
    // Количество элементов в диапазоне
    std::ptrdiff_t length = std::distance(first, last);

    // Если он пуст, то сразу возвращаем
    if (length == 0) return;

    // Определяем минимальное количество элементов в потоке
    std::ptrdiff_t const min_per_thread = estimate_min_per_thread(length);

    // Если диапазон меньше или равен минимуму для каждого потока, обрабатываем его последовательно,
    // иначе во всём этом нет смысла...
    if (length <= min_per_thread)
    {
        std::for_each(first, last, func);
        return;
    }

    // Находим середину диапазона, чтобы разделить работу примерно пополам
    Iterator middle = first;
    std::advance(middle, length / 2);

    // Асинхронно обрабатываем первую половину диапазона
    std::future<void> first_half_result =
        std::async(std::launch::async, &parallel_for_each<Iterator, Func>, first, middle, func);

    // Рекурсивно обрабатываем вторую половину диапазона в текущем потоке
    parallel_for_each(middle, last, func);

    // Дожидаемся завершения асинхронной операции первой половины, прежде чем возвращать
    first_half_result.get();
}


int main()
{
    // Демонстрационный код...
    std::vector<int> data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    parallel_for_each(data.begin(), data.end(), [](int& x)
    {
        x *= 2;
    });

    for (int num : data)
    {
        std::cout << num << ' ';
    }
    std::cout << std::endl;

    return 0;
}
