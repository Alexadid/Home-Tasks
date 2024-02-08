#include <iostream>
#include "include/store.hpp"

int main()
{
    // Создаём продукты

    // Чтобы никто даже не заикнулся о магических числах и строках...
    std::string nameOfProduct1 = "Apples";
    std::string nameOfProduct2 = "Bananas";
    std::string nameOfProduct3 = "Milk";
    std::string nameOfProduct4 = "Dark Matter";
    double priceOfProduct1 = 1.0;
    double priceOfProduct2 = 0.5;
    double priceOfProduct3 = 2.0;
    double priceOfProduct4 = 999.9;

    auto apples     = std::make_shared<Product>(nameOfProduct1, priceOfProduct1);
    auto bananas    = std::make_shared<Product>(nameOfProduct2, priceOfProduct2);
    auto milk       = std::make_shared<Product>(nameOfProduct3, priceOfProduct3);
    auto darkMatter = std::make_shared<Product>(nameOfProduct4, priceOfProduct4);

    // Создаём покупателей
    std::string nameOfCustomer1 = "Alice";
    std::string nameOfCustomer2 = "Borya";
    double availableMoneyOfCustomer1 = 10.0;
    double availableMoneyOfCustomer2 = 15.0;

    auto alice = std::make_shared<Buyer>(nameOfCustomer1, availableMoneyOfCustomer1);
    auto borya = std::make_shared<Buyer>(nameOfCustomer2, availableMoneyOfCustomer2);

    // Имитируем бурную деятельность в магазине
    alice->buyProduct(apples);
    alice->buyProduct(bananas);
    alice->buyProduct(milk);
    borya->buyProduct(bananas);
    borya->buyProduct(darkMatter);

    // Отображаем, какие покупатели купили данные товары
    apples->displayCustomers();
    bananas->displayCustomers();
    milk->displayCustomers();
    darkMatter->displayCustomers();

    // Отображаем, какие продукты купили данные покупатели
    alice->displayPurchasedProducts();
    borya->displayPurchasedProducts();

    return 0;
}
