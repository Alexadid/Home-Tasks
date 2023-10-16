#include "secreteInforamtion.hpp"
#include <iostream>

SecretClass1::SecretClass1(const std::string& part1): m_dataPart1(part1) {}

void SecretClass1::setData(const std::string& newData) { m_dataPart1 = newData; }

std::string SecretClass1::getData() const { return m_dataPart1; }

SecretClass2::SecretClass2(const std::string& part2): m_dataPart2(part2) {}

void SecretClass2::setData(const std::string& newData) { m_dataPart2 = newData; }

std::string SecretClass2::getData() const { return m_dataPart2; }

ProxyClass::ProxyClass(const std::string& part1, const std::string& part2, const std::string& part3)
    : SecretClass1(part1), SecretClass2(part2), m_dataPart3(part3) {}

void ProxyClass::printSecreteInformation() const
{
    std::cout << SecretClass1::getData() << ' ' <<  SecretClass2::getData() << ' ' <<  m_dataPart3 << std::endl;
}

void ProxyClass::setDataPart1(const std::string& newData) { SecretClass1::setData(newData); }

void ProxyClass::setDataPart2(const std::string& newData) { SecretClass2::setData(newData); }

void ProxyClass::setDataPart3(const std::string& newData) { m_dataPart3 = newData; }

void printSensetiveData1(const SecretClass1& obj) { std::cout << obj.m_dataPart1 << std::endl; }

void printSensetiveData2(const SecretClass2& obj) { std::cout << obj.m_dataPart2 << std::endl; }