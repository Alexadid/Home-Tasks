#include <iostream>
#include <algorithm>

// Шаблон функции для поиска в встроенном массиве
template <typename T, std::size_t N, typename Predicate = std::equal_to<T>>
auto findValue(T (&array)[N], const T& value, Predicate pred = Predicate{}) -> T*
{
    for (std::size_t i = 0; i < N; ++i)
    {
        // Используем предоставленный пользователем компаратор
        if (pred(array[i], value))
        {
            return &array[i];
        }
    }

    // Возвращаем nullptr, если значение не было найдено
    return nullptr;
}

// Шаблон функции для поиска в встроенном динамическом массиве
template <typename T, typename Predicate = std::equal_to<T>>
auto findValue(T* array, std::size_t size, const T& value, Predicate pred = Predicate{}) -> T*
{
    for (std::size_t i = 0; i < size; ++i)
    {
        // Используем предоставленный пользователем компаратор
        if (pred(array[i], value))
        {
            return &array[i];
        }
    }

    // Возвращаем nullptr, если значение не было найдено
    return nullptr;
}

int main()
{
    const int sizeOfArray = 4;
    int array[] = {1, 2, 3, 4};

    // Ищем в встроенном массиве
    int valueToFind = 3;
    auto resultFixedArray = findValue(array, valueToFind);

    if (resultFixedArray != nullptr)
    {
        std::cout << "Value " << valueToFind << " found in the fixed-size array." << std::endl;
    }
    else
    {
        std::cout << "Value " << valueToFind << " not found in the fixed-size array." << std::endl;
    }

    // Ищем в встроенном динамическом массиве
    const int sizeDynamicArray = sizeOfArray;
    int* dynamicArray = new int[sizeOfArray]{1, 2, 3, 4};

    // Для примера используем собственный компаратор
    auto resultDynamicArray = findValue(dynamicArray, sizeDynamicArray, valueToFind,
                                       [](const int& a, const int& b) { return a == b; });

    if (resultDynamicArray != nullptr)
    {
        std::cout << "Value " << valueToFind << " found in the dynamic array." << std::endl;
    }
    else
    {
        std::cout << "Value " << valueToFind << " not found in the dynamic array." << std::endl;
    }

    // Не забываем освободить ресурсы!
    delete[] dynamicArray;

    return 0;
}
