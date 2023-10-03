#include <iostream>
#include <string>

// Класс с данными, доступ у которым извне не желателен.
class SecretClass
{
private:
    std::string sensitiveData = "This is sensitive data.";

public:
    void PublicMethod()
    {
        std::cout << "Public method can be accessed by anyone." << std::endl;
    }

    // Ээтот метод доступен только для прокси-класса.
    std::string GetSensitiveData()
    {
        return sensitiveData;
    }
};

// Прокси-класс контролирует доступ к классу SecretClass
class ProxyClass
{
private:
    SecretClass* secretObject;

public:
    ProxyClass(SecretClass* obj) : secretObject(obj) {}

    void AccessPublicMethod()
    {
        secretObject->PublicMethod();
    }

    std::string AccessSensitiveData()
    {
        // Здесь, соответственно, можно добавлять доступ к аналогичным полям...
        return secretObject->GetSensitiveData();
    }
};

int main()
{
    SecretClass secretObj;
    ProxyClass proxy(&secretObj);

    // Получаем доуступ к публичному методу
    proxy.AccessPublicMethod();

    // Получаем доступ через прокси
    std::string data = proxy.AccessSensitiveData();
    std::cout << "Accessed sensitive data: " << data << std::endl;

    // И пытаемся получить доступ к нежелательным данным из SecretClass (не выйдет).
    // std::string directDataAccess = secretObj.sensitiveData; // Ошибка компиляции

    return 0;
}

// В данной попытке реализовать подобный паттерн выбрана следующая стратегия.

// SecretClass содержит некие 'чувствительные' данные (не желательно, чтобы к ним получали доступ некотроллируемым образом)
// и публичный метод.

// ProxyClass играет роль защитного слоя,
// который даёт контроллируемый доступ к 'чувствительной' информации через метод AccessSensitiveData().

// Ключевое здесь это то, что определённые данные недоступны напрямую за пределами класса SecretClass,
// и только прокси-класс может получить к ним доступ.

// Как-то так.
