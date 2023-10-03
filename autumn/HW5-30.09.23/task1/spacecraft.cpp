#include "spacecraft.hpp"

// Опредение конструктора класса
Spacecraft::Spacecraft(const std::string& _name, const std::string& _mission,
                       int year, int month, int day, bool _isOperational)
    : name(_name), mission(_mission), isOperational(_isOperational)
{
    launchDate.tm_year = year - 1900; // tm_year - количество лет, прошедших с 1900 года
    launchDate.tm_mon = month - 1; // (0 = Январь)
    launchDate.tm_mday = day;
    launchDate.tm_hour = 0;
    launchDate.tm_min = 0;
    launchDate.tm_sec = 0;
    launchDate.tm_isdst = -1; // Автоматическое определение летнего времени
    normalizeTime();
}

// Определение деструктора
Spacecraft::~Spacecraft()
{
    // Здесь мог бы быть код для очистки, однако класс не представляет
    // из себя ничего особенного (освобождать ресурсы как-то особенно не требуется)...
    std::cout << "Spacecraft " << name << " is being destroyed." << std::endl;
}

// Функция-член для отображения информации об аппарате
void Spacecraft::displayInfo() const
{
    std::cout << "Spacecraft Name: " << name << std::endl;
    std::cout << "Mission: " << mission << std::endl;
    std::cout << "Launch Date: " << launchDate.tm_year + 1900 << "-"
              << launchDate.tm_mon + 1 << "-" << launchDate.tm_mday << std::endl;
    std::cout << "Status: " << (isOperational ? "Operational" : "Not Operational") << std::endl;
}

// Приватная функция для нормализации времени к формату tm
void Spacecraft::normalizeTime()
{
    std::mktime(&launchDate);
}

// Перегруженный оператор равенства для сравнения аппаратов по их именам
bool Spacecraft::operator==(const Spacecraft& other) const
{
    return name == other.name;
}
