#include <iostream>
#include <string>
#include <ctime>

// Определение структуры Spacecraft
struct Spacecraft
{
    std::string name;
    std::string mission;
    std::tm launchDate; // Используем стрктуру tm для зранения даты и времени
    bool isOperational;

    // Конструктор класса Spacecraft
    Spacecraft(const std::string& _name, const std::string& _mission,
               int year, int month, int day, bool _isOperational = true)
    {
        name = _name;
        mission = _mission;
        launchDate.tm_year = year - 1900; // tm_year - количество лет, прошедших с 1900 года
        launchDate.tm_mon = month - 1;    // (0 = Январь)
        launchDate.tm_mday = day;
        launchDate.tm_hour = 0;
        launchDate.tm_min = 0;
        launchDate.tm_sec = 0;
        launchDate.tm_isdst = -1; // Автоматическое определение летнего времени
        std::mktime(&launchDate); // Приводим время к корректному формату
        isOperational = _isOperational;
    }

    // Деструктор класс для очистки ресурсов
    ~Spacecraft()
    {
        // Здесь мог бы быть код для очистки, однако структура не представляет
        // из себя ничего особенного (освобождать ресурсы не требуется)...
        std::cout << "Spacecraft " << name << " is being destroyed." << std::endl;
    }

    // Функция-член для отображения информации о космическом аппарате
    void displayInfo()
    {
        std::cout << "Spacecraft Name: " << name << std::endl;
        std::cout << "Mission: " << mission << std::endl;
        std::cout << "Launch Date: " << launchDate.tm_year + 1900 << "-"
                  << launchDate.tm_mon + 1 << "-" << launchDate.tm_mday << std::endl;
        std::cout << "Status: " << (isOperational ? "Operational" : "Not Operational") << std::endl;
    }

    // Перегрузка оператора равенства, чтобы сравнить космические аппараты по имени
    // Не лучшая практика в современном C++, но показательна
    bool operator == (const Spacecraft& other)
    {
        return name == other.name;
    }
};

int main()
{
    // Создаём 2 объекта структуры Spacecraft
    Spacecraft venera("Venera 3", "Lander Probe", 1965, 11, 16, false);
    // здесь же можно отметить, что часть параметров может иметь значение по умолчанию 
    Spacecraft voyager("Voyager 1", "Interstellar Probe", 1977, 9, 5);

    // Отображаем информацию об аппаратах
    venera.displayInfo();
    voyager.displayInfo();

    // Проверяем одинаковые ли имена у 2 космических аппаратов
    // В нашем случае, очевидно, нет
    if (venera == voyager)
    {
        std::cout << "These spacecraft have the same name." << std::endl;
    } else
    {
        std::cout << "These spacecraft have different names." << std::endl;
    }

    return 0;
}
