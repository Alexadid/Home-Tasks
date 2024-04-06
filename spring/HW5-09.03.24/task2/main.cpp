#include <iostream>
#include <fstream>
#include <string>



// Enum class, редставляющий различные состояния при разборе исходного кода
enum class ParseState
{
    // Нормальный режим, не в комментарии и не в строковом литерале
    Normal,
    // Внутри строкового литерала ("")
    StringLiteral,
    // Внутри однострочного комментария (//)
    SingleLineComment,
    // Внутри многострочного комментария (/**/)
    MultiLineComment
};


// Функция для удаления ненужных комментариев из заданного файла исходного кода
// Сохраняет специальные комментарии, в том числе:
// - однострочные комметарии, отмеченные '@';
// - многострочные комментарии, отмеченные '$';
void removeComments(const std::string& inputFile)
{
    // Поток ввода для чтения исходного кода
    std::ifstream file(inputFile);

    if (!file.is_open())
    {
        std::cerr << "Could not open the file: " << inputFile << std::endl;
        // Выходим, если файл не может быть открыт
        return;
    }

    // Создаём имя для выходного файла путём добавления "-noComments"
    std::string outputFile = inputFile.substr(0, inputFile.find_last_of('.')) +
                                            "-noComments" +
                                            inputFile.substr(inputFile.find_last_of('.'));
    // Поток вывода для записи обработанного кода
    std::ofstream outFile(outputFile);

    if (!outFile.is_open())
    {
        std::cerr << "Could not create the output file: " << outputFile << std::endl;
        // Выходим, если выходной файл не может быть создан
        return;
    }

    // По умолчанию начинаем в нормальном состоянии
    ParseState state = ParseState::Normal;
    // Строка для сохранения обработанного вывода
    std::string result;

    // Счтываем входной файл посимвольно
    while (!file.eof())
    {
        char currentChar = file.get();
        // Выходим из цикла, если файла закончился
        if (file.eof()) break;

        // Автомат-состояний обрабатывает код в зависимости от состояния
        switch (state)
        {
            // Опять же начинаем в нормальном состоянии
            case ParseState::Normal:
                // Начало строкового литерала
                // Стоит отметить, что вне зависимости от того, что написано в литерале,
                // мы считаем это символами, а не комментариями...
                if (currentChar == '"')
                {
                    state = ParseState::StringLiteral;
                    result += currentChar;
                } else if (currentChar == '/')
                {
                    // Начало однострочного комментария
                    if (file.peek() == '/')
                    {
                        // Двигаемся за следующий '/'
                        file.get();
                        // А вот и особый комментарий! Его нужно оставить
                        if (file.peek() == '@')
                        {
                            // Двигаемся за '@'
                            file.get();
                            result += "//@";
                        } else
                        {
                            state = ParseState::SingleLineComment;
                        }
                    // Начало многострочного комментария
                    } else if (file.peek() == '*')
                    {
                        // Двигаемся за следующий '*'
                        file.get();
                        // Особый многтсрочный комментарий, который нужно оставить
                        if (file.peek() == '$')
                        {
                            // Двигаемся за '$'
                            file.get();
                            result += "/*$";
                        } else
                        {
                            state = ParseState::MultiLineComment;
                        }
                    } else
                    {
                        // Обычный символ кода.
                        result += currentChar;
                    }
                } else
                {
                    // Обычный символ кода.
                    result += currentChar;
                }
                break;

            // Находимся в строковом литерале
            case ParseState::StringLiteral:
                result += currentChar;
                // Конец строкового литерала, с учетом экранирующих символов
                if (currentChar == '"' && result[result.length() - 2] != '\\')
                {
                    state = ParseState::Normal;
                }
                break;

            // Находимся в однострочном комментарии
            case ParseState::SingleLineComment:
                if (currentChar == '\n')
                {
                    // Конец однострочного комментария
                    state = ParseState::Normal;
                    // Добавляем символ перевода строки в вывод
                    result += currentChar;
                }
                break;

            // Находимся в многострочном комментарии
            // Находимся в многострочном комментарии
            case ParseState::MultiLineComment:
                // Проверяем, не закончился ли многострочный комментарий
                if (currentChar == '*' && file.peek() == '/')
                {
                    // Пропускаем следующий символ '/', выходя из комментария
                    file.get(); // Эта строка потребляет '/' из потока
                    state = ParseState::Normal;
                }
                break;
            
        }
    }

    // Закрываем входной файл
    file.close();
    // Записываем обработанный код в выходной файл
    outFile << result;
    // Закрываем выходной файл
    outFile.close();
    // Уведомляем пользователя о том, что обработка кода завершена
    std::cout << "Processed file has been saved to: " << outputFile << std::endl;
}

int main()
{
    // Я решил просто вписать название файла для обработки в код
    // Хотя можно было указываеть его после компиляции при запуске, как флаг
    std::string inputFile = "fileToCorrect.cpp";

    // Вызываем функцию для удаления ненужных комментариев
    removeComments(inputFile);
    
    return 0;
}
