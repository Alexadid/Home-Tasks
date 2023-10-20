#include "dataCollection.hpp"

// Конструктор по умолчанию
DataCollection::DataCollection()
    : m_size1(1), m_size2(1),
      m_dynamicArray1(new int[1]()),
      m_dynamicArray2(new int[1]()),
      m_name("DefaultName")
{
    std::cout << "Default constructor has been used!" << std::endl;
}

// Параметризованный конструктор
DataCollection::DataCollection(int size1, int size2, const std::string& name)
    : m_size1(size1), m_size2(size2),
      m_dynamicArray1(new int[size1]()),
      m_dynamicArray2(new int[size2]()),
      m_name(name)
{
    std::cout << "Parametrized constructor has been used!" << std::endl;
}

// Перемещающий конструктор
DataCollection::DataCollection(DataCollection&& other) noexcept
    : m_size1(std::move(other.m_size1)), m_size2(std::move(other.m_size2)),
      m_dynamicArray1(std::move(other.m_dynamicArray1)),
      m_dynamicArray2(std::move(other.m_dynamicArray2)),
      m_name(std::move(other.m_name))
{
    std::cout << "Move constructor has been used!" << std::endl;
}

// Копирующий конструктор
DataCollection::DataCollection(const DataCollection& other)
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
DataCollection::~DataCollection()
{
    std::cout << "Destructor has been used!" << std::endl;

    delete[] m_dynamicArray1;
    delete[] m_dynamicArray2;
}

// Копирующий оператор присвоения
DataCollection& DataCollection::operator=(const DataCollection& other)
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
DataCollection& DataCollection::operator=(DataCollection&& other) noexcept
{
    swap(*this, other);
    return *this;
}

// Вспомогательая функция для перемещения данных
void DataCollection::swap(DataCollection& first, DataCollection& second)
{
    std::swap(first.m_size1, second.m_size1);
    std::swap(first.m_size2, second.m_size2);
    std::swap(first.m_dynamicArray1, second.m_dynamicArray1);
    std::swap(first.m_dynamicArray2, second.m_dynamicArray2);
    std::swap(first.m_name, second.m_name);
}

// Сеттер для заполнения динамических массивов
void DataCollection::setDynamicArrays(const int* arr1, const int* arr2)
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
int& DataCollection::operator[](int index)
{
    if (index >= 0 && index < m_size1)
    {
        return m_dynamicArray1[index];
    } else if (index >= m_size1 && index < m_size1 + m_size2)
    {
        return m_dynamicArray2[index - m_size1];
    } else
    {
        // В том числе проверка на выход за границы массивов
        throw std::out_of_range("Index out of bounds");
    }
}

// Перегрузка опертора << для вывода объекта класса в консоль
std::ostream& operator<<(std::ostream& os, const DataCollection& obj)
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
