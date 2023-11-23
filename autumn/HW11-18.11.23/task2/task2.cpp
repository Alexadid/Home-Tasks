#include <iostream>
#include <utility>



template <typename DynamicType1, typename DynamicType2, typename... Args>
auto create_objects(Args&&... args)
{
    // Создаём первый объект, используя конструктор по умолчанию
    DynamicType1* obj1 = new DynamicType1();
    // Создаём второй объект, используя предоставленные аргументы
    DynamicType2* obj2 = new DynamicType2(std::forward<Args>(args)...);

    return std::make_pair(obj1, obj2);
}

// Примерный код
class ExampleType1
{
public:
    ExampleType1()
    {
        std::cout << "Default constructor of ExampleType1" << std::endl;
    }

    ~ExampleType1()
    {
        // std::cout << "Freed 1?!" << std::endl;
    }
};

class ExampleType2
{
public:
    ExampleType2(int a, double b)
    {
        std::cout << "Constructor of ExampleType2 with arguments: " << a << " and " << b << std::endl;
    }

    ~ExampleType2()
    {
        // std::cout << "Freed 2?!" << std::endl;
    }
};

int main()
{
    int argument1 = 49;
    double argument2 = 3.14;
    auto objects = create_objects<ExampleType1, ExampleType2>(argument1, argument2);

    // Здесь делаем что-то с созданными объектами...

    // И, разумеется, не забываем освободить аллоцированную память
    // Хоть бы без утечек...
    delete objects.first;
    delete objects.second;

    return 0;
}
