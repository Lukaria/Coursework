//
// .
//

#ifndef CURSED_CUSTOMER_H
#define CURSED_CUSTOMER_H
#pragma once

#include "User.h"

class Customer : public User {
public:
    Customer() : User("Customer") {};

    Customer(string role, string username, string password) : User(role, username, password) {};

    Customer(string username, string password) : User("Customer", username, password) {};

    Customer(string role, string username, string password, string address) : User(role, username, password, address) {};

    void Interface() override;

    void MyProfile();
};


#endif //CURSED_CUSTOMER_H
