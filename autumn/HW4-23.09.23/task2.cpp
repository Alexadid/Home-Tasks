#include <iostream>
#include <string>
#include <vector>

// Заранее объявляем структуры (иначе будем получать ошибки) и функции
struct Product;
struct Customer;

void updateProductCustomers(Product*, Customer*);
void displayPurchases(const std::vector<Product>&);

// Определение структуры Product
struct Product
{
    std::string name;
    double price;
    // Вектор указателй на покупателей, которые купили этот продукт
    std::vector<struct Customer*> customers;
};

// Определение структуры Customer
struct Customer
{
    std::string name;
    double availableMoney;
    // Вектор указателй на продукты, которые купил этот покупатель
    std::vector<struct Product*> purchasedProducts;
};



int main()
{
    // Создаём веткоры продуктов и покупателей соответственно
    std::vector<Product> products = {
        {"Apples", 1.0},
        {"Bananas", 0.5},
        {"Milk", 2.0},
        {"Dark Matter", 999.9}
    };

    std::vector<Customer> customers = {
        {"Alice", 10.0},
        {"Borya", 15.0}
    };

    // Симулируем покупки
    updateProductCustomers(&products[0], &customers[0]); // Алиса покупает яблоки
    updateProductCustomers(&products[1], &customers[0]); // Она же покупает бананы
    updateProductCustomers(&products[2], &customers[0]); // И молоко

    updateProductCustomers(&products[1], &customers[1]); // Боря покупает только бананы
    updateProductCustomers(&products[3], &customers[1]); // Боря не покупает тёмную материю, т.к. средств не хватает

    // Отображаем покупки
    displayPurchases(products);

    return 0;
}

// Фкнция для обновления вектора покупателей, которые купили определённый продукт
void updateProductCustomers(Product* product, Customer* customer)
{
    // Проверяем может ли покупатель позволить себе продукт
    if (customer->availableMoney >= product->price)
    {
        customer->availableMoney -= product->price;
        product->customers.push_back(customer);
        customer->purchasedProducts.push_back(product);
    }
}

// Фкнция для отображения покупок
void displayPurchases(const std::vector<Product>& products)
{
    for (const auto& product : products)
    {
        std::cout << "Product: " << product.name << ", Price: $" << product.price << std::endl;
        std::cout << "Customers who bought this product:" << std::endl;

        for (const auto& customerPtr : product.customers)
        {
            std::cout << "- " << customerPtr->name << std::endl;
        }

        std::cout << std::endl;
    }
}