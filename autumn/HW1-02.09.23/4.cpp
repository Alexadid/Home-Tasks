#include <iostream>

int main() {
    int firstCoefficient = 0;
    int secondCoefficient = 0;

    std::cout << "Type in values of coefficients x and y: ";
    std::cin >> firstCoefficient >> secondCoefficient;

    std::cout << "Before swapping: x = " << firstCoefficient << ", y = " << secondCoefficient << std::endl;

    // Используем оператор XOR на переменных firstCoefficient и secondCoefficient
    firstCoefficient = firstCoefficient ^ secondCoefficient;
    // Эта операция XOR объединяет биты firstCoefficient и secondCoefficient таким образом,
    // что firstCoefficient теперь содержит побитовый результат XOR.
    secondCoefficient = firstCoefficient ^ secondCoefficient;
    // Теперь, посколькуfirstCoefficientx содержит результат XOR,
    // применение XOR к secondCoefficient дает нам исходное значение firstCoefficient.
    firstCoefficient = firstCoefficient ^ secondCoefficient;
    // Аналогичным образом получаем новое значение firstCoefficient.

    std::cout << "After swapping: x = " << firstCoefficient << ", y = " << secondCoefficient << std::endl;

    return 0;
}
