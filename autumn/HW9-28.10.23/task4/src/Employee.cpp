#include "../include/Employee.hpp"

// Определение конструктора
Employee::Employee(std::string name, std::string surname, std::string title, double salary)
    : m_name(name), m_surname(surname), m_title(title), m_salary(salary) {}

// Определение геттеров
std::string Employee::name() const { return m_name; }

std::string Employee::surname() const { return m_surname; }

std::string Employee::title() const { return m_title; }

double Employee::salary() const { return m_salary; }
