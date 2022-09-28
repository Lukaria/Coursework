//Использование базовыъ принципов объектно-ориентированного программирования
// (наследования)


#ifndef CURSED_ADMIN_H
#define CURSED_ADMIN_H
#pragma once

#include "User.h"
#include "Customer.h"//!?!

class Admin : public User {
public:
    Admin() : User("Admin") {};

    Admin(string username, string password) : User("Admin", username, password) {};

    Admin(string role, string username, string password) : User(role, username, password) {};

    Admin(string role, string username, string password, string address) : User(role, username, password, address) {};

    Admin(const Admin& obj);

    void Interface() override;

    void RestaurantInterface();

    void CustomerInterface();

    static void RestaurantDishInterface(string type);

};

#endif //CURSED_ADMIN_H
