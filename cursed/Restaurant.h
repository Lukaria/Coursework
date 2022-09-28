//
// Created by Shedory on 04.04.2022.
//
#pragma once

#include "FileFunc.h"
#include "Dish.h"

class Restaurant {
    string type;
    string tags[3];
public:
    Restaurant() : type("N/A") {};

    Restaurant(string type, string* arr);

    static int GetAllInfo();

    void WriteInfo();

    void AddDish(Dish dish);

    void DeleteDish(const int pos);

    void EditDish(Dish dish, const int pos);

    int GetRestaurantMenu(int pos);

    int RestaurantMenu();

    string GetType() { return type; }

    void TableInfo();

    void GetData();

    friend ostream& operator<<(ostream& out, const Restaurant& obj);

    friend istream& operator>>(istream& in, Restaurant& obj);
};