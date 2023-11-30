#include "../include/dataCollection.hpp"

// Базовый констуктор
DataCollection::DataCollection() noexcept
    : m_size1(1), m_size2(1),
      m_dynamicArray1(nullptr),
      m_dynamicArray2(nullptr),
      m_name("DefaultName")
{
    m_dynamicArray1 = new int[m_size1]{};
    m_dynamicArray2 = new int[m_size2]{};
    // std::cout << "Default constructor has been used!" << std::endl;
}

// Параметризованный конструктор
DataCollection::DataCollection(int size1, int size2, const std::string& name)
    : m_size1(size1), m_size2(size2),
      m_dynamicArray1(nullptr),
      m_dynamicArray2(nullptr),
      m_name(name)
{
    try
    {
        // Проверяем размеры
        if (m_size1 < 0 || m_size2 < 0)
        {
            throw NegativeArraySizeException();
        } else if (m_size1 > MAX_SIZE || m_size2 > MAX_SIZE)
        {
            throw SizeLimitExceededException();
        }

        m_dynamicArray1 = new int[m_size1]{};
        m_dynamicArray2 = new int[m_size2]{};
        // std::cout << "Parametrized constructor has been used!" << std::endl;
    } catch (const std::bad_alloc& e)
    {
        // В случаем, если new выдаёт ошибку очищаем ресурсы
        delete[] m_dynamicArray1;
        delete[] m_dynamicArray2;

        // Забрасываем исключение выше
        throw;
    }
}

// Move constructor
DataCollection::DataCollection(DataCollection&& other)
    : m_size1(other.m_size1), m_size2(other.m_size2),
      m_dynamicArray1(nullptr),
      m_dynamicArray2(nullptr),
      m_name(std::move(other.m_name))
{
    m_dynamicArray1 = std::exchange(other.m_dynamicArray1, nullptr);
    m_dynamicArray2 = std::exchange(other.m_dynamicArray2, nullptr);
    // std::cout << "Move constructor has been used!" << std::endl;

    // Опять проверяем ограничения на размер массива...
    if (m_size1 < 0 || m_size2 < 0)
    {
        throw NegativeArraySizeException();
    } else if (m_size1 > MAX_SIZE || m_size2 > MAX_SIZE)
    {
        throw SizeLimitExceededException();
    }

    // Проверяем на самоприсваивание
    if (this != &other)
    {
        // Обнуляем указатели на другой объект
        other.m_dynamicArray1 = nullptr;
        other.m_dynamicArray2 = nullptr;
        other.m_size1 = 0;
        other.m_size2 = 0;
    }
}

// копирующий конструктор
DataCollection::DataCollection(const DataCollection& other)
    : m_size1(other.m_size1), m_size2(other.m_size2),
      m_dynamicArray1(nullptr),
      m_dynamicArray2(nullptr),
      m_name(other.m_name)
{
    try
    {
        // Аналогично: проверяем размеры
        if (m_size1 > MAX_SIZE || m_size2 > MAX_SIZE)
        {
            throw SizeLimitExceededException();
        }

        m_dynamicArray1 = new int[m_size1]{};
        m_dynamicArray2 = new int[m_size2]{};
    } catch (const std::bad_alloc& e)
    {
        // Очищаем выделенные ресурсы
        delete[] m_dynamicArray1;
        delete[] m_dynamicArray2;

        throw;
    }
    
    // std::cout << "Copy constructor has been used!" << std::endl;

    // Проверка на самоприсваивание
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

// Деструктор
DataCollection::~DataCollection()
{
    // std::cout << "Destructor has been used!" << std::endl;

    delete[] m_dynamicArray1;
    delete[] m_dynamicArray2;
}

// Копирующий оператор присваивания
DataCollection& DataCollection::operator=(const DataCollection& other)
{
    // Проверка на самоприсваивание...
    if (this != &other)
    {
        try
        {
            // Освобождаем ресурсы
            delete[] m_dynamicArray1;
            delete[] m_dynamicArray2;

            // Проверяем размеры
            if (other.m_size1 > MAX_SIZE || other.m_size2 > MAX_SIZE)
            {
                throw SizeLimitExceededException();
            }
            // Копируем данные из другого объекта
            m_size1 = other.m_size1;
            m_size2 = other.m_size2;
            m_dynamicArray1 = new int[m_size1];
            m_dynamicArray2 = new int[m_size2];
            m_name = other.m_name;
        } catch (const std::bad_alloc& e)
        {
            // Очищаем...
            delete[] m_dynamicArray1;
            delete[] m_dynamicArray2;

            throw;
        }

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

// Перемещающий оператор присваивания
DataCollection& DataCollection::operator=(DataCollection&& other)
{
    // Проверка на самоприсваивание
    if (this != &other)
    {
        // Освобождаем ремурсы этого объекта
        delete[] m_dynamicArray1;
        delete[] m_dynamicArray2;

        // Проверяем на корректность размеров массивов
        if (other.m_size1 > MAX_SIZE || other.m_size2 > MAX_SIZE)
        {
            throw SizeLimitExceededException();
        }

        // Перемещаем данные из объекта-донора
        m_size1 = std::exchange(other.m_size1, 0);
        m_size2 = std::exchange(other.m_size2, 0);
        m_dynamicArray1 = std::exchange(other.m_dynamicArray1, nullptr);
        m_dynamicArray2 = std::exchange(other.m_dynamicArray2, nullptr);
        m_name = std::move(other.m_name);
    }

    return *this;
}

// Сеттер для заполнения массивов
void DataCollection::setDynamicArrays(const int* arr1, const int* arr2) noexcept
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

// Перегружаем оператор []
int& DataCollection::operator[](int index)
{
    if (index >= 0 && index < m_size1)
    {
        return m_dynamicArray1[index];
    }
    else if (index >= m_size1 && index < m_size1 + m_size2)
    {
        return m_dynamicArray2[index - m_size1];
    }
    else if (index < 0)
    {
        throw NegativeNumberIndexingException();
    }
    else
    {
        throw IndexOutOfBoundsException();
    }
}

//  Перегружаем оператор [] - константная версия
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
    else if (index < 0)
    {
        throw NegativeNumberIndexingException();
    }
    else
    {
        throw IndexOutOfBoundsException();
    }
}

// Перегружаем оператор вывода << для печати объекта в консоль
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
