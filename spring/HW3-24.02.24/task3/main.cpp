#include <random>
#include <string>
#include <algorithm>
#include <set>
#include <fstream>
#include <iostream>
#include "include/hash.hpp"



// Шаблонная функция для заполнения произвольного контейнера случайными строками заданной длины
// За счёт использования set гарантирует уникальность строк
template<typename Container>
void fillContainerWithUniqueRandomStrings(Container& container, size_t stringLength)
{
    // Символы для генерации строк
    const std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
    const size_t alphabetSize = alphabet.size();

    // Равномерно распределённый генератор целочисленных случайных чисел для выбора символов
    std::random_device randomDevice;
    std::mt19937 generator(randomDevice());
    std::uniform_int_distribution<> charDistribution(0, alphabetSize - 1);

    std::set<std::string> uniqueStrings;

    // Заполняем контейнер
    for (auto& element : container)
    {
        std::string randomString;
        do
        {
            randomString.clear();
            for (size_t i = 0; i < stringLength; ++i)
            {
                // Генерируем случайный символ из алфавита
                char randomChar = alphabet[charDistribution(generator)];
                randomString += randomChar;
            }
        }
        // Пытаемся вставить строку в set
        // Если строка повторяется, то повторяем процесс
        while (!uniqueStrings.insert(randomString).second);

        // Строка гарантирована уникальная
        element = randomString;
    }
}

int main()
{
    // Общее количество уникальных срок для генерации
    const size_t totalNumberOfStrings = 1000000;
    // Шаг количества строк для исследования коллизий
    const size_t stepSize = 10000;
    std::vector<std::string> strings(totalNumberOfStrings);

    // Генерируем уникальные случайные строки
    // Длина каждой строки 6, т.к. в таком случае мы можем исследовать до 3.08 * 10^8 строк
    fillContainerWithUniqueRandomStrings(strings, 6);

    // Скорее тестовый код, но пусть будет
    std::cout << "Strings have been generated." << std::endl;

    // Записывать данные будем в CSV файл
    std::ofstream outputFile("hash_collision_analysis.csv");
    outputFile << "NumberOfStrings,RSHash,JSHash,PJWHash,ELFHash,BKDRHash,SDBMHash,DJBHash,DEKHash,APHash\n";

    // Вектор, хранящий хэши для анализа плотностей
    std::vector<unsigned int> hashValues[9];

    for (size_t numStrings = stepSize; numStrings <= totalNumberOfStrings; numStrings += stepSize)
    {
        std::unordered_map<unsigned int, unsigned int> hashCounts[9];
        // Избавляемся от предыдущих хэшей
        for (int j = 0; j < 9; ++j)
        {
            hashValues[j].clear();
        }

        // Хэшируем каждую строку каждой из исследуемых хэш-функций и сохраняем хэш
        for (size_t i = 0; i < numStrings; ++i)
        {
            // Функции рассчитаны на C-строки, так что переводим в этот формат
            const auto& str = strings[i];
            unsigned int hashes[] = {
                RSHash(str.c_str(), str.length()),
                JSHash(str.c_str(), str.length()),
                PJWHash(str.c_str(), str.length()),
                ELFHash(str.c_str(), str.length()),
                BKDRHash(str.c_str(), str.length()),
                SDBMHash(str.c_str(), str.length()),
                DJBHash(str.c_str(), str.length()),
                DEKHash(str.c_str(), str.length()),
                APHash(str.c_str(), str.length()),
            };

            for (int j = 0; j < 9; ++j)
            {
                hashCounts[j][hashes[j]]++;
                hashValues[j].push_back(hashes[j]);
            }
        }

        // Подсчитываем коллизии для каждой хэш-функции на данном шаге
        outputFile << numStrings;
        for (int i = 0; i < 9; ++i)
        {
            unsigned int collisions = 0;
            for (const auto& pair : hashCounts[i])
            {
                if (pair.second > 1)
                {
                    collisions += pair.second - 1;
                }
            }
            outputFile << "," << collisions;
        }
        outputFile << "\n";
    }

    // Закрываем файл
    outputFile.close();
    // Информируем ползователя об окончании записи
    std::cout << "Collision data has been written to hash_collision_analysis.csv" << std::endl;

    // Сохраняем хэши для анализа плотностей
    for (int i = 0; i < 9; ++i)
    {
        std::ofstream hashFile("hash_values_" + std::to_string(i) + ".csv");
        for (auto val : hashValues[i])
        {
            hashFile << val << "\n";
        }
        hashFile.close();
    }

    // Информируем ползователя об окончании записи
    std::cout << "Hash values have been written for density analysis." << std::endl;

    return 0;
}
