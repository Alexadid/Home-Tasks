#include <iostream>
#include <vector>

int main()
{
    // Эксперимент 1: Изменение ёмкости вектора при нехватке памяти для размещения новых элементов
    // Без ручного резервирования
    std::cout << "Expirement 1 has begun." << std::endl; 

    // Создаём вектор
    std::vector<int> vect1;
    // Подсчитываем ёмкость вектора при небольшом изменении
    size_t lastCapacity = 0;
    for (int i = 0; i < 100; ++i)
    {
        if (vect1.capacity() != lastCapacity)
        {
            std::cout << "Capacity changed: " << vect1.capacity() << std::endl;
            lastCapacity = vect1.capacity();
        }
        vect1.push_back(i);
    }

    

    // Попробуем увеличить ёмкость вектора более, чем в 2 раза за раз
    std::vector<int> vect2;
    // Подсчитываем ёмкость вектора при небольшом изменении
    lastCapacity = 0;
    for (int i = 0; i < 100; i += 2*i+1)
    {
        
        if (vect2.capacity() != lastCapacity)
        {
            std::cout << "Capacity changed: " << vect2.capacity() << std::endl;
            std::cout << "Size: " << vect2.size() << std::endl;
            lastCapacity = vect2.capacity();
        }

        for (int j = 0; j < i; ++j)
        {
            vect2.push_back(i);
        }
    }



    // Эксперимент 2: Изменение ёмкости вектора при нехватке памяти для размещения новых элементов
    // С ручным резервированием
    std::cout << "Expirement 2 has begun." << std::endl;

    int manualCapacity = 50;
    std::vector<int> vecWithReserve;

    vecWithReserve.reserve(manualCapacity);
    lastCapacity = 0;
    for (int i = 0; i < 100; ++i)
    {
        if (vecWithReserve.capacity() != lastCapacity)
        {
            std::cout << "Capacity changed (with manual reserve): " << vecWithReserve.capacity() << std::endl;
            lastCapacity = vecWithReserve.capacity();
            
        }
        vecWithReserve.push_back(i);
    }



    // Эксперимент 3: Запрос большого количества памяти
    std::cout << "Expirement 3 has begun." << std::endl;

    std::vector<int> largeVec;
    // Чётвёрка - это далеко не случайный выбор и не магическое число
    size_t arbitrarilyLargeNumber = std::numeric_limits<size_t>::max() / 4;

    try
    {
        largeVec.reserve(arbitrarilyLargeNumber);
        std::cout << "Large reserve successful, capacity: " << largeVec.capacity() << std::endl;
    } catch (const std::bad_alloc& error)
    {
        std::cout << "Allocation failed: " << error.what() << std::endl;
    } catch (const std::length_error& error)
    {
        std::cout << "Allocation failed: " << error.what() << std::endl;
    }

    return 0;
}

// Поговорим о наблюдаемых особенностях векторов.

// Эксперимент 1.

/*
Capacity changed: 1
Capacity changed: 2
Capacity changed: 4
Capacity changed: 8
Capacity changed: 16
Capacity changed: 32
Capacity changed: 64
Capacity changed: 128
*/

// Прекрасно видно, что вектор удваивает свою ёмкость каждый раз, когда ему требуется увеличить размер.
// После прочтения нескольких статей в интернете выяснилось следующее.
// Точный коэффициент роста не указан стандартом C++ и может отличаться в разных реализациях
// (например, libc++abi, используемый g++ на mac).

/*
Capacity changed: 1
Size: 1
Capacity changed: 8
Size: 5
Capacity changed: 32
Size: 18
*/

// Кроме того, в случае libc++abi, если вектору требуется увеличить свою ёмкость более, чем в 2 раза,
// он увеличивает её до такого значения 2^n, что оно больше (или равно) необходимой для выполнения операции ёмкости

// Эксперимент 2.

/*
Capacity changed (with manual reserve): 50
Capacity changed (with manual reserve): 100
*/

// Вручную установив начальную ёмкость вектора с использованием reserve, можно уменьшить количество раз,
// когда вектору необходимо увеличивать свою ёмкость.
// Коэффициент роста такой же, что и в эксперименте 1.
// (по крайней мере, в случае g++)

// Эксперимент 3.

// При запросе слишком большого объёма памяти вызов reserve вызывает исключение std::bad_alloc,
// если система не может предоставить запрошенную память (кроме ряда случаев)

// Именно об этих случаях мы и поговорим...
// 1) std::bad_alloc - возникает в выше описанном случае
// 2) std::length_error - возникает в результате попыток
// превысить установленные реализацией ограничения длины для некоторого объекта
// (оносится не только к вектору)

// Последний случай возникает при примерно
// arbitrarilyLargeNumber >= std::numeric_limits<size_t>::max() / 3;