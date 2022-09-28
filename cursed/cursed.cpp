#include <iostream>
#include<direct.h>
#include "Customer.h"
#include "Admin.h"

using namespace std;

void terminator() {
    cerr << ">>UNEXPECTED ERROR" << endl;
    system("pause");
    exit(-1);
}

void folders() {
    _mkdir("DATA");
    _mkdir("DATA\\Receipts");
    _mkdir("DATA\\Restaurants");
}

int main() {
    folders();
    /*Admin obj("Admin", "admin", "qwert", "--");
    obj.IncludeUser("Admin");*/
    system("chcp 1251");
    User* user = new Admin();
    set_terminate(terminator);
    FileFunc<Customer> file;
    int choice;
    while (true) {
        system("cls");
        cout << "\t\t\t--Служба доставки еды--\n";
        cout << "(1) - Вход\t\t(2) - Регистрация\t\t(3) - Выход" << endl;
        choice = check::SwitchCheck(3);
        switch (choice) {
        case 1:    
        {
            bool authorizat = false;
            while (true) {
                string username, password;
                cout << "Введите логин: ";
                cin >> username;
                cout << "Введите пароль: "; 
                cin.ignore();
                cin >> password;
                Customer user1(username, password);
                int i = user1.Authorization(username, password);
                password = user1.Encoder();

                if (i == 1) {
                    user = new Customer("Customer", username, password, 
                        file.GetObj("Users", file.GetPos("Users", username)).GetAddress());
                    authorizat = true;
                    break;
                }
                else if (i == 2) {
                    user = new Admin(username, password);
                    authorizat = true;
                    break;
                }
                else {
                    cout << "Неверный логин или пароль!" << endl;
                    system("pause");
                    cout << "(1) - Повторить ввод\n(2) - Назад" << endl;
                    if (check::SwitchCheck(2) == 1) {
                        system("cls");
                        cout << "\t\t\t--Служба доставки еды--\n";
                        cout << "(1) - Вход\t\t(2) - Регистрация\t\t(3) - Выход\n1" << endl;
                    }
                    else break;
                }
            }
            if (authorizat) user->Interface();
        }
              break;
        case 2: {
            cout << "(1) - Как клиент\n(2) - Как сотрудник" << endl;
            string role;
            int i = check::SwitchCheck(2);
            if (i == 1) role = "Customer";
            else role = "Admin";
            bool authorizat = false;

            string username, password;
            while (true) {
                authorizat = true;
                cout << "Введите логин: ";
                cin >> username;
                if (file.isNameExistInFile("Users", username)) {
                    cout << "Пользователь с данным именем уже существует!" << endl;
                    cout << "(1) - Ввести новое имя\n(2) - Назад" << endl;
                    if (check::SwitchCheck(2) == 1) {
                        system("cls");
                        cout << "\t\t\t--Служба доставки еды--\n";
                        cout << "(1) - Вход\t\t(2) - Регистрация\t\t(3) - Выход" << endl;
                        cout << "2\n(1) - Как клиент\n(2) - Как сотрудник\n" << i << endl;
                    }
                    else {
                        authorizat = false;
                        break;
                    }
                }
                else break;
            }
            if (authorizat) {

                cout << "Введите пароль: ";
                cin.ignore();
                cin >> password;
                Customer use(role, username, password);
                if (use.IncludeUser(role)) {
                    string address = use.UpdateAddress();
                    cout << "Регистрация прошла успешно!" << endl;
                    system("pause");
                    if (i == 1)user = new Customer;
                    else user = new Admin;
                    user->SetUsername(username);
                    user->SetAddress(address);
                    user->Encoder(password);
                    user->Interface();
                }
                else system("pause");
            }
        }
              break;
        case 3:
            delete user;
            return 0;
        }
    }

}
