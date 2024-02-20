#ifndef STORE_HPP
#define STORE_HPP

#include <iostream>
#include <string>
#include <vector>
#include <memory>

class Buyer;

// Объявление класса Product
class Product
{
public:
    // Конструктор, принимающий на вход имя и цену продукта
    Product(const std::string& name, double price);

    // Метод для добавления покупателся, который купил товар
    void addCustomer(const std::weak_ptr<Buyer>& buyer);

    // Метод для вывода покупателей, которые купили товар
    void displayCustomers();

    // Геттер-метод для получения имени продукта
    std::string getName() const;

    // Геттер-метод для получения цены продукта
    double getPrice() const;
private:
    std::string name;   // Имя продукта
    double price;       // Цена продукта
    std::vector<std::weak_ptr<Buyer>> customers; // // Ветор weak_ptr к покупателям, которые купили товар
};

// По поводу использования enable_shared_from_this...
// По отношению к Product его испозование было избыточным, а вообще смысл в нём есть.
// Классу Buyer требуется предоставить std::shared_ptr к саму себе, чтобы работать с Product
// Механизм std::enable_shared_from_this соответственно позволяет классу Buyer ссылаться на самого себя без создания
// ещё одного контрольного блока. Как-то так.

// Объявление класса Buyer
class Buyer : public std::enable_shared_from_this<Buyer>
{
public:
    // Конструктор, принимающий имя и доступный бюджет (за неимением лучшего слова) покупателя
    Buyer(const std::string& name, double availableMoney);

    // Метод для прbобретения покупателем продутка
    void buyProduct(const std::shared_ptr<Product>& product);

    // Метод для вывода продуктов, которые купил покупатель
    void displayPurchasedProducts();

    // Геттер-метод для получения имени покупателя
    std::string getName() const;
private:
    std::string name;       // Имя покупателя
    double availableMoney;  // Бюджет покупателя (доступные деньги для покупки...)
    std::vector<std::shared_ptr<Product>> products; // Вектор shared_ptr к продуктам, которые купил покупатель
};

#endif // STORE_HPP
