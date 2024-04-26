#include <iostream>
#include <filesystem>
#include <chrono>
#include <iomanip>

// Improved readability by using a namespace alias
namespace fs = std::filesystem;

int main()
{
    // Чтобы не вызвать проблем с доступом к несуществующим папкам,
    // я использую папку в этом же домашнем задании.
    // Вы же, Умар, можете менять его, как угодно - обработка ошибок есть
    fs::path directoryPath("../task2");

    // Проверяем, существует ли указанный путь и является ли он директорией
    if (!fs::exists(directoryPath) || !fs::is_directory(directoryPath))
    {
        std::cerr << "Error: The specified path is not a valid directory." << std::endl;
        return 1;
    }

    for (const auto& entry : fs::directory_iterator(directoryPath))
    {
        auto fileName = entry.path().filename();

        // Определите тип обхекта файловой системы
        std::string fileType;
        if (entry.is_directory())
        {
            fileType = "Directory";
        } else if (entry.is_regular_file())
        {
            fileType = "File";
        } else if (entry.is_symlink())
        {
            fileType = "Symbolic Link";
        } else if (entry.is_block_file())
        {
            fileType = "Block Device";
        } else if (entry.is_character_file())
        {
            fileType = "Character Device";
        } else if (entry.is_fifo())
        {
            fileType = "FIFO (Named Pipe)";
        } else if (entry.is_socket())
        {
            fileType = "Socket";
        } else
        {
            fileType = "Unknown";
        }

        // Получаем время последнего изменения
        auto lastWriteTime = fs::last_write_time(entry);
        auto systemTimePoint = std::chrono::time_point_cast<std::chrono::system_clock::duration>(
            lastWriteTime - fs::file_time_type::clock::now() + std::chrono::system_clock::now());

        // Переводим в системное время
        auto convertedTime = std::chrono::system_clock::to_time_t(systemTimePoint);

        // Выводим полученную информацию в консоль
        std::cout << "Name: " << fileName << ";\n" << "Type: " << fileType << ";\n"
                << "Last Modified: " << std::put_time(std::localtime(&convertedTime), "%F %T") << std::endl << std::endl;
    }
    return 0;
}
