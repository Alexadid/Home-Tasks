#include "include/dataCollection.hpp"

int main()
{
    // Тестируем класс на параметризованный констурктор, сеттор и вывод в консоль
    size_t sizeOfDynamicArray1 = 3;
    size_t sizeOfDynamicArray2 = 2;
    std::string nameOfTestDataObject1 = "Object of DataCollection class";
    DataCollection data(sizeOfDynamicArray1, sizeOfDynamicArray2, nameOfTestDataObject1);
    int dynamicArray1[] = {1, 2, 3};
    int dynamicArray2[] = {4, 5};
    data.setDynamicArrays(dynamicArray1, dynamicArray2);
    std::cout << data << std::endl;

    // Здесь тестируем конструктор по умолчанию
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
    // std::cout << newData[sizeOfDynamicArray1 + sizeOfDynamicArray2];

    // Проверка работоспособности копирующего конструктора
    auto copiedData = DataCollection(newData);
    std::cout << copiedData << std::endl;

    // Проверка работоспособности перемещающего конструктора
    auto movedData = DataCollection(std::move(newData));
    std::cout << movedData << std::endl;



    // Проверка работоспособности перемещающего оператора присвоения
    // Создаём новый объект класса DataCollection
    int sizeOfDynamicArray3 = 3;
    int sizeOfDynamicArray4 = 4;
    std::string nameOfTestDataObject2 = "Object1";
    DataCollection newObject1(sizeOfDynamicArray3, sizeOfDynamicArray4, nameOfTestDataObject2);
    int dynamicArray3[] = {1, 2, 3};
    int dynamicArray4[] = {4, 5, 6, 7};
    newObject1.setDynamicArrays(dynamicArray3, dynamicArray4);

    // Выводим исходный объект
    std::cout << "Original Object:\n" << newObject1 << std::endl;

    // Создаём второй объект
    DataCollection newObject2;

    // Используем перемещающий оператор присвоения, чтобы переместить данные из newObject1 в newObject2
    newObject2 = std::move(newObject1);

    // Отображаем модифицированные объекты
    std::cout << "Object 1 after move:\n" << newObject1 << std::endl;
    std::cout << "Object 2 after move assignment:\n" << newObject2 << std::endl;

    return 0;
}
