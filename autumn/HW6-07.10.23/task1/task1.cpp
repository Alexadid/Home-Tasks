#include "dataCollection.hpp"

int main()
{
    // Тестируем класс на параметризованный констурктор, сеттор и вывод в консоль
    size_t sizeOfDynamicArray1 = 3;
    size_t sizeOfDynamicArray2 = 2;
    std::string nameOfTestDataObject = "Object of DataCollection class";
    DataCollection data(sizeOfDynamicArray1, sizeOfDynamicArray2, nameOfTestDataObject);
    int dynamicArray1[] = {1, 2, 3};
    int dynamicArray2[] = {4, 5};
    data.setDynamicArrays(dynamicArray1, dynamicArray2);
    std::cout << data << std::endl;

    // Здесь тестируем конструктор по колчанию
    auto newData = DataCollection();
    // А вот здесь присваивающий опретор присвоения
    newData = data;
    // Как видим вначале выводятся данные из первого динамического массива, а затем из второго
    for (size_t i = 0; i < sizeOfDynamicArray1 + sizeOfDynamicArray2; i++)
    {
        std::cout << newData[i] << std::endl;
    }

    // Здесь же можно продемонстрировать существующую проверку на выход за пределы массивов
    // Очевидно вызовет ошибку
    //std::cout << newData[sizeOfDynamicArray1 + sizeOfDynamicArray2];

    // Проверка работоспособности копирующего конструктора
    auto copiedData = DataCollection(newData);
    std::cout << copiedData << std::endl;

    // Проверка работоспособности перемещающего конструктора
    auto movedData = DataCollection(std::move(newData));
    std::cout << movedData << std::endl;

    return 0;
}
