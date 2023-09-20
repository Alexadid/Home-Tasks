#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

// Объявление функция
void printArray(const std::vector<int>&);
std::vector<int> generateRandomArray(int, int, int);

// Лямбда-выражения для сортировка по возрастнаию и убыванию соответственно
auto ascendingSort = [](int a, int b)
{
    return a < b;
};

auto descendingSort = [](int a, int b)
{
    return a > b;
};

int main()
{
    const int size = 10;
    const int minRange = 0;
    const int maxRange = 100;

    // Проводим генерацию массива
    std::vector<int> numbers = generateRandomArray(size, minRange, maxRange);  

    std::cout << "Unsorted array: ";  
    printArray(numbers);

    // Сортируем в порядке возрастания, используя std::sort при помощи лямбда-выражения ascendingSort
    std::sort(numbers.begin(), numbers.end(), ascendingSort);

    std::cout << "Sorted in ascending order: ";
    printArray(numbers);

    // Сортируем в порядке убывания, используя std::sort при помощи лямбда-выражения descendingSort
    std::sort(numbers.begin(), numbers.end(), descendingSort);

    std::cout << "Sorted in descending order: ";
    printArray(numbers);

    return 0;
}

// Функция для печати массива в консоль
void printArray(const std::vector<int>& arr)
{
    // Лямбда-выржаение для печати вектора
    std::for_each(arr.begin(), arr.end(), [](int i)
    {
        std::cout << i << " ";
    });
    std::cout << std::endl;
}

// Функция для генерации слуяайного массива заданного размера с заданным диапазоном
std::vector<int> generateRandomArray(int size, int minRange, int maxRange)
{
    // Задаём генератору случайных чисел текущее время в качестве сида
    srand(static_cast<unsigned>(time(0)));
    
    std::vector<int> arr(size);

    for (int i = 0; i < size; ++i)
    {
        arr[i] = rand() % (maxRange - minRange + 1) + minRange;
    }
    return arr;
}
