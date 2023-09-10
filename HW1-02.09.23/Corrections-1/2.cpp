#include <iostream>
#include <string>

// Константы для перевода единиц
const double kgToGram = 1000.0;  // 1 kg = 1000 g
const double meterToCm = 100.0;  // 1 m = 100 cm
const double jouleToErg = 1e7;  // 1 J = 10^7 erg


// Функция для перевода физических единиц с поддержкой простейшей обрабокти ошибок
double translatePhysicsData(double value, const std::string fromUnit, const std::string toUnit)
{
    // Достаточно простая обработка ошибок
    // Считаем все отрицательные значения ошибочными
    if (value < 0.0)
    {
        std::cerr << "Error: Negative values are not supported." << std::endl;
        return -1.0;
    }

    // Структура для удобства хранения всей информации о переводе
    struct conversion
    {
        const char* from;
        const char* to;
        double multiplier;
    };

    // Массив для поддержки перевода единиц, включая необходимый коэффициент перевода
    const conversion availableConversions[] = {
        { "kg", "g", kgToGram },
        { "g", "kg", 1.0 / kgToGram },
        { "m", "cm", meterToCm },
        { "cm", "m", 1.0 / meterToCm },
        { "J", "erg", jouleToErg },
        { "erg", "J", 1.0 / jouleToErg }
    };

    double result;
    bool conversionFound = false; // флаг, отвечает за то, найден ли (выполнен, соответственно) соответствующий тип перевода

    for (const auto& conversion : availableConversions)
    {
        if (fromUnit == conversion.from && toUnit == conversion.to)
        {
            result = value * conversion.multiplier;
            conversionFound = true;
            break;
        }
    }

    if (!conversionFound)
    {
        // В случае какой-либо ошибки со стороны пользователя возвращаем -1, код ошибки
        std::cerr << "Unsupported unit conversion: " << fromUnit << " to " << toUnit << std::endl;
        return -1.0;
    }

    return result;
}


int main()
{
    std::string fromUnit, toUnit;
    double inputValue;

    // Считываем данные для перевода
    std::cout << "Enter the input value: ";
    std::cin >> inputValue;

    // Считываем из каких и в какие единицы нужно перевести значение
    // Ошибками займёмся в самой функции
    std::cout << "Enter the original unit (kg, m, J, etc.), you can enter either SI or CGS units: ";
    std::cin >> fromUnit;
    std::cout << "Enter the target unit (g, cm, erg, etc.), you can enter either SI or CGS units: ";
    std::cin >> toUnit;

    double result = translatePhysicsData(inputValue, fromUnit, toUnit);

    if (result != -1.0) {
        std::cout << inputValue << " " << fromUnit << " is equivalent to " << result << " " << toUnit << std::endl;
    }

    return 0;
}
