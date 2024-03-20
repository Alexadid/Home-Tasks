#include <filesystem>
#include <iostream>
#include <stdexcept>



// Для некоторого улучшения читаемости кода
namespace fs = std::filesystem;

// Фукнция, возвращающая размер переданной сущности:
// 1. если это файл, то возвращает размер;
// 2. если это директория, то рекурсивно возвращает размер всех вложений;
// 3. если указан несуществующий  путь, то функция выбрасывает исключение.
uintmax_t getEntitySize(const fs::path& path)
{
    // Проверяем, существует ли путь, в принципе
    if (!fs::exists(path))
    {
        throw std::runtime_error("Path does not exist");
    }

    // Если это файл, то, УРА, возвращаем его размер
    if (fs::is_regular_file(path))
    {
        return fs::file_size(path);
    }

    // Если это директория, то итерируемся по её содержимомму при помощи directory_iterator
    else if (fs::is_directory(path))
    {
        uintmax_t totalSize = 0;
        fs::directory_iterator dir_iter(path), end;

        while (dir_iter != end)
        {
            fs::directory_entry entry = *dir_iter;

            // Если это файл, то добавляем его размер к totalSize
            if (entry.is_regular_file())
            {
                totalSize += entry.file_size();
            }

            // Если это директория, то итерируемся по её содержимому (не рекурсивно)
            else if (entry.is_directory())
            {
                fs::directory_iterator sub_dir_iter(entry.path());

                for (const auto& sub_entry : sub_dir_iter)
                {
                    if (sub_entry.is_regular_file())
                    {
                        totalSize += sub_entry.file_size();
                    }
                }
            }
            ++dir_iter;
        }

        return totalSize;
    } else
    {
        // Если путь не ведёт ни к обычному файлу, ни к директории (чтобы это ни было)
        throw std::runtime_error("Path is neither a file nor a directory");
    }
}

int main()
{
    // Работоспособность с файлом
    try
    {
        // На этот раз лезем в первое задание
        fs::path testPath = "../task1/main.cpp";
        std::cout << "Size: " << getEntitySize(testPath) << " bytes" << std::endl;
    }
    catch (const std::runtime_error& error)
    {
        std::cerr << error.what() << std::endl;
    }

    // Работоспособность с директорией
    try
    {
        fs::path testPath = "../task1/";
        std::cout << "Size: " << getEntitySize(testPath) << " bytes" << std::endl;
    }
    catch (const std::runtime_error& error)
    {
        std::cerr << error.what() << std::endl;
    }

    // Работоспособность (или скорее её отсутствие) в случае несуществующего пути
    try
    {
        fs::path testPath = "../task2077/";
        std::cout << "Size: " << getEntitySize(testPath) << " bytes" << std::endl;
    }
    catch (const std::runtime_error& error)
    {
        std::cerr << error.what() << std::endl;
    }

    return 0;
}
