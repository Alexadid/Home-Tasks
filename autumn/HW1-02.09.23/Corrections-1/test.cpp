#include <iostream>
#include <iomanip>

int main()
{
    bool varTrue = true;
    bool varFalse = false;

    // Вывод bool переменных в чистом виде с исползованием setw и setfill с выравниваем справа
    std::cout << std::setw(20) << std::setfill('.') << std::right << varTrue << std::endl;
    std::cout << std::setw(20) << std::setfill('.') << std::right << varFalse << std::endl;
    // Вывод bool переменных в чистом виде с исползованием setw и setfill с выравниваем слева
    std::cout << std::setw(20) << std::setfill('.') << std::left << varTrue << std::endl;
    std::cout << std::setw(20) << std::setfill('.') << std::left << varFalse << std::endl;
    // Вывод bool переменных в виде boolalpha с исползованием setw и setfill с выравниваем справа
    std::cout << std::setw(20) << std::setfill('.') << std::boolalpha << std::right << varTrue << std::endl;
    std::cout << std::setw(20) << std::setfill('.') << std::boolalpha << std::right << varFalse << std::endl;
    // Вывод bool переменных в виде boolalpha с исползованием setw и setfill с выравниваем слева
    std::cout << std::setw(20) << std::setfill('.') << std::boolalpha << std::left << varTrue << std::endl;
    std::cout << std::setw(20) << std::setfill('.') << std::boolalpha << std::left << varFalse << std::endl;

    return 0;
}