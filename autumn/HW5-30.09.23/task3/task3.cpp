#include <iostream>
#include <string>

#include "secreteInforamtion.hpp"

int main()
{
    ProxyClass objectOfProxyClass("This is sensetive data. Part 1.", "This is sensetive data. Part 2.", "This is sensetive data. Part 3.");

    printSensetiveData1(objectOfProxyClass);
    printSensetiveData2(objectOfProxyClass);

    objectOfProxyClass.printSecreteInformation();

    objectOfProxyClass.setDataPart1("This is the new secrete info.");

    objectOfProxyClass.printSecreteInformation();

    printSensetiveData1(objectOfProxyClass);

    return 0;
}

// Опишем новую систему...

// Во главе угла стоит ProxyClass, который принимает данные и позволяет их изменять.
// В свою очередь, доступ к m_dataPart1 раздаёт SecretClass1, а к m_dataPart2 - SecretClass2
// при помощи ключевого слова friend
// Поулчается это путём наследования, полей m_dataPart1 и m_dataPart2 класом ProxyClass

// Как-то так на данный момент.