#ifndef DATACOLLECTION_H
#define DATACOLLECTION_H

#include <iostream>
#include <string>
#include <utility>

class DataCollection {
private:
    int m_size1;
    int m_size2;
    int* m_dynamicArray1;
    int* m_dynamicArray2;
    std::string m_name;

public:
    DataCollection();
    DataCollection(int size1, int size2, const std::string& name);
    DataCollection(DataCollection&& other) noexcept;
    DataCollection(const DataCollection& other);
    ~DataCollection();
    DataCollection& operator=(const DataCollection& other);
    DataCollection& operator=(DataCollection&& other) noexcept;
    void setDynamicArrays(const int* arr1, const int* arr2);
    int& operator[](int index);
    friend std::ostream& operator<<(std::ostream& os, const DataCollection& obj);
    void swap(DataCollection& first, DataCollection& second);
};

#endif
