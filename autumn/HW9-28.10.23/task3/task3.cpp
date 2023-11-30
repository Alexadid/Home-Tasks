#include "include/dataCollection.hpp"

int main()
{
    try
    {
        // Создаём объект DataCollection с размером массива, превышающим лимит
        int sizeOfArray1 = 150;
        int sizeOfArray2 = 50;
        std::string nameOfDataCollection = "ExceedingSize";
        DataCollection collectionWithExceedingSize(sizeOfArray1, sizeOfArray2, nameOfDataCollection);

        // Соответственно, эта строка не будет достигнута, т.к. конструктор выбросит исключение
        std::cout << collectionWithExceedingSize << std::endl;

        // Дальше в том числе демонстрируется стратегия от частного к общему
    } catch (const NegativeArraySizeException& e)
    {
        // Вначале предполагаем наиболее частный случай в виде попытки создать массив отрицательной длины
        std::cerr << "Caught NegativeArraySizeException: " << e.what() << std::endl;
    } catch (const SizeLimitExceededException& e)
    {
        // Затем предпоалагаем более общий случай в виде превышение лимита на длину массива
        std::cerr << "Caught SizeLimitExceededException: " << e.what() << std::endl;
    } catch (const DataCollectionException& e)
    {
        // Пытаемся поймать более общую ошибку общую для нашего класса
        std::cerr << "Caught DataCollectionException: " << e.what() << std::endl;
    } catch (const std::exception& e)
    {
        // Здесь пытаемся поймать наиболее общую ошибку, если предыдущие не получилось
        std::cerr << "Caught std::exception: " << e.what() << std::endl;
    }

    try
    {
        // На этот раз создаём объект класса DataCollection с верными параметрами
        int sizeOfArray1 = 50;
        int sizeOfArray2 = 30;
        std::string nameOfDataCollection = "ValidCollection";
        DataCollection validCollection(sizeOfArray1, sizeOfArray2, nameOfDataCollection);

        // Тут пытаемся получить доступ к элементу, который лежит в пределах массива
        int value = validCollection[10];

        // В свою очередь, здесь пытаемся получить доступ к элементу с несуществующим индексом
        // Соответственно, будет выброшена ошибка IndexOutOfBoundsException
        value = validCollection[100];

        // Очевидно, эта строка не будет достигнута...
        std::cout << validCollection << std::endl;

        // Опять идём от частного к общему
    } catch (const NegativeNumberIndexingException& e)
    {
        // Предпоалагаем попытку обращения по отрицательному индексу
        std::cerr << "Caught NegativeNumberIndexingException: " << e.what() << std::endl;
    }
    catch (const IndexOutOfBoundsException& e)
    {
        // Более общая ошибка в виде индекса за пределами массива
        std::cerr << "Caught IndexOutOfBoundsException: " << e.what() << std::endl;
    } catch (const DataCollectionException& e)
    {
        // Ещё более общая ошибка, но всё ещё специфичная для нашего класса
        std::cerr << "Caught DataCollectionException: " << e.what() << std::endl;
    } catch (const std::exception& e)
    {
        // И наболее общая ошибка
        std::cerr << "Caught std::exception: " << e.what() << std::endl;
    }

    return 0;
}
