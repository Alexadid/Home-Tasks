#include <iostream>

// Enumeration кодов ошибок
enum class ErrorCode
{
    Success,
    FileNotFound,
    InvalidInput,
    DivisionByZero
};

// Структура для хранения или результата или кода ошибки
struct Result
{
    union
    {
        int resultValue;
        ErrorCode errorCode;
    };
    bool isSuccess;

    // Не самая лучшая практики, но в данном конексте очень упрощает код
    // Конутруктор для успешного результата
    Result(int value) : resultValue(value), isSuccess(true) {}

    // Конструктор для ошибочного результата
    Result(ErrorCode code) : errorCode(code), isSuccess(false) {}
};

// Функция - пример использования обработки ошибок с Result
Result divide(int a, int b)
{
    if (b == 0) { return Result(ErrorCode::DivisionByZero); }
    return Result(a / b);
}



int main()
{
    // Пример ошибки: деление на ноль
    Result result = divide(10, 0);

    if (result.isSuccess)
    {
        std::cout << "Result: " << result.resultValue << std::endl;
    } else
    {
        std::cout << "Error: ";
        switch (result.errorCode)
        {
            case ErrorCode::FileNotFound:
                std::cout << "File not found." << std::endl;
                break;
            case ErrorCode::InvalidInput:
                std::cout << "Invalid input." << std::endl;
                break;
            case ErrorCode::DivisionByZero:
                std::cout << "Division by zero." << std::endl;
                break;
            default:
                std::cout << "Unknown error." << std::endl;
                break;
        }
    }

    return 0;
}
