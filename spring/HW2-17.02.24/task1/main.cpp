#include "include/stopwatch.hpp"

// Решил взять что-то помедленнее - бабл-сорт (передаю привет Википедии)
// Смешно, что за счёт его медлительности я некторое время считал, что таймер не работает,
// т.к. он показывал 0 для std::sort
void bubbleSort(std::vector<int>& vect)
{
    bool swapped = true;
    int j = 0;
    while (swapped)
    {
        swapped = false;
        j++;
        for (size_t i = 0; i < vect.size() - j; i++)
        {
            if (vect[i] > vect[i + 1])
            {
                std::swap(vect[i], vect[i + 1]);
                swapped = true;
            }
        }
    }
}

int main()
{
    // Количество элементов в векторе, который будем сортировать
    int numberOfElementsInVector = 25000;
    // Вектор для сортировки
    std::vector<int> data(numberOfElementsInVector);
    // Непосредственно генерация при помощи случайных чисел
    std::generate(data.begin(), data.end(), std::rand);

    // Измеряем std::sort
    Stopwatch stopwatch; // Создаём секундомер, он уже запущен
    std::sort(data.begin(), data.end());
    // Выводим время работы секундомера в миллисекундах
    std::cout << "std::sort took: " << stopwatch.elapsed<std::chrono::milliseconds>() << " milliseconds.\n";

    // Вновь генерируем данные
    std::generate(data.begin(), data.end(), std::rand);
    // Сбрасываем время таймера, он на паузе
    stopwatch.reset();
    // Соответственно, включаем таймер
    stopwatch.start();

    // Измеряем бабл-сорт
    bubbleSort(data);
    // И вновь выводим время работы таймера
    std::cout << "bubbleSort took: " << stopwatch.elapsed<std::chrono::milliseconds>() << " milliseconds.\n";

    return 0;
}
