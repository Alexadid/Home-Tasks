#include <iostream>
#include <bitset>
#include <string>

const unsigned int bookIdBitLimit = 0x3FFF;
const unsigned int yearBitLimit = 0xFFF;
const unsigned int monthBitLimit = 0xF;
const unsigned int dayBitLimit = 0x1F;
const unsigned int numSectionsBitLimit = 0xF;
const unsigned int numChaptersBitLimit = 0x7F;
const unsigned int numPagesBitLimit = 0x7FF;

// Определение сткруктуры для хранения информации о книгах с использованием битовых полей
struct BookInfo
{
    unsigned int bookId : 14;      // 0-10000, требуется 14 бит
    bool status;                   // находится в библиотеке или на руках у читателя
    unsigned int year : 12;        // Год (1990-4095), требуется 12 бит
    unsigned int month : 4;        // Месяц (1-12), требуется 4 бита
    unsigned int day : 5;          // День (1-31), требуется 5 бит
    unsigned int numSections : 4;  // 0-10, требуется 4 бита
    unsigned int numChapters : 7;  // 0-100, требуется 7 бит
    // Исправил количество бит, выделенное для количества страниц
    // Для хранения числа не превышающего 2000 хватает 11 бит (2047_10)
    unsigned int numPages : 11;    // 0-2000, треубется 11 бит
};

void InputBookInfo(BookInfo&);
bool IsDateValid(unsigned int, unsigned int, unsigned int);
void OutputBookInfo(const BookInfo&);



int main()
{
    BookInfo book;

    // Вводим информацию о книге
    InputBookInfo(book);

    // Проверяем кооректность введённой даты
    if (!IsDateValid(book.year, book.month, book.day))
    {
        std::cout << "Invalid date entered." << std::endl;
        return 1; // Выходим из программы с кодом ошибки 1
    }

    // Выводим информацию о книге
    OutputBookInfo(book);

    return 0;
}

// Функция для ввода информации о книге
void InputBookInfo(BookInfo& book)
{
    unsigned int tempValue;
    bool tempValueBool;

    std::cout << "Please enter book information:" << std::endl;
    std::cout << "Book ID (0-10000): ";
    std::cin >> tempValue;
    // Здесь и далее удостоверяемся, что количество бит будет корректным
    book.bookId = tempValue & bookIdBitLimit;

    std::cout << "Status (0 - In Library, 1 - In Hands of Reader): ";
    std::cin >> tempValueBool;
    book.status = tempValueBool;

    std::cout << "Receipt Date (YYYY-MM-DD)." << std::endl;
    std::cout << "Year (1990-4095): ";
    std::cin >> tempValue;
    book.year = tempValue & yearBitLimit;

    std::cout << "Month (1-12): ";
    std::cin >> tempValue;
    book.month = tempValue & monthBitLimit;

    std::cout << "Day (1-31): ";
    std::cin >> tempValue;
    book.day = tempValue & dayBitLimit;

    std::cout << "Number of Sections (0-10): ";
    std::cin >> tempValue;
    book.numSections = tempValue & numSectionsBitLimit;

    std::cout << "Number of Chapters (0-100): ";
    std::cin >> tempValue;
    book.numChapters = tempValue & numChaptersBitLimit;

    std::cout << "Number of Pages (0-2000): ";
    std::cin >> tempValue;
    book.numPages = tempValue & numPagesBitLimit;
}

// Функция для проверки корректности введённой даты (по отношению к нашей библиотеке в том числе)
bool IsDateValid(unsigned int year, unsigned int month, unsigned int day)
{
    // Библиотека относительно новая, однако готовы работать долго, поэтому и ограничение до 4095 года 
    if (year >= 1990 && year <= 4095 &&
        month >= 1 && month <= 12 &&
        day >= 1 && day <= 31)
    {
        return true;
    }
    return false;
}

// Функция для вывода информации о книге
void OutputBookInfo(const BookInfo& book)
{
    std::cout << "\nBook Information:" << std::endl;
    std::cout << "Book ID: " << book.bookId << std::endl;
    std::cout << "Status: " << book.status << std::endl;
    std::cout << "Receipt Date: " << book.year << "-" << book.month << "-" << book.day << std::endl;
    std::cout << "Number of Sections: " << book.numSections << std::endl;
    std::cout << "Number of Chapters: " << book.numChapters << std::endl;
    std::cout << "Number of Pages: " << book.numPages << std::endl;
}