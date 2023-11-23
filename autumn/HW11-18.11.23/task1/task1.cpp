#include <iostream>
#include <cstring>



// вариантивный шаблон функции, использующий выражение свёртки
template<typename... Args>
int lengthWithFoldExpression(const Args&... args)
{
    return (... + std::strlen(args));
}

// вариативный шаблон функции, использлующий рекурсию вместо выржаения свёртки
template <typename Arg>
int length(const Arg& arg)
{
    return std::strlen(arg);
}

template <typename First, typename... OtherArguments>
int length(const First& f, const OtherArguments&... args)
{
    int result = 0;
    result += length(f);
    result += length(args...);
    return result;
}

int main()
{
    // Примеры использовал те же, что и вы дали
    // С использованием выражения свёртки
    std::cout << lengthWithFoldExpression("asd", "sssssss", "d") << std::endl;  // 11

    // Без исопльзования выржаения свёртки
    std::cout << length("asd", "sssssss", "d") << std::endl; // 11
    return 0;
}
