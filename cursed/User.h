//»спользование базовыъ принципов объектно-ориентированного программировани€
// (абстракци€, инкапсул€ци€)
// использование перегрузки методов и операторов

#ifndef CURSED_USER_H
#define CURSED_USER_H
#pragma once

#include <string.h>
#include <iostream>
#include "Restaurant.h"//#include "Dish.h" , #include "FileFunc.h"
#include "Order.h"//#include "Dish.h" , #include "FileFunc.h"
#include <memory>
#include <iomanip>

using namespace std;

class User {
protected:
    string role;
    string username;
    string password;
    string address;
    Order order;
public:
    User() : role(""), username(""), password(""), address("") {};

    User(string role) : role(role), username("N/A"), password("blueprint"), address("N/A") {};

    User(string role, string username, string password) : role(role), username(username),
        password(password), address("N/A") {};

    User(string role, string username, string password, string address);

    User(string username, string password) : username(username),
        password(password), address("N/A") {};


    virtual bool IncludeUser(string role);

    int Authorization(string username, string password);//сделать виртуальной

    string Encoder();

    string Encoder(string str);

    string Decoder();

    virtual void Interface() = 0;

    string GetUsername() { return username; }

    //метод FileFunc.GetRestCustName использует дл€ получени€ имени (или названи€ блюда)
    string GetType() { return username; }

    void SetUsername(string username) { this->username = username; }

    string GetPassword() { return password; }

    string GetRole() { return role; }

    void SetRole(string role) { this->role = role; }

    void SetPassword(string password) { this->password = password; }


    string GetAddress() { return address; }

    void SetAddress(string address) { this->address = address; }

    string UpdateAddress();

    void TableInfo();

    void GetData();

    friend bool operator==(const User& obj1, const User& obj2) {
        if (obj1.role == obj2.role &&
            obj1.username == obj2.username &&
            obj1.password == obj2.password)
            return true;//декодер парол€ вроде не нужен
        return false;
    }


    friend ostream& operator<<(ostream& out, const User& obj);

    friend istream& operator>>(istream& in, User& obj);

};


#endif //CURSED_USER_H
