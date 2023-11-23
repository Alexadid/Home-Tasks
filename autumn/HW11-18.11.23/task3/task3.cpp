#include <iostream>
#include <utility>

template <typename Func1, typename Func2, typename... Args>
auto variable_function(Func1 func1, Func2 func2, Args&&... args)
{
    // Предполагая, что обе функции имеют одинаковое количество и типы аргументов
    return std::make_pair(func1(std::forward<Args>(args)...), func2(std::forward<Args>(args)...));
}

int main()
{
    auto lambda1 = [](int arg1, int arg2) { return arg1 + arg2; };
    auto lambda2 = [](int arg1, int arg2) { return arg1 * arg2; };

    // Пример с целочисленными аргументами
    int argument1 = 3;
    int argument2 = 4;
    auto result = variable_function(lambda1, lambda2, argument1, argument2);

    std::cout << "Result of lambda1: " << result.first << std::endl;
    std::cout << "Result of lambda2: " << result.second << std::endl;

    return 0;
}
