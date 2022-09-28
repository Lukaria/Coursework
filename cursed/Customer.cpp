//
// Created by Shedory on 18.04.2022.
//

#include "Customer.h"

//общее меню пользователя
void Customer::Interface() {
    Restaurant restaurant;
    while (true) {
        system("cls");
        cout << "Добро пожаловать, " << username << '!' << endl;
        cout << "(1) - Меню" << endl;
        cout << "(2) - Корзина" << endl;
        cout << "(3) - Мой профиль" << endl;
        cout << "(4) - Выход из приложения" << endl;
        int choice1;
        choice1 = check::SwitchCheck(4);
        switch (choice1) {
        case 1:
            while (true) {
                FileFunc<Restaurant> infile;
                system("cls");
                int i = restaurant.RestaurantMenu();
                if (i == -1) break;
                int j = restaurant.GetRestaurantMenu(i);
                string str = infile.GetRestCustName("all", i);
                if (j == -1) continue;
                FileFunc<Dish> dish;
                order.SetOrderName(username);
                order.Push(dish.GetObj("Restaurants\\" + str, j - 1));
                cout << "Готово!" << endl;
                system("pause");
            }
              break;
        case 2:
            order.SetOrderInfo(this->username, this->address);
            order.GetOrder();
            break;
        case 3:
            MyProfile();
            break;
        case 4:
            exit(0);
        }
    }
}

//личный кабинет пользователя
void Customer::MyProfile() {
    FileFunc<Customer> file;
    int choice;
    string str;
    system("cls");
    while (true) {
        system("cls");
        cout << "Имя: " << username << endl;
        cout << "Адрес доставки: " << this->address << endl;
        cout << "------------------------------\n";
        cout << "(1) - Изменить имя\n(2) - Изменить пароль\n(3) - Изменить адрес доставки\n";
        cout << "(4) - Список заказов\n(5) - В главное меню\n(6) - Выход из приложения" << endl;
        choice = check::SwitchCheck(6);
        switch (choice) {
        case 1: {
            while (true) {
                cout << "Введите новое имя: ";
                string newname;
                getline(cin, newname, '\n');
                Customer cust("Customer", newname, this->password);
                if (!file.isNameExistInFile("Users", newname)) {

                    file.EditFile("Users", cust, file.GetPos("Users", username));
                    FileFunc<Dish> file2;
                    file2.MoveFile("Receipts\\" + username + "Receipt", "Receipts\\" + newname + "Receipt");
                    username = newname;
                    cout << "Готово!" << endl;
                    system("pause");
                    break;
                }
                else cout << "Пользователь с данным именем уже существует!" << endl;
                system("pause");
            }
        }
              break;
        case 2: {
            string newpass;
            cout << "Введите старый пароль: ";
            getline(cin, newpass, '\n');
            if (newpass == Encoder()) {
                while (true) {
                    cout << "Введите новый пароль: ";
                    getline(cin, newpass, '\n');
                    if (newpass != Encoder()) {
                        password = newpass;
                        file.EditFile("Users", Customer("Customer", username, Decoder()),
                            file.GetPos("Users", username));

                        cout << "Пароль успешно изменен!" << endl;
                        break;
                    }
                    else cout << "Новый пароль не должен повторять старый" << endl;
                }

            }
            else cout << "Неверно введен пароль!" << endl;
            system("pause");
        }
              break;
        case 3: {
            this->address = UpdateAddress();
            Customer cust(this->role, this->username, this->password, this->address);

            file.EditFile("Users", cust, file.GetPos("Users", username));
            cout << "Готово!" << endl;
            system("pause");
        }
              break;
        case 4:
            order.SetOrderInfo(this->username, this->address);
            order.GetReceipts();
            break;
        case 5:
            return;
        case 6:
            exit(0);
        }
    }

}


