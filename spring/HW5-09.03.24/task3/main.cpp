#include <iostream>
#include <fstream>
#include <string>

int main()
{
    // Обычные дела...
    // Открываем файл, проверяем работает ли всё
    std::string filePath = "sampleLines.txt";
    std::ifstream file(filePath);
    if (!file.is_open())
    {
        std::cerr << "Failed to open file: " << filePath << std::endl;
        return 1;
    }

    int lineNumber;
    std::cout << "Enter the line number to read: ";
    std::cin >> lineNumber;

    // Предполагаем, что каждая строка фиксированного размера
    // При этом считаем только символы, которые видит пользователь,
    // так что '\n' придётся учесть отдельно
    const int lineLength = 32;
    // Расчитываем смещение
    // Вычитаем 1 из lineNumber, т.к. всё начинается с 0
    // Добавляем 1 к lineLength ввиду вышеупомянутой ситуации
    int offset = (lineNumber - 1) * (lineLength + 1);

    // Устанавливаем указатель на чтение файла
    file.seekg(offset, std::ios::beg);

    // Опрашиваем пользователя...
    std::string line;
    if (std::getline(file, line))
    {
        std::cout << "Line " << lineNumber << ": " << line << std::endl;
    } else
    {
        std::cerr << "Failed to read the line. It might not exist." << std::endl;
    }

    // Наконец-то закрываем файл
    file.close();
    return 0;
}
