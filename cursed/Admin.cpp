//
// Created by Shedory on 17.04.2022.
//

#include "Admin.h"

Admin::Admin(const Admin& obj) {
    username = obj.username;
    password = obj.password;
    role = obj.role;
}

//общий интерфейс админа
void Admin::Interface() {
    system("chcp 1251");
    int choice;
    while (true) {
        system("cls");
        cout << "(1) - Рестораны\n(2) - Пользователи\n(3) - Выход из приложения" << endl;
        choice = check::SwitchCheck(3);
        switch (choice) {
        case 1:
            system("cls");
            Admin::RestaurantInterface();
            break;
        case 2:
            Admin::CustomerInterface();
            break;
        case 3:
            exit(0);
        }
    }
}

//инерфейс для общего управления ресторанами
void Admin::RestaurantInterface() {
    int choice;
    while (true) {
        system("cls");
        cout
            << "(1) - Список ресторанов\n(2) - Меню ресторана\n(3) - Добавить ресторан\n(4) - Удалить ресторан\n(5) - Редактировать ресторан";
        cout << "\n(6) - Выход в главное меню" << endl;
        choice = check::SwitchCheck(6);
        system("cls");
        switch (choice) {
        case 1:
            cout << "(1) - Список ресторанов\n--------------\n";
            Restaurant::GetAllInfo();
            system("pause");
            break;
        case 2: {
            cout << "(2) - Открыть меню ресторана\n--------------\n";
            Restaurant rest;
            FileFunc<Restaurant> file;
            int i = rest.RestaurantMenu(); //вывод всех ресторанов, получение их количества
            if (i == -1) break;
            RestaurantDishInterface(file.GetRestCustName("all", i)); //интерфейс конкретного ресторана
        }
              break;
        case 3: {
            cout << "(3) - Добавить ресторан\n--------------\n";
            string type;
            string arr[3];
            cout << "Введите название ресторана: ";
            getline(cin, type, '\n');
            cout << "Введите 3 тега ресторана: " << endl;
            for (int i = 0; i < 3; i++) {
                cout << '[' << i + 1 << "] : ";
                getline(cin, arr[i], '\n');
            }
            unique_ptr<Restaurant> ptr = make_unique<Restaurant>(type, arr);
            ptr->WriteInfo();
            cout << "Готово!" << endl;
            system("pause");
        }
              break;
        case 4: {
            cout << "(4) - Удалить ресторан\n--------------\n";
            int i = Restaurant::GetAllInfo();
            cout << "Выберите ресторан для удаления: ";
            i = check::SwitchCheck(i);
            FileFunc<Restaurant> file;
            file.KillFile("Restaurants\\" + file.GetRestCustName("all", i)); //удаление файла по его названию
            file.DeleteFile("all", i - 1);
            cout << "Готово!" << endl;
            system("pause");
        }
              break;
        case 5: {
            cout << "(5) - Редактировать ресторан\n--------------\n";
            int i = Restaurant::GetAllInfo();
            cout << "Выберите ресторан для редактирования: ";
            i = check::SwitchCheck(i);
            FileFunc<Restaurant> file;
            string type;
            string arr[3];
            cout << "Введите новое название ресторана: ";
            getline(cin, type, '\n');
            cout << "Введите 3 тега ресторана: " << endl;
            for (int i = 0; i < 3; i++) {
                cout << '[' << i + 1 << "] : ";
                getline(cin, arr[i], '\n');
            }
            unique_ptr<Restaurant> restaurant = make_unique<Restaurant>(type, arr);
            FileFunc<Dish> move;
            move.MoveFile("Restaurants\\" + file.GetRestCustName("all", i), "Restaurants\\" + type);
            file.EditFile("all", *restaurant, i - 1);
            cout << "Готово!" << endl;
            system("pause");
        }
              break;
        case 6:
            return;

        }
    }

}

