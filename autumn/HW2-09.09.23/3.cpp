#include <iostream>
#include <vector>

// Функция для проверки отсортирован ли массив
bool isSorted(const std::vector<int>& arr)
{
    for (size_t i = 1; i < arr.size(); ++i)
    {
        if (arr[i] < arr[i - 1])
        {
            return false;
        }
    }
    return true;
}

// Функция для проведения бинарного поиска по массиву
bool binarySearch(const std::vector<int>& arr, int target)
{
    int left = 0;
    int right = arr.size() - 1;

    while (left <= right)
    {
        int mid = left + (right - left) / 2;

        if (arr[mid] == target)
        {
            // Число найдено!
            return true;
        } else if (arr[mid] < target)
        {
            // Отбрасываем левую половину
            left = mid + 1;
        } else
        {
            // Отбрасываем правую половину
            right = mid - 1;
        }
    }

    // Элемент так и не был обнаружен... Жаль
    return false;
}

int main()
{
    std::vector<int> sortedArray;
    int numElements;

    // Вводим количество элементов в векторе
    std::cout << "Enter the number of elements: ";
    std::cin >> numElements;

    // Вводим элементы вектора
    std::cout << "Enter " << numElements << " sorted elements: ";
    for (int i = 0; i < numElements; ++i)
    {
        int element;
        std::cin >> element;
        sortedArray.push_back(element);
    }

    // Проверяем отсортирован ли вектор
    if (!isSorted(sortedArray))
    {
        std::cout << "The input vector is not sorted. Please enter a sorted vector." << std::endl;
        return 1;
    }

    int target;

    // Вводим число, которое будем искать в векторе
    std::cout << "Enter the number to search for: ";
    std::cin >> target;

    if (binarySearch(sortedArray, target))
    {
        std::cout << "Element " << target << " found in the array." << std::endl;
    } else
    {
        std::cout << "Element " << target << " not found in the array." << std::endl;
    }

    return 0;
}
