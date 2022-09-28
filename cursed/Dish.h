//
// Created by Shedory on 16.04.2022.
//

#ifndef CURSED_DISH_H
#define CURSED_DISH_H
#pragma once

#include "Exception.h"
#include <string>
#include <vector>
#include <cstring>

//using namespace check;

using namespace std;

class Dish {
    string restaurant;
    string type;
    float price;
    //char ingredients[255];
    string ingredients;
    int kkal;

public:
    Dish() : price(0), kkal(0) {};

    Dish(string type, float pr, string ingredients, int kal) : type(type), price(pr), kkal(kal) {
        //strcpy(this->ingredients, ingredients);
        this->ingredients = ingredients;
    }

    Dish(string type, float pr, string ingredients, int kal, string restaurant) : type(type), price(pr), kkal(kal),
        restaurant(restaurant) {

        this->ingredients = ingredients;
        //strcpy(this->ingredients, ingredients.c_str());
    }

    //Конструктор используется для создания объекта типа Dish, который содержит информацию об общей стоимости заказа
    //и дате его оформления. Имеет форматированный вывод
    Dish(float totalmoney, string datetime, string address) {
        this->restaurant = address;
        this->price = totalmoney;
        this->type = "NotDish";
        this->kkal = -1; //для форматирования вывода
        this->ingredients = datetime;
        //strcpy(this->ingredients, datetime.c_str());
    };

    Dish(const Dish& obj);

    ~Dish() = default;

    void SetType(string type) { this->type = type; }

    string GetType() { return type; }

    void SetPrice(float price);

    float GetPrice() const;

    void SetIngredients();

    string GetIngredients();

    void SetKkal(int kkal);

    int GetKkal();

    string GetRestaurant() { return restaurant; }

    void SetRestaurant(string restaurant) { this->restaurant = restaurant; } //установка ресторана, содержащего это блюда
                     
                                                                             //поле используется для фильтрации
    void TableInfo();

    void GetData();

    friend ostream& operator<<(ostream& stream, Dish& obj);

    friend istream& operator>>(istream& stream, Dish& obj);

    friend bool operator<(const Dish& obj1, const Dish& obj2) { return obj1.ingredients < obj2.ingredients;
    /*return obj1.price <= obj2.price;*/ }

    friend bool operator>(const Dish& obj1, const Dish& obj2) { return obj1.price > obj2.price; }
};


#endif //CURSED_DISH_H
