#include "include/DynamicArray.hpp"



int main()
{
    // Конструктор по умолчанию
    DynamicArray<int> array1;
    std::cout << "arr1: " << array1 << std::endl;

    // параметризованный конструткор
    int sizeOfArray2 = 5;
    int fillInValue = 12;
    DynamicArray<int> array2(sizeOfArray2, fillInValue);
    std::cout << "array2: " << array2 << std::endl;

    // Копирующий конструткор
    DynamicArray<int> array3(array2);
    std::cout << "array3 (copy of array2): " << array3 << std::endl;

    // перемещающий конструткор
    DynamicArray<int> array4(std::move(array3));
    std::cout << "array3 after move: " << array3 << std::endl;
    std::cout << "array4 (moved from array3): " << array4 << std::endl;

    // Копирующий оператор присвоения
    DynamicArray<int> array5;
    array5 = array2;
    std::cout << "array5 (copy of array2): " << array5 << std::endl;

    // Перемещающий оператор присвоения
    DynamicArray<int> array6;
    array6 = std::move(array5);
    std::cout << "array6 (moved from array5): " << array6 << std::endl;
    std::cout << "array5 after move: " << array5 << std::endl;

    // Оператор обращения к элементу массива
    int arbitrtayIndex = 2;
    int fillInValueForIndex = 99;
    array6[arbitrtayIndex] = fillInValueForIndex;
    std::cout << "array6 after modifying element at index 2: " << array6 << std::endl;

    // Функция для вывода размера массива
    std::cout << "Size of array6: " << array6.size() << std::endl;

    // Фкнция изменения массива с заполнением пустых клеток (если такие появляются) заданным значением
    int newSizeOfArray = 8;
    array6.resize(newSizeOfArray);
    std::cout << "array6 after resizing to 8 elements: " << array6 << std::endl;

    // Функция push_back
    int pushBackValue = 888;
    array6.push_back(pushBackValue);
    std::cout << "array6 after push_back: " << array6 << std::endl;

    return 0;
}
