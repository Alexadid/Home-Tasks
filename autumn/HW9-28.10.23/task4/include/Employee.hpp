#ifndef EMPLOYEE_HPP
#define EMPLOYEE_HPP

#include <string>

class Employee
{
private:
    std::string m_name;
    std::string m_surname;
    std::string m_title;
    double m_salary;

public:
    // Конструктор
    Employee(std::string name, std::string surname, std::string title, double salary);

    // Геттеры
    std::string name() const;
    std::string surname() const;
    std::string title() const;
    double salary() const;
};

#endif
