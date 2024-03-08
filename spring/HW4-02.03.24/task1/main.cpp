#include <algorithm>
#include <cmath>
#include <iostream>
#include <numeric>
#include <random>
#include <vector>
#include <set>



// Простейшая функция для определения, является ли число простым
bool is_prime(int num)
{
    // Если 0 или 1 - очевидно не простое
    if (num <= 1) return false;
    // 2 - первое простое число, сразу да!
    // В дальнейшем можно пропустить все чётные числа
    if (num == 2) return true;
    // Делаем ровно это - исключаем чётные
    if (num % 2 == 0) return false;

    for (int i = 3; i * i <= num; i += 2)
    {
        // Если делится на любое нечётное число вплоть до num^0.5, то не простое
        if (num % i == 0) return false;
    }

    // Если ничего не нашли, то очевидно, что число простое
    return true;
}

int main()
{
    // Подготавливаем всё для генерации случайных чисел
    std::random_device rd;
    std::mt19937 gen(rd());
    // Среднее = 0, стандартное отклонение = 1
    // Данное распределние потребуется для создания П2
    std::normal_distribution<> dis(0, 1);

    // a. Создаём последовательность П1
    // Поскольку я стараюсь использовать англоязычные названия для переменных,
    // назовём её Seq1 (Sequence 1)
    std::vector<int> Seq1(10);
    std::iota(Seq1.begin(), Seq1.end(), 1);
    
    // b. Добавляем числа, по желанию
    // Самой простой вариант реализовать ввод
    std::cout << "Enter numbers to add to Seq1, followed by non-numeric input (e.g., 'end') to finish:" << std::endl;
    std::copy(
        std::istream_iterator<int>(std::cin),
        std::istream_iterator<int>(),
        std::back_inserter(Seq1));

    // c. Перемешиваем П1
    std::shuffle(Seq1.begin(), Seq1.end(), gen);

    // d. Удаляем повторяющиеся элементы
    std::set<int> seen;
    std::vector<int> Seq1_unique;
    std::copy_if(Seq1.begin(), Seq1.end(), std::back_inserter(Seq1_unique),
                [&seen](const int& value) { return seen.insert(value).second; });

    Seq1 = Seq1_unique;

    // e. Подсчитываем нечётные числа
    int odd_count = std::count_if(Seq1.begin(), Seq1.end(), [](int x) { return x % 2 != 0; });

    std::cout << "Odd count: " << odd_count << std::endl;

    // f. Минимальное и максимальное значения
    auto [min_it, max_it] = std::minmax_element(Seq1.begin(), Seq1.end());

    std::cout << "Min: " << *min_it << ", Max: " << *max_it << std::endl;

    // g. Находим первое простое число (по порядку) в последовательности
    auto prime_it = std::find_if(Seq1.begin(), Seq1.end(), is_prime);

    // И выводим его
    if (prime_it != Seq1.end())
    {
        std::cout << "Found a prime: " << *prime_it << std::endl;
    } else
    {
        // Или пишем, что таких нет
        std::cout << "No prime found" << std::endl;
    }

    // h. Заменяем в П1 все элементы на их квадраты
    std::transform(Seq1.begin(), Seq1.end(), Seq1.begin(), [](int x) { return x * x; });

    // i. Создаём П2
    std::vector<double> Seq2(Seq1.size());
    std::generate(Seq2.begin(), Seq2.end(), [&]() { return dis(gen); });

    // j. Вычисляем сумму элементов П2
    double sum_Seq2 = std::accumulate(Seq2.begin(), Seq2.end(), 0.0);

    std::cout << "Sum of Seq2: " << sum_Seq2 << std::endl;

    // k. Заменяем несколько первых элементов в П2 на 1
    // Предполагаем, что 'несколько' - это aFewElements (3 в моём исоплнении)
    int aFewElements = 3;
    std::fill_n(Seq2.begin(), std::min(aFewElements, static_cast<int>(Seq2.size())), 1.0);

    // l. Создаём П3, как разность между П1 и П2, благо количество элементов одинаковое
    std::vector<double> Seq3(Seq1.size());
    std::transform(Seq1.begin(), Seq1.end(), Seq2.begin(), Seq3.begin(), std::minus<>());

    // m. Заменяем все отрицательные элементы в П3 на нули
    std::transform(Seq3.begin(), Seq3.end(), Seq3.begin(), [](double x) { return x < 0 ? 0.0 : x; });

    // n. Избавляемся от всех нулевых элементов в П3
    Seq3.erase(std::remove(Seq3.begin(), Seq3.end(), 0.0), Seq3.end());

    // o. Изменяем порядок элементов в П3 на обратный
    std::reverse(Seq3.begin(), Seq3.end());

    // p. Определяем 3 наибольших элемента в П3 путём частичной сортировки
    std::vector<double> top3(std::min(3, static_cast<int>(Seq3.size())));
    std::partial_sort_copy(Seq3.begin(), Seq3.end(), top3.begin(), top3.end(), std::greater<>());

    std::cout << "Top 3 elements in Seq3: " << std::endl;
    for (auto n : top3) std::cout << n << " ";
    std::cout << std::endl;

    // q. Сортируем П1 и П2 по возрастанию
    std::sort(Seq1.begin(), Seq1.end());
    std::sort(Seq2.begin(), Seq2.end());

    // r. Создаём П4 слиянием П1 и П2
    std::vector<double> Seq4(Seq1.size() + Seq2.size());
    // Для корректности переводим элементы П1 из int в double
    std::transform(Seq1.begin(), Seq1.end(), Seq1.begin(), [](int x) { return static_cast<double>(x); });
    std::merge(Seq1.begin(), Seq1.end(), Seq2.begin(), Seq2.end(), Seq4.begin());

    // s. Определяем диапазон для упорядоченной вставки числа 1 в П4
    auto lower = std::lower_bound(Seq4.begin(), Seq4.end(), 1.0);
    auto upper = std::upper_bound(Seq4.begin(), Seq4.end(), 1.0);

    std::cout << "Range for 1 in Seq4: [" << std::distance(Seq4.begin(), lower) << ", " << std::distance(Seq4.begin(), upper) << ")" << std::endl;

    // Выводим полученные последовательности
    std::cout << "Seq1: ";
    for (auto elementsOfSeq1 : Seq1) std::cout << elementsOfSeq1 << " ";
    std::cout << std::endl;

    std::cout << "Seq2: ";
    for (auto elementsOfSeq2 : Seq2) std::cout << elementsOfSeq2 << " ";
    std::cout << std::endl;

    std::cout << "Seq3: ";
    for (auto elementsOfSeq3 : Seq3) std::cout << elementsOfSeq3 << " ";
    std::cout << std::endl;

    std::cout << "Seq4: ";
    for (auto elementsOfSeq4 : Seq4) std::cout << elementsOfSeq4 << " ";
    std::cout << std::endl;

    return 0;
}
