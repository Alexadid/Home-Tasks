#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

// Заранее объявляем функции
std::vector<int> generateRandomArray(int size, int minRange, int maxRange);
void merge(std::vector<int>& arr, int left, int middle, int right, std::vector<int>& temp);
void mergeSort(std::vector<int>& arr, int left, int right, std::vector<int>& temp);

int main()
{
    const int size = 10;
    // Указываем диапазон генерации случайных чисел в массиве
    const int minRange = 0;
    const int maxRange = 100;

    // Проводим генерацию массива
    std::vector<int> arr = generateRandomArray(size, minRange, maxRange);

    // Вспомогательный массив
    std::vector<int> temp(arr.size());

    std::cout << "Original array: ";
    for (size_t num : arr)
    {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    mergeSort(arr, 0, arr.size() - 1, temp);

    std::cout << "Sorted array: ";
    for (size_t num : arr)
    {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}

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

// Функция для сливания двух отсортированных массивов в один сортированный
void merge(std::vector<int>& arr, int left, int middle, int right, std::vector<int>& temp)
{
    // Подсчитываем размеры двух подмассивов
    int sizeOfFirstArr = middle - left + 1;
    int sizeOfSecondArr = right - middle;

    // Копируем данные из исходного массива в временный
    for (size_t i = 0; i < sizeOfFirstArr; i++)
    {
        temp[i] = arr[left + i];
    }

    // Сливаем два подмассива из временного массива temp в исходный
    int i = 0, j = middle + 1, k = left; // Возможно не лучшие названия для индексов...
    while (i < sizeOfFirstArr && j <= right)
    {
        if (temp[i] <= arr[j])
        {
            arr[k] = temp[i];
            i++;
        } else
        {
            arr[k] = arr[j];
            j++;
        }
        k++;
    }

    // Копируем все оставшиеся элементы из левого подмассива (если они вообще есть)
    while (i < sizeOfFirstArr)
    {
        arr[k] = temp[i];
        i++;
        k++;
    }
}

// Рекурсивная фвкнция для преводения сортровки слянием
void mergeSort(std::vector<int>& arr, int left, int right, std::vector<int>& temp)
{
    if (left < right)
    {
        // Находим серединную точку для деления массива на две половины
        int middle = left + (right - left) / 2;

        // Рекурсивно сортируем две половины
        mergeSort(arr, left, middle, temp);
        mergeSort(arr, middle + 1, right, temp);

        // Сливаем отсортированные половины
        merge(arr, left, middle, right, temp);
    }
}
