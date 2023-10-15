#include <iostream>
#include <string>
#include <ctime>

struct Spacecraft
{
    std::string m_name{"Name"};
    std::string m_mission{"Mission Name"};
    std::tm m_launchDate{};
    bool m_isOperational{true};  // Значение по умолчанию

    // Конструктор по умолчанию
    Spacecraft() = default;

    // Параметризованный конструктор, использующий список инициализации
    Spacecraft(const std::string& name, const std::string& mission, int year, int month, int day, bool isOperational = true)
        : m_name(name), m_mission(mission), m_isOperational(isOperational)
    {
        m_launchDate.tm_year = year - 1900;
        m_launchDate.tm_mon = month - 1;
        m_launchDate.tm_mday = day;
        std::mktime(&m_launchDate);
    }

    // Деструктор (без изменений)
    ~Spacecraft()
    {
        std::cout << "Spacecraft " << m_name << " is being destroyed." << std::endl;
    }

    // Перегрузка оператора равенства, чтобы сравнить космические аппараты по имени (без изменений)
    void displayInfo()
    {
        std::cout << "Spacecraft Name: " << m_name << std::endl;
        std::cout << "Mission: " << m_mission << std::endl;
        std::cout << "Launch Date: " << m_launchDate.tm_year + 1900 << "-"
                  << m_launchDate.tm_mon + 1 << "-" << m_launchDate.tm_mday << std::endl;
        std::cout << "Status: " << (m_isOperational ? "Operational" : "Not Operational") << "\n" << std::endl;
    }

    // Перегрузка оператора равенства, чтобы сравнить космические аппараты по имени (без изменений)
    bool operator == (const Spacecraft& other)
    {
        return m_name == other.m_name;
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

    // Демонстрация работы конструктора по умолчанию
    auto shuttle = Spacecraft();
    shuttle.displayInfo();

    return 0;
}
