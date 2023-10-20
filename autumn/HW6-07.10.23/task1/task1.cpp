#include <iostream>
#include <string>
#include <utility> // for std::move

class DataCollection {
private:
    int m_size1;
    int m_size2;
    int* m_dynamicArray1;
    int* m_dynamicArray2;
    std::string m_name;

public:
    // Конструктор по умолчанию
    DataCollection()
        : m_size1(1), m_size2(1),
        m_dynamicArray1(new int[1]()),
        m_dynamicArray2(new int[1]()),
        m_name("DefaultName")
    {
        std::cout << "Default constructor has been used!" << std::endl;
    }

    // Параметризованный конструктор
    DataCollection(int size1, int size2, const std::string& name)
        : m_size1(size1), m_size2(size2),
        m_dynamicArray1(new int[size1]()),
        m_dynamicArray2(new int[size2]()),
        m_name(name)
    {
        std::cout << "Parametrized constructor has been used!" << std::endl;
    }

    // Перемещающий конструктор
    DataCollection(DataCollection&& other) noexcept
        : m_size1(std::move(other.m_size1)), m_size2(std::move(other.m_size2)),
          m_dynamicArray1(std::move(other.m_dynamicArray1)),
          m_dynamicArray2(std::move(other.m_dynamicArray2)),
          m_name(std::move(other.m_name))
    {
        std::cout << "Move constructor has been used!" << std::endl;
    }

    // Копирующий конструктор
    DataCollection(const DataCollection& other)
        : m_size1(other.m_size1), m_size2(other.m_size2),
        m_dynamicArray1(new int[other.m_size1]),
        m_dynamicArray2(new int[other.m_size2]),
        m_name(other.m_name)
    {
        std::cout << "Copy constructor has been used!" << std::endl;
        for (int i = 0; i < m_size1; i++)
        {
            m_dynamicArray1[i] = other.m_dynamicArray1[i];
        }

        for (int i = 0; i < m_size2; i++)
        {
            m_dynamicArray2[i] = other.m_dynamicArray2[i];
        }
    }

    // Деструктор, освобождает ресурсы, задействованные динамическими массивами
    ~DataCollection()
    {
        std::cout << "Destructor has been used!" << std::endl;

        if (m_dynamicArray1 != nullptr)
        {
            delete[] m_dynamicArray1;
        }

        if (m_dynamicArray2 != nullptr)
        {
            delete[] m_dynamicArray2;
        }
    }

    // Копирующий оператор присвоения
    DataCollection& operator=(const DataCollection& other)
    {
        if (this != &other)
        {
            // Освобожаем текущие ресурсы
            delete[] m_dynamicArray1;
            delete[] m_dynamicArray2;

            // Копируем данные из другого объекта
            m_size1 = other.m_size1;
            m_size2 = other.m_size2;
            m_dynamicArray1 = new int[m_size1];
            m_dynamicArray2 = new int[m_size2];
            m_name = other.m_name;

            for (int i = 0; i < m_size1; i++)
            {
                m_dynamicArray1[i] = other.m_dynamicArray1[i];
            }
            for (int i = 0; i < m_size2; i++)
            {
                m_dynamicArray2[i] = other.m_dynamicArray2[i];
            }
        }
        return *this;
    }

    // Перемещающий оператор присвоения
    DataCollection& operator=(DataCollection&& other) noexcept
    {
        swap(*this, other);
        return *this;
    }

    friend void swap(DataCollection& first, DataCollection& second)
    {
        std::swap(first.m_size1, second.m_size1);
        std::swap(first.m_size2, second.m_size2);
        std::swap(first.m_dynamicArray1, second.m_dynamicArray1);
        std::swap(first.m_dynamicArray2, second.m_dynamicArray2);
        std::swap(first.m_name, second.m_name);
    }

    // Сеттер для заполнения динамических массивов
    void setDynamicArrays(const int* arr1, const int* arr2)
    {
        for (int i = 0; i < m_size1; i++)
        {
            m_dynamicArray1[i] = arr1[i];
        }

        for (int i = 0; i < m_size2; i++)
        {
            m_dynamicArray2[i] = arr2[i];
        }
    }

    // Перегрузка опертора доступа - []
    int& operator[](int index)
    {
        if (index >= 0 && index < m_size1)
        {
            return m_dynamicArray1[index];
        } else if (index >= m_size1 && index < m_size1 + m_size2)
        {
            return m_dynamicArray2[index - m_size1];
        } else
        {
            throw std::out_of_range("Index out of bounds");
        }
    }

    // Перегрузка опертора << для вывода объекта класса в консоль
    friend std::ostream& operator<<(std::ostream& os, const DataCollection& obj)
    {
        os << "Name: " << obj.m_name << std::endl;
        os << "Array 1: ";

        for (int i = 0; i < obj.m_size1; i++)
        {
            os << obj.m_dynamicArray1[i] << ' ';
        }

        os << std::endl;
        os << "Array 2: ";

        for (int i = 0; i < obj.m_size2; i++)
        {
            os << obj.m_dynamicArray2[i] << ' ';
        }

        os << std::endl;
        return os;
    }
};

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