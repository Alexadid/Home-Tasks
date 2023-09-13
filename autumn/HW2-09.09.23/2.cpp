#include <iostream>
#include <vector>
#include <cstdlib>   // для rand() и srand()
#include <ctime>     // для time()

// Функция для генерации слуяайного массива заданного размера с заданным диапазоном
std::vector<int> generateRandomArray(int size, int minRange, int maxRange)
{
    // Задаём генератору случайных чисел текущее время в качестве сида
    srand(static_cast<unsigned>(time(0)));
    
    std::vector<int> arr(size);

    for (size_t i = 0; i < size; ++i)
    {
        arr[i] = rand() % (maxRange - minRange + 1) + minRange;
    }
    return arr;
}

// Функция для сортировки массива целых чисел вставками
void insertionSort(std::vector<int>& arr)
{
    int n = arr.size();
    for (size_t i = 1; i < n; ++i)
    {
        int key = arr[i];
        int j = i - 1;

        // Перемещаем элементы arr[0..i-1], которые больше key,
        // на одну позицию впереди их текущей позиции
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key;
    }
}

// Функция для сортировки массива целых чисел вставками с использованием std::swap
// Во многом идея позаимствована из статьи на Википедии
void insertionSortWithSwap(std::vector<int>& arr)
{
    for (size_t i = 1; i < arr.size(); ++i)
    {
        for (size_t j = i; j > 0 && arr[j] < arr[j - 1]; --j)
        {
            std::swap(arr[j], arr[j - 1]);
        }
    }
}

int main()
{
    const int size = 10;
    // Указываем диапазон генерации случайных чисел в массиве
    const int minRange = 0;
    const int maxRange = 100;

    // Проводим генерацию массива
    std::vector<int> numbers = generateRandomArray(size, minRange, maxRange);

    // Переменная для хранения ответа польлзователя на вопрос о типе сортировки
    char userAnswer;

    // Выводим неотсортированный массив
    std::cout << "Original Array: ";
    for (int num : numbers)
    {
        std::cout << num << " ";
    }
    std::cout << std::endl;


    while(true)
    {
        std::cout << "Would you like to sort your array using std::swap[Y/N]? ";
        std::cin >> userAnswer;

        if (userAnswer == 'Y')
        {
            insertionSortWithSwap(numbers);
            break;
        } else if (userAnswer == 'N')
        {
            insertionSort(numbers);
            break;
        } else
        {
            std::cout << "Error, you've entered the unsupported option for this question. Try again..." << std::endl;
        }  
    }  

    // Выводим отсортированный массив
    std::cout << "Sorted Array: ";
    for (int num : numbers)
    {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
