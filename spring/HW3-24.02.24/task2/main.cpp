#include <random>
#include <vector>
#include <algorithm>
#include <set>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include "boost/functional/hash.hpp"



// Определяем структуру с различными типами полей 
struct MyStruct
{
    int intValue;
    std::string stringValue;
    bool boolValue;

    // Конструктор по умолчанию для структуры
    MyStruct() : intValue(0), stringValue(""), boolValue(false) {}

    // И конструктор с возможностью инициализировать поля
    // (исопльзовался в том числе во время тестирования)
    MyStruct(int i, const std::string& s, bool b) : intValue(i), stringValue(s), boolValue(b) {}
};

// При помощи boost::hash_combine определим хэш-функцию для нашей структуры
size_t hash_value(const MyStruct& mStruct)
{
    size_t seed = 0;
    boost::hash_combine(seed, mStruct.intValue);
    boost::hash_combine(seed, mStruct.stringValue);
    boost::hash_combine(seed, mStruct.boolValue);
    return seed;
}

// Шаблонная функция для заполнения контейнеров уникальным случайно сгенерированными MyStruct
template<typename Container>
void fillContainerWithUniqueRandomMyStructs(Container& container)
{
    // Равномерно распределённый генератор целочисленных случайных чисел для выбора символов
    std::random_device randomDevice;
    std::mt19937 generator(randomDevice());
    // Распределения для каждого из полей
    std::uniform_int_distribution<> intDistribution(0, 99);
    std::uniform_int_distribution<> boolDistribution(0, 1);
    // Символы для будущей генерации поля-строки
    const std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
    std::uniform_int_distribution<> charDistribution(0, alphabet.size() - 1);

    std::set<std::string> uniqueRepresentations; // For checking uniqueness

    for (auto& element : container) 
    {
        MyStruct randomInstance;
        //size_t hash;
        do
        {
            int intValue = intDistribution(generator);

            // Также, как и в задаче 3 генерируем строку длиной 6 символов
            std::string stringValue(6, ' ');
            for (char& ch : stringValue)
            {
                ch = alphabet[charDistribution(generator)];
            }
            bool boolValue = boolDistribution(generator);

            randomInstance = MyStruct(intValue, stringValue, boolValue);

            // Подсчитываем хэш для структуры
            //hash = hash_value(randomInstance);
        }
        // Для генерации уникальных структур будем преобрахховывать их данные
        // в строки и пытаться вставить их в set
        while (!uniqueRepresentations.insert(std::to_string(randomInstance.intValue) + "_" +
                                             randomInstance.stringValue + "_" +
                                             std::to_string(randomInstance.boolValue)).second);

        element = randomInstance;
    }
}

int main()
{
    // Общее количество уникальных структур для генерации
    const size_t totalNumberOfStructs = 2000000;
    // Шаг количества структур для исследования коллизий
    const size_t stepSize = 25000;
    std::vector<MyStruct> structs(totalNumberOfStructs);

    // Генерируем уникальные случайные структуры
    fillContainerWithUniqueRandomMyStructs(structs);

    // Скорее тестовый код, но пусть будет
    std::cout << "Structs have been generated." << std::endl;

    // Записывать данные будем в CSV файл
    std::ofstream outputFile("hash_collision_analysis.csv");
    outputFile << "NumberOfStructs,BoostHash\n";

    // Вектор, хранящий хэши для анализа плотностей 
    std::vector<size_t> hashValues;

    for (size_t numStructs = stepSize; numStructs <= totalNumberOfStructs; numStructs += stepSize) 
    {
        //std::cout << numStructs << std::endl;

        std::unordered_map<size_t, unsigned int> hashCounts;
        // Избавляемся от предыдущих хэшей
        hashValues.clear();

        // Хэшируем каждый MyStruct и сохраняем хэш
        for (size_t i = 0; i < numStructs; ++i)
        {
            size_t hash = hash_value(structs[i]);

            hashCounts[hash]++;
            hashValues.push_back(hash);
        }

        // Подсчитываем число коллизий
        outputFile << numStructs;
        unsigned int collisions = 0;
        for (const auto& pair : hashCounts)
        {
            if (pair.second > 1)
            {
                collisions += pair.second - 1;
            }
        }
        outputFile << "," << collisions << "\n";
    }

    // Закрываем файл
    outputFile.close();
    // Информируем ползователя об окончании записи
    std::cout << "Collision data has been written to hash_collision_analysis.csv" << std::endl;

    // Сохраняем хэши для анализа плотностей
    std::ofstream hashFile("hash_values.csv");
    for (auto val : hashValues)
    {
        hashFile << val << "\n";
    }
    hashFile.close();

    // Информируем ползователя об окончании записи
    std::cout << "Hash values have been written for density analysis." << std::endl;

    return 0;
}
