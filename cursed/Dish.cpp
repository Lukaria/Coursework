//
// Created by Shedory on 16.04.2022.
//

#include "Dish.h"

void Dish::SetPrice(float price) { this->price = price; }

float Dish::GetPrice() const { return price; }

void Dish::SetKkal(int kkal) { this->kkal = kkal; }

int Dish::GetKkal() { return kkal; }

void Dish::SetIngredients() {
    cin.ignore();
    cin >> ingredients;
}

string Dish::GetIngredients() {
    return ingredients;
}

void Dish::TableInfo()
{
    cout << "Название блюда\t" << "Цена\t" << "Калорийность";
    cout << "\nИнгредиенты" << endl;
}

//обработка данных
void Dish::GetData() {
    if (kkal == -1) { //в случае kkal == -1 (признак не_блюда) вывод изменяется
        cout << "#######################" << endl;
        cout << "Общая цена: " << price << endl;
        cout << "Дата заказа: " << ingredients << endl;
        cout << "Адрес доставки: " << restaurant << endl;
        cout << "#######################" << endl;
    }
    else {
        /*cout << type << endl;
        cout << "Цена: " << price << endl;
        cout << "Ингредиенты: " << ingredients << endl;
        cout << "Калорийность: " << kkal << endl;*/
        cout << type << '\t' << price << '\t' << kkal << endl;
        cout << ingredients << endl;
    }

}

Dish::Dish(const Dish& obj) {
    this->type = obj.type;
    this->price = obj.price;
    this->ingredients = obj.ingredients;
    //strcpy(this->ingredients, obj.ingredients);
    this->kkal = obj.kkal;
    this->restaurant = obj.restaurant;
}

istream& operator>>(istream& stream, Dish& obj) {
    getline(stream, obj.type, ':');
    while(obj.type[0] == '\n' || obj.type[0] == '\r') obj.type.erase(0, 1);
    getline(stream, obj.ingredients, ';');
    getline(stream, obj.restaurant, ';');
    stream >> obj.price >> obj.kkal;
    return stream;
}

ostream& operator<<(ostream& stream, Dish& obj) {
    stream << "\n" << obj.type << ":" << obj.ingredients << ";" << obj.restaurant << ";" << obj.price << endl
        << obj.kkal;
    return stream;
}




