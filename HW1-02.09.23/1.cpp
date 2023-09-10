#include <iostream>
#include <iomanip>
#include <string>

// Данная функция является попыткой обойти странности компиляции
// на arm64 версии g++ наблюдается непредвиденное поведение
// std::setfill при использовании с std::boolalpha
// bool значение всё равно расчитывается как '1' или '0'
std::string boolToString(bool value)
{
    return value ? "true" : "false";
}

// функция для более удобного вывода сообщения
void translateMessage(
    int messageLength,
    std::string productName,
    int productPrice, 
    int maxTemperature,
    bool cashBackAvailable)
{
    const std::string priceMessage = "Price:";
    const std::string cashBackAvailabilityMessage = "Has cash-back:";
    const std::string maxTemperatureMessage = "Max temperature:";

    // Сообщение о начале вывода
    std::cout << std::setw(messageLength) << std::setfill('*');
    std::cout << "Output" ;
    std::cout << std::setw(messageLength) << std::setfill('*') << '\n';   

    // Название продукта
    std::cout << productName << '\n';

    // Сообщение о цене, цена представлена в 16-ричной системе счисления
    std::cout << std::setw(messageLength - 8) << std::setfill('.') << std::left;
    // Почему 8? Ответ прост:
    // именно столько символов нужно, чтобы вместить integer в 16-ричной системе счисления
    std::cout << priceMessage;
    std::cout << std::hex << std::uppercase << std::setw(8) << std::setfill('0') << std::right;
    std::cout << productPrice << '\n';

    // Сообщение о наличии кэшбека
    std::cout << cashBackAvailabilityMessage;
    std::cout << std::setw(messageLength - cashBackAvailabilityMessage.size());
    std::cout << std::setfill('.') << std::boolalpha << std::right;
    std::cout << boolToString(cashBackAvailable) << '\n';

    // Сообщение о максимальной температуре хранения
    std::cout << maxTemperatureMessage;
    std::cout << std::setw(messageLength - maxTemperatureMessage.size());
    std::cout << std::setfill('.') << std::dec << std::showpos << maxTemperature << std::endl;
}

int main() {
    std::string productName;
    int productPrice, maxTemperature;
    bool cashBackAvailable;

    // Ввод данных
    std::cout << "Product's name: ";
    getline(std::cin, productName);
    std::cout << "Product's price: ";
    std::cin >> productPrice;
    std::cout << "Is cash-back available for this product? (true/false) ";
    // std::boolalpha используется для простоты ввода значения
    std::cin >> std::boolalpha >> cashBackAvailable;
    std::cout << "Maximum storing temperature: ";
    std::cin >> maxTemperature;

    // Здесь и в дальнейших задачах всё, что выводится в консоль пишется по анлгийски
    // во избежании проблем в случае отсутствия соответствующих пакетов...



    // Вывод переведённого сообщения
    // Длина каждого сообщения - 25 символов в соответствии с примером
    translateMessage(25, productName, productPrice, maxTemperature, cashBackAvailable);

    return 0;
}
