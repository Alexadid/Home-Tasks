#include <iostream>
#include <vector>
#include <fstream>
#include <filesystem>
#include "include/json.hpp"



// Структура PersonInfo для хранения данных о человеке
struct PersonInfo
{
    int age;
    float height;
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
    PersonInfo acquaintance1 = {30, 6.1f, false, "Alice Smith", {}};
    PersonInfo acquaintance2 = {28, 5.5f, true, "Bob Johnson", {}};
    PersonInfo person = {25, 5.9f, true, "John Doe", {acquaintance1, acquaintance2}};

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
