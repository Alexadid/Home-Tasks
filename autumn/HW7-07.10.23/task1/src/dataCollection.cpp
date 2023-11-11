#include "../include/dataCollection.hpp"

// Конструктор по умолчанию
DataCollection::DataCollection()
    : m_size1(1), m_size2(1),
      m_dynamicArray1(nullptr),
      m_dynamicArray2(nullptr),
      m_name("DefaultName")
{
    m_dynamicArray1 = new int[m_size1]{};
    m_dynamicArray2 = new int[m_size2]{};
    std::cout << "Default constructor has been used!" << std::endl;
}

// Параметризованный конструктор
DataCollection::DataCollection(int size1, int size2, const std::string& name)
    : m_size1(size1), m_size2(size2),
      m_dynamicArray1(nullptr),
      m_dynamicArray2(nullptr),
      m_name(name)
{
    m_dynamicArray1 = new int[m_size1]{};
    m_dynamicArray2 = new int[m_size2]{};
    std::cout << "Parametrized constructor has been used!" << std::endl;
}

// Перемещающий конструктор
DataCollection::DataCollection(DataCollection&& other) noexcept
    : m_size1(other.m_size1), m_size2(other.m_size2),
      m_dynamicArray1(nullptr),
      m_dynamicArray2(nullptr),
      m_name(std::move(other.m_name))
{
    m_dynamicArray1 = std::exchange(other.m_dynamicArray1, nullptr);
    m_dynamicArray2 = std::exchange(other.m_dynamicArray2, nullptr);
    std::cout << "Move constructor has been used!" << std::endl;
    if (this != &other)
    {
        // Nullify the pointers in the 'other' object
        other.m_dynamicArray1 = nullptr;
        other.m_dynamicArray2 = nullptr;
        other.m_size1 = 0;
        other.m_size2 = 0;
    } 
}

// Копирующий конструктор
DataCollection::DataCollection(const DataCollection& other)
    : m_size1(other.m_size1), m_size2(other.m_size2),
      m_dynamicArray1(nullptr),
      m_dynamicArray2(nullptr),
      m_name(other.m_name)
{
    m_dynamicArray1 = new int[m_size1]{};
    m_dynamicArray2 = new int[m_size2]{};
    std::cout << "Copy constructor has been used!" << std::endl;

    if (this != &other)
    {
        for (int i = 0; i < m_size1; i++)
        {
            m_dynamicArray1[i] = other.m_dynamicArray1[i];
        }

        for (int i = 0; i < m_size2; i++)
        {
            m_dynamicArray2[i] = other.m_dynamicArray2[i];
        }
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
    if (this != &other)
    {
        // Free resources in the current object
        delete[] m_dynamicArray1;
        delete[] m_dynamicArray2;

        // Move data from the donor object
        m_size1 = std::exchange(other.m_size1, 0);
        m_size2 = std::exchange(other.m_size2, 0);
        m_dynamicArray1 = std::exchange(other.m_dynamicArray1, nullptr);
        m_dynamicArray2 = std::exchange(other.m_dynamicArray2, nullptr);
        m_name = std::move(other.m_name);
    }

    return *this;
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

// Перегрузка опертора доступа - [] const версия
const int& DataCollection::operator[](int index) const
{
    if (index >= 0 && index < m_size1)
    {
        return m_dynamicArray1[index];
    }
    else if (index >= m_size1 && index < m_size1 + m_size2)
    {
        return m_dynamicArray2[index - m_size1];
    }
    else
    {
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
