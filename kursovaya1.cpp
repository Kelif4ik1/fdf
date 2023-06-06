#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <Windows.h>

using namespace std;

struct Product {
    int number;
    string name;
    int quantity;
    double price, cost;
};

void printProductInfo(const vector<Product>& products, int number) {
    for (const auto& product : products) {
        if (product.number == number) {
            cout << "Изделие с номером " << number << " есть на складе. Количество: " << product.quantity << endl;
            return;
        }
    }

    cout << "Изделие с номером " << number << " отсутствует на складе." << endl;
}

void printTotalCost(const vector<Product>& products) {
    double totalCost = 0;

    for (const auto& product : products) {
        totalCost += product.cost;
    }

    cout << totalCost << endl;
}

void printProductsWithinRange(const vector<Product>& products, int start, int end) {
    cout << "Список изделий c номерами в диапазоне от " << start << " до " << end << ":" << endl;

    for (const auto& product : products) {
        if (product.number >= start && product.number <= end) {
            cout << product.number << " " << product.name << endl;
        }
    }
}

void printProductWithMaxPrice(const vector<Product>& products) {
    auto maxPriceProduct = max_element(products.begin(), products.end(), [](const Product& a, const Product& b) {
        return a.price < b.price;
        });

    cout << "Изделие с самой большой ценой: " << maxPriceProduct->name << ", цена: " << maxPriceProduct->price << endl;
}

void printProductsWithNameStartingWith(const vector<Product>& products, char letter) {
    cout << "Список изделий на складе, наименование которых начинается с буквы " << letter << ":" << endl;

    for (const auto& product : products) {
        if (product.name.size() > 0 && product.name[0] == letter) {
            cout << product.number << " " << product.name << endl;
        }
    }
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    ifstream file("products.bin", ios::binary);

    if (!file.is_open()) {
        cout << "Не удалось открыть файл с данными о товарах." << endl;
        return 0;
    }

    vector<Product> products;

    while (!file.eof()) {
        Product product;
        file >> product.number >> product.name >> product.quantity >> product.price >> product.cost;
        products.push_back(product);
    }

    file.close();
    int a, b; string c;
    //5. Выдать список изделий на складе, наименование которых начинается с заданной буквы.\n6. Выход из программы.\n"
    cout << "Выдать справку о наличии товара на складе по его номеру.";
    cout << "Введите номер товара: "; cin >> a;
    printProductInfo(products, a);
    cout << "Выдать общую стоимость всех изделий." << endl << "Общая стоимость всех изделий, хранящихся на складе: ";
    printTotalCost(products);
    cout << "Выдать список всех изделий с номераи в заданном интервале." << endl << "Задайте интервал двумя числами:" << endl;
    cin >> a >> b;
    printProductsWithinRange(products, a, b);
    cout << "Найти изделие с самой большой ценой." << endl;
    printProductWithMaxPrice(products);
    cout << "Выдать список изделий на складе, наименование которых начинается с заданной буквы." << endl << "Введите букву: ";
    cin >> c;
    printProductsWithNameStartingWith(products, c[0]);

    return 0;
}