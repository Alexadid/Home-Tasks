#include <iostream>
#include <string>
#include <ctime>

struct Spacecraft
{
    std::string name;
    std::string mission;
    std::tm launchDate{};
    bool isOperational{true};  // Значение по умолчанию

    // Конструктор по умолчанию
    Spacecraft() = default;

    // Параметризованный конструктор, использующий список инициализации
    Spacecraft(const std::string& _name, const std::string& _mission, int year, int month, int day, bool _isOperational = true)
        : name(_name), mission(_mission), isOperational(_isOperational)
    {
        launchDate.tm_year = year - 1900;
        launchDate.tm_mon = month - 1;
        launchDate.tm_mday = day;
        std::mktime(&launchDate);
    }

    // Деструктор (без изменений)
    ~Spacecraft()
    {
        std::cout << "Spacecraft " << name << " is being destroyed." << std::endl;
    }

    // Перегрузка оператора равенства, чтобы сравнить космические аппараты по имени (без изменений)
    void displayInfo()
    {
        std::cout << "Spacecraft Name: " << name << std::endl;
        std::cout << "Mission: " << mission << std::endl;
        std::cout << "Launch Date: " << launchDate.tm_year + 1900 << "-"
                  << launchDate.tm_mon + 1 << "-" << launchDate.tm_mday << std::endl;
        std::cout << "Status: " << (isOperational ? "Operational" : "Not Operational") << std::endl;
    }

    // Перегрузка оператора равенства, чтобы сравнить космические аппараты по имени (без изменений)
    bool operator == (const Spacecraft& other)
    {
        return name == other.name;
    }
};

int main()
{
    // Создаём 2 объекта структуры Spacecraft
    Spacecraft venera{"Venera 3", "Lander Probe", 1965, 11, 16, false};
    Spacecraft voyager{"Voyager 1", "Interstellar Probe", 1977, 9, 5};

    // Отображаем информацию об аппаратах
    venera.displayInfo();
    voyager.displayInfo();

    // Проверяем одинаковые ли имена у 2 космических аппаратов
    // В нашем случае, очевидно, нет
    if (venera == voyager)
    {
        std::cout << "These spacecraft have the same name." << std::endl;
    }
    else
    {
        std::cout << "These spacecraft have different names." << std::endl;
    }

    return 0;
}