//интерфейс работы с пользователями
void Admin::CustomerInterface() {
    int choice;
    FileFunc<Customer> file;
    while (true) {
        system("cls");
        cout.clear();
        cout
            << "(1) - Все пользователи\n(2) - Добавить пользователя\n(3) - Удалить пользователя\n(4) - Редактировать пользователя\n";
        cout << "(5) - Заказы пользователя\n(6) - Выход" << endl;
        choice = check::SwitchCheck(6);
        system("cls");
        switch (choice) {
        case 1:
            cout << "(1) - Все пользователи\n--------------\n";
            file.ReadFile("Users");
            system("pause");
            break;
        case 2: {
            cout << "(2) - Добавить пользователя\n--------------\n";
            string name, pass;
            cout << "Введите имя: ";
            getline(cin, name, '\n');
            if (!file.isNameExistInFile("Users", name)) {
                cout << "Введите пароль: ";
                getline(cin, pass, '\n');
                unique_ptr<Customer> customer = make_unique<Customer>(name, pass);
                customer->UpdateAddress();
                customer->IncludeUser("Customer");
                
                cout << "Готово!" << endl;
            }
            else cout << "Пользователь с данным именем уже существует!" << endl;
            system("pause");
        }
              break;
        case 3: {
            cout << "(3) - Удалить пользователя\n--------------\n";
            int i = file.ReadFile("Users");
            cout << "Выберите пользователя для удаления: ";
            i = check::SwitchCheck(i);
            if (file.GetObj("Users", i - 1).GetRole() == "Admin") {
                cout << "Нельзя удалить аккаунт админа!" << endl;
                system("pause");
                break;
            }
            string name = file.GetRestCustName("Users", i);
            file.KillFile("Receipts\\" + name + "Receipt");
            file.DeleteFile("Users", i - 1);
            cout << "Готово!" << endl;
            system("pause");
        }
              break;
        case 4: {
            cout << "(4) - Редактировать пользователя\n--------------\n";
            int i = file.ReadFile("Users");
            cout << "Выберите пользователя для редактирования: ";
            i = check::SwitchCheck(i);
            cout << "Введите новое имя: ";
            string newname, newpass;
            getline(cin, newname, '\n');
            if (!file.isNameExistInFile("Users", newname)) {
                cout << "Введите новый пароль: ";
                getline(cin, newpass, '\n');
                string role = file.GetObj("Users",
                    i - 1).GetRole(); //получение старой роли изменяемого пользователя
                Customer obj(role, newname, newpass);
                obj.Encoder();      //обновление пароля (кодирование)
                if (obj.GetRole() == "Customer") {
                    obj.UpdateAddress();
                    file.MoveFile("Receipts\\" + file.GetRestCustName("Users", i) + "Receipt",
                        "Receipts\\" + newname + "Receipt");
                    
                }
                file.EditFile("Users", obj, i - 1);
                cout << "Готово!" << endl;
            }
            else cout << "Пользователь с данным именем уже существует!" << endl;
            system("pause");
        }
              break;
        case 5: {
            cout << "(5) - Список заказов пользователя\n--------------\n";
            int i = file.ReadFile("Users");
            i = check::SwitchCheck(i);
            
            if (file.GetObj("Users", i - 1).GetRole() == "Admin") {
                cout << "Пользователь с ролью Admin не может иметь заказов!" << endl;
                system("pause");
                break;
            }
            string name = file.GetRestCustName("Users", i);
            cout << "Заказы пользователя " << name << ':' << endl;
            order.SetOrderName(name);
            order.GetReceipts();
        }
              break;
        case 6:
            return;
        }

    }
}

//интерфейс конкретного ресторана
void Admin::RestaurantDishInterface(string type) {
    int choice;
    FileFunc<Dish> file;
    while (true) {
        system("cls");
        cout << "Ресторан " << type << endl;
        cout
            << "(1) - Просмотреть меню\n(2) - Добавить блюдо\n(3) - Удалить блюдо\n(4) - Редактировать блюдо\n(5) - Выход"
            << endl;
        choice = check::SwitchCheck(5);
        switch (choice) {
        case 1:
            system("cls");
            cout << "(1) - Меню ресторана "<<type<< "\n--------------\n";
            file.ReadFile("Restaurants\\" + type);
            system("pause");
            break;
        case 2: {
            system("cls");
            cout << "(2) - Добавить блюдо ресторана " << type << "\n--------------\n";
            string name, restaurant, ingredients;
            float price;
            int kkal;
            cout << "Введите информацию о блюде:" << endl;
            cout << "Введите название блюда: ";
            getline(cin, name, '\n');
            cout << "Введите цену блюда: ";
            price = check::Check();
            cout << "Введите калорийность: ";
            kkal = check::Check();
            cout << "Введите ингредиенты блюда: ";
            getline(cin, ingredients, '\n');
            unique_ptr<Dish> ptr = make_unique<Dish>(name, price, ingredients, kkal, type);
            file.WriteFile("Restaurants\\" + type, *ptr);
            cout << "Готово!" << endl;
            system("pause");
        }
              break;
        case 3: {
            cout << "(3) - Удалить блюдо ресторана " << type << "\n--------------\n";
            system("cls");
            int i = file.ReadFile("Restaurants\\" + type);
            if (i == 0) {
                cout << "Файл пуст!" << endl;
                system("pause");
                break;
            }
            cout << "Выберите блюдо для удаления: ";
            i = check::SwitchCheck(i);
            file.DeleteFile("Restaurants\\" + type, i - 1);
            cout << "Готово!" << endl;
            system("pause");
        }
              break;
        case 4: {
            system("cls");
            cout << "(4) - Редактировать блюдо ресторана " << type << "\n--------------\n";
            int i = file.ReadFile("Restaurants\\" + type);
            if (i == 0) {
                cout << "Файл пуст!" << endl;
                system("pause");
                break;
            }
            
            
            cout << "Выберите блюдо для редактирования: ";
            i = check::SwitchCheck(i);

            string name, restaurant;
            char ingredients[255];
            float price;
            int kkal;
            cout << "Введите информацию о блюде:" << endl;
            cout << "Введите название блюда: ";
            getline(cin, name, '\n');
            cout << "Введите цену блюда: ";
            price = check::Check();
            cout << "Введите калорийность: ";
            kkal = check::Check();
            cout << "Введите ингредиенты блюда: ";
            cin.getline(ingredients, 255);
            restaurant = type;
            unique_ptr<Dish> ptr = make_unique<Dish>(name, price, ingredients, kkal, type);

            file.EditFile("Restaurants\\" + type, *ptr, i - 1);
            cout << "Готово!" << endl;
            system("pause");
        }
              break;
        case 5:
            return;
        }

    }


}

