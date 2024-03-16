#include <iostream>
#include <sstream>
#include <iomanip>



// Манипулятор вывода, который восстанавливает поток, находящийся в состоянии fail
std::ostream& clearfail(std::ostream& stream)
{
    // Очищаем флаги состояния ошибки
    stream.clear();
    return stream;
}

int main()
{
    std::stringstream stringStream;

    // Переводим поток в состояние fail
    stringStream.setstate(std::ios::failbit);

    std::cout << "Before using the manipulator, good() = " << std::boolalpha << stringStream.good() << std::endl;

    // Испольлзуем манипулятор для возвращение его в работоспособное состояние
    stringStream << clearfail;

    std::cout << "After using the manipulator, good() = " << std::boolalpha << stringStream.good() << std::endl;

    // Демонстрируем, что поток теперь готов для работы
    stringStream << "This is a test after clearing the fail state.";
    std::string output;
    // Читаем из потока для, чтобы продемонстрировать, что всё теперь работает
    stringStream >> output;

    // Смешно, что я потратил так много времени на эту строку...
    // Я забыл, что поток поток читает ввод до ПРОБЕЛА, а не до \name
    // Даже стыдно как-то
    std::cout << "Stream content: " << output << std::endl;

    // Если бы хотелось отправить всю строку, нужно было бы сделать вот так.
    /*
    // Демонстрируем, что поток теперь готов для работы
    // Добавляем \n, чтобы обозначить конец ввода для getline
    stringStream << "This is a test after clearing the fail state.\n";

    std::string output;
    // Используем getline для чтения всй строки
    std::getline(stringStream, output);
    std::cout << "Stream content: " << output << std::endl;
    */

    return 0;
}
