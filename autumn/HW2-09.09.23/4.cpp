#include <iostream>

int main()
{
    int sizeOfArray1, sizeOfArray2;

    // Вводим размер первого массива
    std::cout << "Enter the size of the first array: ";
    std::cin >> sizeOfArray1;

    // Создаём динамисекий массив заданного размера при помощи new
    int* array1 = new int[sizeOfArray1];

    // Заполняем первый массив данным из консоли
    std::cout << "Enter " << sizeOfArray1 << " integers for the first array: ";
    for (int i = 0; i < sizeOfArray1; i++)
    {
        std::cin >> array1[i];
    }

    // Просим пользователя ввести размер второго массива
    std::cout << "Enter the size of the second array: ";
    std::cin >> sizeOfArray2;

    // Создаём динамисекий массив второго размера
    int* array2 = new int[sizeOfArray2];

    // Копируем данные из первого массива во второй
    for (int i = 0; i < sizeOfArray2; i++)
    {
        if (i < sizeOfArray1)
        {
            array2[i] = array1[i];
        } else
        {
            std::cout << "Enter an integer for position " << i << ": ";
            std::cin >> array2[i];
        }
    }

    // Подсчитываем среднее значение элементов второго массива
    double sum = 0;
    for (int i = 0; i < sizeOfArray2; i++)
    {
        sum += array2[i];
    }
    double average = sizeOfArray2 > 0 ? sum / sizeOfArray2 : 0;

    std::cout << "The average value of elements in the second array is: " << average << std::endl;

    // Освобождаем задействованную массивами память
    delete[] array1;
    delete[] array2;

    return 0;
}
