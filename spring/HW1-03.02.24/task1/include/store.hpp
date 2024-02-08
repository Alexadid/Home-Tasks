#ifndef STORE_HPP
#define STORE_HPP

#include <iostream>
#include <string>
#include <vector>
#include <memory>

// Уж лучше в этот раз я переборщу с количеством комментариев, чем получится, как в прошлый раз...

// Заранее объявляем класс Buyer для устранения циклической зависимости
class Buyer;

// Объявление класса Product
class Product : public std::enable_shared_from_this<Product>
{
public:
    // Конструктор, принимающий на вход имя и цену продукта
    Product(const std::string& name, double price);

    // Метод для добавления покупателся, который купил товар
    void addCustomer(const std::shared_ptr<Buyer>& buyer);

    // Метод для вывода покупателей, которые купили товар
    void displayCustomers();

    // Геттер-метод для получения имени продукта
    std::string getName() const;

    // Геттер-метод для получения цены продукта
    double getPrice() const;
private:
    std::string name;   // Имя продукта
    double price;       // Цена продукта
    std::vector<std::shared_ptr<Buyer>> customers;  // Ветор shared_ptr к покупателям, которые купили товар
};

// Объявление класса Buyer
class Buyer : public std::enable_shared_from_this<Buyer>
{
public:
    // Конструктор, принимающий имя и доступный бюджет (за неимением лучшего слова) покупателя
    Buyer(const std::string& name, double availableMoney);

    // Метод для преобретения покупателем продутка
    void buyProduct(const std::shared_ptr<Product>& product);

    // Метод для вывода продуктов, которые купил покупатель
    void displayPurchasedProducts();

    // Геттер-метод для получения имени покупателя
    std::string getName() const;
private:
    std::string name;       // Имя покупателя
    double availableMoney;  // Бюджет покупателя (доступные деньги для покупки...)
    std::vector<std::shared_ptr<Product>> products; // Ветор shared_ptr к продуктам, которые купил покупатель
};

#endif // STORE_HPP
