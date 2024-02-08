#include "../include/store.hpp"

// Определение методов класса Product

// Конструктор для класса Product
Product::Product(const std::string& name, double price) : name(name), price(price) {}

// Метод добавления, который купил товар
void Product::addCustomer(const std::shared_ptr<Buyer>& buyer)
{
    customers.push_back(buyer);
}

// Методя для вывода покупателей, которые купили продукт
void Product::displayCustomers()
{
    std::cout << "Customers who bought " << name << ":" << std::endl;
    for (const auto& customer : customers)
    {
        std::cout << "- " << customer->getName() << std::endl; // Моё любимое разыменование указателей
    }
}

// Геттер-метод для получения имени продукта
std::string Product::getName() const
{
    return name;
}

// Геттер-метод для получения цены продукта
double Product::getPrice() const
{
    return price;
}

// Определение методов класса Buyer

// Конструктор для класса Buyer
Buyer::Buyer(const std::string& name, double availableMoney) : name(name), availableMoney(availableMoney) {}

 // Метод для преобретения покупателем продутка
void Buyer::buyProduct(const std::shared_ptr<Product>& product)
{
    if (availableMoney >= product->getPrice())
    {
        availableMoney -= product->getPrice();
        products.push_back(product);
        product->addCustomer(shared_from_this());
    }
} // Можно будет потом добавить обработку ошибок...

// Метод для вывода продуктов, которые купил покупатель
void Buyer::displayPurchasedProducts()
{
    std::cout << "Products purchased by " << name << ":" << std::endl;
    for (const auto& product : products)
    {
        std::cout << "- " << product->getName() << std::endl;
    }
}

// Геттер-метод для получения имени покупателя
std::string Buyer::getName() const
{
    return name;
}
