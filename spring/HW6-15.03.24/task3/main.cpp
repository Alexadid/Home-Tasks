#include <iostream>
#include <vector>
#include <fstream>
#include <filesystem>
#include "include/json.hpp"



// Структура PersonInfo для хранения данных о человеке
struct PersonInfo
{
    int age;
    double height;
    bool isEmployed;
    std::string name;
    std::vector<PersonInfo> acquaintances;

    // Сериализируем структуру в формат JSON
    friend std::ostream& operator<<(std::ostream& os, const PersonInfo& info);
};

// Перегрузка оператора << для сериализации в JSON
std::ostream& operator<<(std::ostream& os, const PersonInfo& info)
{
    // Базовая структура JSON без отступов (пока не решил, как их сделать красиво)
    os << "{\n";
    os << "\"age\": " << info.age << ",\n";
    os << "\"height\": " << info.height << ",\n";
    os << "\"isEmployed\": " << (info.isEmployed ? "true" : "false") << ",\n";
    os << "\"name\": \"" << info.name << "\",\n";
    os << "\"acquaintances\": [";
    for (size_t i = 0; i < info.acquaintances.size(); ++i)
    {
        if (i > 0) os << ",";
        os << "\n" << info.acquaintances[i];
    }

    if (!info.acquaintances.empty()) os << std::endl;
    os << "]\n";
    os << "}";
    return os;
}

// Функция для создания директории для хранения полученных JSON'ов
void createDirectory(const std::filesystem::path& dirPath)
{
    std::filesystem::create_directories(dirPath);
}

// Сериализируем объект PersonInfo и созраняем его в файл
bool serializeAndSavePersonInfo(const PersonInfo& person, const std::filesystem::path& filePath)
{
    std::ofstream file(filePath);
    if (file.is_open())
    {
        file << person;
        file.close();
        return true;
    } else
    {
        std::cerr << "Failed to open file for writing." << std::endl;
        return false;
    }
}

// Десериализируем PersonInfo из JSON файла
bool deserializePersonInfo(const std::filesystem::path& filePath, nlohmann::json& jsonData)
{
    std::ifstream fileInput(filePath);
    if (fileInput.is_open())
    {
        fileInput >> jsonData;
        fileInput.close();
        return true;
    } else
    {
        std::cerr << "Failed to open file for reading." << std::endl;
        return false;
    }
}

int main()
{
    // Путь для хранения информации
    std::filesystem::path dirPath = "./info";
    createDirectory(dirPath);

    // Создаём 3 людей для демонстрации всех возможностей
    // Решил сразу избавиться от магичсеких чисел, хотя место это занимает порядком...
    int ageOfPerson1 = 30;
    double heightOfPerson1 = 170.0;
    bool isEmployedPerson1 = false;
    std::string nameOfPerson1 = "Alice";
    PersonInfo acquaintance1 = {ageOfPerson1, heightOfPerson1, isEmployedPerson1, nameOfPerson1, {}};

    int ageOfPerson2 = 28;
    double heightOfPerson2 = 199.9;
    bool isEmployedPerson2 = true;
    std::string nameOfPerson2 = "Borya";
    PersonInfo acquaintance2 = {ageOfPerson2, heightOfPerson2, isEmployedPerson2, nameOfPerson2, {}};
    
    int ageOfPerson3 = 999;
    double heightOfPerson3 = 169.8;
    bool isEmployedPerson3 = true;
    std::string nameOfPerson3 = "John Doe";
    PersonInfo person = {ageOfPerson3, heightOfPerson3, isEmployedPerson3, nameOfPerson3, {acquaintance1, acquaintance2}};

    // Пытаемся сериализировать и сохранить гланый объект PersonInfo
    if (!serializeAndSavePersonInfo(person, dirPath / "person.json"))
    {
        // Выходим, если запись не удаётся
        return 1;
    }

    // Пытаемся десериализировать и сохранить гланый объект PersonInfo
    nlohmann::json jsonData;
    if (!deserializePersonInfo(dirPath / "person.json", jsonData))
    {
        // Выходим, если чтение не удаётся
        return 1;
    }

    // Выводим данные в консоль, наконец-то...
    std::cout << jsonData.dump(4) << std::endl;

    return 0;
}
