#include <iostream>

// Определение enum для месяцев
enum class Month
{
    January, February, March, April, May, June,
    July, August, September, October, November, December
};

int getNumberOfDaysInMonth(Month);

int main()
{
    int monthNumber;
    std::cout << "Enter the number of the month (1-12): ";
    std::cin >> monthNumber;

    // Конвертируем ввод пользователя в enum месяца
    Month inputMonth = static_cast<Month>(monthNumber - 1);

    int numberOfDays = getNumberOfDaysInMonth(inputMonth);

    if (numberOfDays != -1)
    {
        std::cout << "There are " << numberOfDays << " days in the specified month." << std::endl;
    } else
    {
        std::cout << "Invalid month input." << std::endl;
    }

    return 0;
}

// Функция для получения количества дней в месяце
int getNumberOfDaysInMonth(Month month)
{
    switch (month)
    {
        case Month::January:
        case Month::March:
        case Month::May:
        case Month::July:
        case Month::August:
        case Month::October:
        case Month::December:
            return 31; // В этих месяцах 31 день
        case Month::April:
        case Month::June:
        case Month::September:
        case Month::November:
            return 30; // В этих месяцах 30 дней
        case Month::February:
            return 28; // В феврале 28 дней (игнорируем високосный год)
        default:
            return -1; // Некорректный месяц
    }
}