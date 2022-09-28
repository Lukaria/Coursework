//
// Created by Shedory on 19.04.2022.
//

#ifndef CURSED_ORDER_H
#define CURSED_ORDER_H
//#define _CRT_SECURE_NO_WARNINGS
#pragma once

#include <ctime>
#include <iostream>
#include <list>
#include "Dish.h"
#include "FileFunc.h"


using namespace std;

class Order {
    string datetime;
    string username;
    string address;
    float totalmoney = 0;
    list<Dish> receipt; //корзина
public:
    void GetUsername() { exit(-1); }

    Order() : username("N/A"), address("N/A"), totalmoney(0) {
        time_t currentTime = time(nullptr);
        datetime = asctime(localtime(&currentTime));
    }

    Order(string username, float totalmoney) : username(username), totalmoney(totalmoney) {
        time_t currentTime = time(nullptr);
        datetime = asctime(localtime(&currentTime));
    }


    string UpdateTime();

    string GetTime() { return datetime; }

    void SetOrderName(string name) { username = name; }

    void SetOrderInfo(string username, string address) {
        this->username = username;
        this->address = address;
    }


    string GetOrderName() { return username; }

    void SetTotalmoney(float money) { totalmoney = money; }

    float GetTotalmoney() { return totalmoney; }

    void Push(Dish dish);

    void GetOrder();

    void GetReceipts();
};


#endif //CURSED_ORDER_H
