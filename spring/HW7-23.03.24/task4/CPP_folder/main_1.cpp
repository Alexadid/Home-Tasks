#include <iostream>
#include <random>
#include <thread>
#include <vector>
#include <atomic>
#include <cmath>



// Общий ресурс - число точек под кривой для всех потоков
int pointsBelowCurve = 0;
// Мьютекс для защиты общего ресурса
std::mutex pointsMutex;


// Класс-обёртка над генераторми случайных чисел.
// Призван немного ускорить обсчёт за счёт того, что генератор не будет инициализироваться
// при каждом вызове функции monteCarlo
class ThreadLocalRandom
{
public:
    // Конструктор параметризованный,
    // так как расчитывается сугубо число Гомперца, генерируем числа в диапазоне от 0 до 1 
    ThreadLocalRandom() : gen(std::random_device{}()), dis(0.0, 1.0) {}

    // Метод для соответственно генерации
    double nextDouble()
    {
        return dis(gen);
    }

private:
    // Использую ветер Мерсенна в качестве генератора
    std::mt19937 gen;
    std::uniform_real_distribution<> dis;
};

/*
============================================================================================================================
Скажу пару слов об оценке числе Гомперца.
В случае использования геометричсекого метода Монте Карло мы ограничиваем подинтегральную фукнцию прямоугольником,
а затем генерируем точки. По числу точек, оказавшихся под кривой, заданной исходной функцией, мы оцениваем искомое число.
Число Гомперца может быть вычислено, интегрирую функцию f(x) = 1 / (1 - ln(x)) на отрезке от 0 до 1
(таким образом, область ограничивается квадратом со стороной 1)
============================================================================================================================
*/

// Фукнция вычисляющая значение функции f(x)
double f(double x)
{
    return 1.0 / (1.0 - std::log(x));
}

// Реализация геометричсекого метода Монте Карло в параллельном виде
void monteCarlo(int pointsPerThread, ThreadLocalRandom& rand)
{
    // Локальный счётчик для точек, которые попали под кривую
    int belowCurve = 0;
    for(int i = 0; i < pointsPerThread; ++i)
    {
        // Генерируем точку
        double x = rand.nextDouble();
        double y = rand.nextDouble();
        if(y < f(x)) belowCurve++;
    }
    // Используем мьютекс 
    std::lock_guard<std::mutex> guard(pointsMutex);
    pointsBelowCurve += belowCurve;
    // Мьютекс автоматически освобождается, когда происходит выход за пределы области видимости
}

int main()
{
    // Общее число точек
    const int totalPoints = 1000000;
    // Количество потоков, основанное на hardware_concurrency
    const int numThreads = std::thread::hardware_concurrency();
    // Итого получаем число точек в каждом из потоков
    int pointsPerThread = totalPoints / numThreads;

    // Вектор для хранения потоков
    std::vector<std::thread> threads;

    for(int i = 0; i < numThreads; ++i)
    {
        threads.push_back(std::thread([=]()
        {
            // Для каждого потока инициализируем ThreadLocalRandom
            ThreadLocalRandom rand;
            monteCarlo(pointsPerThread, rand);
        }));
    }

    // Дожидаемся завершения работы всех потоков
    for(auto& thr : threads)
    {
        thr.join();
    }

    double estimatedArea = static_cast<double>(pointsBelowCurve) / totalPoints;

    // Вуаля, число Гомперца оценено
    std::cout << "Estimated Gompertz number: " << estimatedArea << std::endl;

    return 0;
}
