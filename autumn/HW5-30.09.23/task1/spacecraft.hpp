#ifndef SPACECRAFT_HPP
#define SPACECRAFT_HPP

#include <iostream>
#include <string>
#include <ctime>

// Объявление класса Spacecraft
class Spacecraft
{
public:
    // Контруктор класса
    Spacecraft(const std::string& _name, const std::string& _mission,
               int year, int month, int day, bool _isOperational = true);
    
    // Деструктор класса
    ~Spacecraft();

    // Функция-член для отображения информации об аппарате
    void displayInfo() const;

    // Перегруженный оператор равенства для сравнения аппаратов по их именам
    bool operator==(const Spacecraft& other) const;

private:
    // Приватные данные
    std::string name;
    std::string mission;
    std::tm launchDate;
    bool isOperational;

    // Приватная функция для нормализации времени к формату tm
    void normalizeTime();
};

#endif // SPACECRAFT_HPP
