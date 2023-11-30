#ifndef DATACOLLECTION_H
#define DATACOLLECTION_H

#include <iostream>
#include <string>
#include <stdexcept>

class DataCollectionException : public std::exception
{
private:
    std::string errorMessage;

public:
    explicit DataCollectionException(const char* message) : errorMessage(message) {}

    // Переопределяем функцию what(), чтобы выдать сообщение об ошибке
    const char* what() const noexcept override
    {
        return errorMessage.c_str();
    }
};

class IndexOutOfBoundsException : public DataCollectionException
{
public:
    IndexOutOfBoundsException() : DataCollectionException("Index out of bounds") {}
};

class SizeLimitExceededException : public DataCollectionException
{
public:
    SizeLimitExceededException() : DataCollectionException("Size limit exceeded") {}
};

class LogicalErrorException : public DataCollectionException
{
public:
    LogicalErrorException() : DataCollectionException("Logical error occurred") {}
};

class NegativeNumberIndexingException : public DataCollectionException
{
public:
    NegativeNumberIndexingException() : DataCollectionException("Negative number indexing") {}
};

class NegativeArraySizeException : public DataCollectionException
{
public:
    NegativeArraySizeException() : DataCollectionException("Negative size of the array") {}
};

class DataCollection
{
private:
    static const int MAX_SIZE = 100; // Максимальный допустимый каждого из массивов

    int m_size1;
    int m_size2;
    int* m_dynamicArray1;
    int* m_dynamicArray2;
    std::string m_name;

public:
    DataCollection() noexcept;
    DataCollection(int size1, int size2, const std::string& name);
    DataCollection(DataCollection&& other);
    DataCollection(const DataCollection& other);
    ~DataCollection();
    DataCollection& operator=(const DataCollection& other);
    DataCollection& operator=(DataCollection&& other);
    void setDynamicArrays(const int* arr1, const int* arr2) noexcept;
    int& operator[](int index);
    const int& operator[](int index) const;
    friend std::ostream& operator<<(std::ostream& os, const DataCollection& obj);
};

#endif
