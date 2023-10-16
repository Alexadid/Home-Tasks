#ifndef SECRETE_INFORMATION_HPP
#define SECRETE_INFORMATION_HPP

#include <iostream>
#include <string>

// Классs с данными, доступ к которым мы хотим дать определённой функции
class SecretClass1
{
    friend void printSensetiveData1(const SecretClass1&);
private:
    std::string m_dataPart1;
public:
    SecretClass1(const std::string& part1);

    void setData(const std::string& newData);

    std::string getData() const;
};

class SecretClass2
{
    friend void printSensetiveData2(const SecretClass2&);
private:
    std::string m_dataPart2;
public:
    SecretClass2(const std::string& part2);

    void setData(const std::string& newData);

    std::string getData() const;
};

// Прокси-класс контролирует доступ к классам SecretClass1 и SecretClass2
class ProxyClass : public SecretClass1, public SecretClass2
{
private:
    //std::string m_dataPart1;
    //std::string m_dataPart2;
    std::string m_dataPart3;
public:
    ProxyClass(const std::string& part1, const std::string& part2, const std::string& part3);

    void setDataPart1(const std::string& newData);
    void setDataPart2(const std::string& newData);
    void setDataPart3(const std::string& newData);

    void printSecreteInformation() const;
};

void printSensetiveData1(const SecretClass1&);

void printSensetiveData2(const SecretClass2&);

#endif