#ifndef SPACECRAFT_HPP
#define SPACECRAFT_HPP

#include <iostream>
#include <string>
#include <ctime>

// Объявление класса Spacecraft
class Spacecraft
{
public:
    // Конструктор по умолчанию
    Spacecraft() = default;

    // Контруктор класса
    Spacecraft(const std::string& _name, const std::string& _mission,
               int year, int month, int day, bool _isOperational = true);

    // Функция-член для отображения информации об аппарате
    void displayInfo() const;

    // Перегруженный оператор равенства для сравнения аппаратов по их именам
    bool operator==(const Spacecraft& other) const;

    // Деструктор класса
    ~Spacecraft();

private:
    // Приватные данные
    std::string m_name{"Name"};
    std::string m_mission{"Mission Name"};
    std::tm m_launchDate{};
    bool m_isOperational{true};

};

#endif // SPACECRAFT_HPP
