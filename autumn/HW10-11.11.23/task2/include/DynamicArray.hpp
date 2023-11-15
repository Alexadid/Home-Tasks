#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include <iostream>
#include <string>
#include <utility>
#include <stdexcept>

template <typename T>
class DynamicArray
{
private:
    int m_size;
    T* m_data;
    T* m_backup;

public:
    // Конструктор по умолчанию
    DynamicArray()
        : m_size(0),
          m_data(nullptr),
          m_backup(nullptr)
    {
        // std::cout << "Default constructor has been used!" << std::endl;
    }

    // Параметризованный конструктор
    // Все ячейки динамического массива заполняются знаечнием заданного типа
    DynamicArray(int size, const T& value = T())
        : m_size(size),
          m_data(nullptr),
          m_backup(nullptr)
    {
        m_data = new T[size]{};
        m_backup = new T[size]{};

        std::fill(m_data, m_data + m_size, value);
        copyData(m_data, m_backup, m_size);

        // std::cout << "Parametrized constructor has been used!" << std::endl;
    }

    // Копирующий конструткор
    DynamicArray(const DynamicArray& other)
        : m_size(other.m_size),
          m_data(nullptr),
          m_backup(nullptr)
    {
        // Проверка на само присваивание
        if (this != &other)
        {
            m_data = new T[other.m_size]{};
            m_backup = new T[other.m_size]{};

            copyData(other.m_data, m_data, m_size);
            copyData(other.m_backup, m_backup, m_size);
        }

        // std::cout << "Copy constructor has been used!" << std::endl;
    }

    // Перемещающий конструткор
    DynamicArray(DynamicArray&& other) noexcept
        : m_size(0),
          m_data(nullptr),
          m_backup(nullptr)
    {
        swap(other);

        // Проверка на само присваивание
        if (this != &other)
        {
            delete[] other.m_data;
            delete[] other.m_backup;
            other.m_data = nullptr;
            other.m_backup = nullptr;
            other.m_size = 0;
        }

        // std::cout << "Move constructor has been used!" << std::endl;
    }

    // Деструктор
    ~DynamicArray()
    {
        delete[] m_data;
        delete[] m_backup;

        // std::cout << "Destructor has been used!" << std::endl;
    }

    // Копирующий оператор присвоения
    DynamicArray& operator=(const DynamicArray& other)
    {
        if (this != &other)
        {
            delete[] m_data;
            delete[] m_backup;

            m_size = other.m_size;
            m_data = new T[m_size]{};
            m_backup = new T[m_size]{};

            copyData(other.m_data, m_data, m_size);
            copyData(other.m_backup, m_backup, m_size);
        }
        return *this;
    }

    // Пермещающий оператор присвоения
    DynamicArray& operator=(DynamicArray&& other) noexcept
    {
        if (this != &other)
        {
            delete[] m_data;
            delete[] m_backup;

            m_size = 0;
            m_data = nullptr;
            m_backup = nullptr;

            swap(other);

            delete[] other.m_data;
            delete[] other.m_backup;
            other.m_data = nullptr;
            other.m_backup = nullptr;
            other.m_size = 0;
        }
        return *this;
    }

    // Оператор обращения к элементу
    T& operator[](int index)
    {
        if (index < 0 || index >= m_size)
        {
            std::out_of_range("Index out of range");
        }
        return m_data[index];
    }

    const T& operator[](int index) const
    {
        if (index < 0 || index >= m_size)
        {
            throw std::out_of_range("Index out of bounds");
        }
        return m_data[index];
    }

    // Оператор вывода
    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, const DynamicArray<U>& array)
    {
        for (int i = 0; i < array.m_size; i++)
        {
            os << array.m_data[i] << ' ';
        }
        os << std::endl;
        return os;
    }

    // Функция размера динамического массива
    int size() const
    {
        return m_size;
    }

    // Функция изменения размеров массива
    void resize(int newSize, const T& value = T())
    {
        if (newSize <= 0)
        {
            std::out_of_range("Index out of range");
        }
        else if (newSize < m_size)
        {
            // Уменьшаем размер, выкидываем избытычные элементы
            DynamicArray<T> temp(newSize);
            copyData(m_data, temp.m_data, newSize);
            swap(temp);
        }
        else if (newSize > m_size)
        {
            // Увеличиваем размер, заполняем новые клетки предложенным значением
            // или полагаемся на поведения при инициализации по умолчанию
            DynamicArray<T> temp(newSize, value);
            copyData(m_data, temp.m_data, m_size);
            swap(temp);
        }
        // Если newSize равен m_size, то не делаем ровным счётом ничего
}


    // Функция swap
    void swap(DynamicArray& other)
    {
        std::swap(m_data, other.m_data);
        std::swap(m_backup, other.m_backup);
        std::swap(m_size, other.m_size);
    }

    // Функция push_back
    void push_back(const T& value)
    {
        resize(m_size + 1, value);
    }

private:
    // Вспомогательная фукнция для глубокого копирования
    void copyData(const T* source, T* destination, int size)
    {
        for (int i = 0; i < size; i++)
        {
            destination[i] = source[i];
        }
    }
};

#endif
