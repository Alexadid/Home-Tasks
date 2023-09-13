#include <iostream>
#include <string>
#include <vector>

// Функция для проверки того, является ли символ частью слова (буква, апостроф или дефис)
// Апостроф считаем частью слова и не отбрасываем
// Дефис, в отличие от тире, считаем частью слова
bool isWordCharacter(char c) { return (std::isalpha(c) || c == '\'' || c == '-'); }

// Функция, которая составляет из исходной строки вектор слов и знаков препинания
// На вход подаётся ссылка на строку для экономия памяти в случае слишком длинных строк
std::vector<std::string> extractWords(const std::string& sourceText)
{
    std::vector<std::string> result;
    std::string currentWord = "";

    for (char c : sourceText)
    {
        if (isWordCharacter(c))
        {
            currentWord += c;
        } else
        {
            if (!currentWord.empty())
            {
                result.push_back(currentWord);
                currentWord = "";
            }
            if (!std::isspace(c))
            {
                // Сохраняем знаки препинания в виде отдельных элементов вектора
                result.push_back(std::string(1, c));
            }
        }
    }

    // Граничный случай: последний символ исходной строки - буква, апостроф или дефис
    if (!currentWord.empty())
    {
        result.push_back(currentWord);
    }

    return result;
}

int main()
{
    std::string sourceText;
    std::cout << "Enter the source text: ";
    std::getline(std::cin, sourceText);

    std::vector<std::string> result = extractWords(sourceText);

    // Для проверки выводим вектор по ячейкам, каждая с новой строки
    std::cout << "This is the result of text formating:\n";
    for (const std::string& element : result)
    {
        std::cout << element << std::endl;
    }

    return 0;
}
