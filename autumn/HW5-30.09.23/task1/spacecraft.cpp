#include "spacecraft.hpp"

// Опредение конструктора класса
Spacecraft::Spacecraft(const std::string& _name, const std::string& _mission,
                       int year, int month, int day, bool _isOperational)
    : m_name(_name), m_mission(_mission), m_isOperational(_isOperational)
{
    m_launchDate.tm_year = year - 1900; // tm_year - количество лет, прошедших с 1900 года
    m_launchDate.tm_mon = month - 1; // (0 = Январь)
    m_launchDate.tm_mday = day;
    m_launchDate.tm_hour = 0;
    m_launchDate.tm_min = 0;
    m_launchDate.tm_sec = 0;
    m_launchDate.tm_isdst = -1; // Автоматическое определение летнего времени
    std::mktime(&m_launchDate); // Убрал метод normalizeTime, перенёс в конструктор
}

// Определение деструктора
Spacecraft::~Spacecraft()
{
    // Здесь мог бы быть код для очистки, однако класс не представляет
    // из себя ничего особенного (освобождать ресурсы как-то особенно не требуется)...
    std::cout << "Spacecraft " << m_name << " is being destroyed." << std::endl;
}

// Функция-член для отображения информации об аппарате
void Spacecraft::displayInfo() const
{
    std::cout << "Spacecraft Name: " << m_name << std::endl;
    std::cout << "Mission: " << m_mission << std::endl;
    std::cout << "Launch Date: " << m_launchDate.tm_year + 1900 << "-"
              << m_launchDate.tm_mon + 1 << "-" << m_launchDate.tm_mday << std::endl;
    std::cout << "Status: " << (m_isOperational ? "Operational" : "Not Operational") << "\n" << std::endl;
}

// Перегруженный оператор равенства для сравнения аппаратов по их именам
bool Spacecraft::operator==(const Spacecraft& other) const
{
    return m_name == other.m_name;
}
