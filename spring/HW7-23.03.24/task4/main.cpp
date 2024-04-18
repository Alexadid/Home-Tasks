#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <filesystem>
#include <future>
#include <thread>
#include <functional>

namespace fs = std::filesystem;



// Функция для подсчета строк в одном файле
void count_lines_in_file(const std::string& file_path, std::promise<int>&& promise)
{
    try
    {
        std::ifstream file(file_path);
        if (!file.is_open())
        {
            throw std::runtime_error("Could not open the file: " + file_path);
        }

        int count = 0;
        std::string line;

        // Этот цикл считывает строки, но также проверяет наличие последней пустой строки
        while (true)
        {
            std::streampos previous_position = file.tellg();
            if (!getline(file, line))
            {
                if (file.eof() && previous_position != -1)
                {
                    // Проверяем, заканчивается ли файл новой строкой
                    file.seekg(-1, std::ios_base::end);
                    if (file.get() == '\n')
                    {
                        count++;
                    }
                }
                break;
            }
            count++;
        }
        file.close();

        // Установливаем результат для этого файла
        promise.set_value(count);
    } catch(...)
    {
        // Передаём любое исключение в основной поток
        promise.set_exception(std::current_exception());
    }
}

// Функция для поиска всех cpp-файлов и асинхронного подсчёта их строк
int count_lines_in_cpp_files(const std::string& directory)
{
    std::vector<std::future<int>> futures;
    for (const auto& entry : fs::directory_iterator(directory))
    {
        if (entry.is_regular_file() && entry.path().extension() == ".cpp")
        {
            std::promise<int> promise;
            futures.push_back(promise.get_future());
            std::thread(count_lines_in_file, entry.path().string(), std::move(promise)).detach();
        }
    }

    int total_lines = 0;
    for (auto& fut : futures)
    {
        // Перебрасываем любые исключения из потока
        total_lines += fut.get();
    }
    return total_lines;
}

int main()
{
    // Демонстрационный код: файлы собрал из этого задания
    const std::string path = "CPP_folder";

    try
    {
        int total_lines = count_lines_in_cpp_files(path);
        std::cout << "Total lines in .cpp files: " << total_lines << std::endl;
    } catch (const std::exception& error)
    {
        std::cerr << "Error: " << error.what() << std::endl;
    }

    return 0;
}
