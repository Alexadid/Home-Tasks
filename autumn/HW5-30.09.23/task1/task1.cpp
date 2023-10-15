#include "spacecraft.hpp"

int main()
{
    // Создаём 2 объекта класса Spacecraft
    Spacecraft venera("Venera 3", "Lander Probe", 1965, 11, 16, false);
    Spacecraft voyager("Voyager 1", "Interstellar Probe", 1977, 9, 5);

    // Отображаем информацию об аппаратах
    venera.displayInfo();
    voyager.displayInfo();

    // Проверяем одинаковые ли имена у 2 космических аппаратов
    // В нашем случае, очевидно, нет
    if (venera == voyager)
    {
        std::cout << "These spacecrafts have the same name." << std::endl;
    }
    else
    {
        std::cout << "These spacecrafts have different names." << std::endl;
    }

    // Дестомнтрация работы конструктора по умолчанию...
    auto shuttle = Spacecraft();
    shuttle.displayInfo();

    return 0;
}
