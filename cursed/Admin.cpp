//
// Created by Shedory on 17.04.2022.
//

#include "Admin.h"

Admin::Admin(const Admin& obj) {
    username = obj.username;
    password = obj.password;
    role = obj.role;
}

//����� ��������� ������
void Admin::Interface() {
    system("chcp 1251");
    int choice;
    while (true) {
        system("cls");
        cout << "(1) - ���������\n(2) - ������������\n(3) - ����� �� ����������" << endl;
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

//�������� ��� ������ ���������� �����������
void Admin::RestaurantInterface() {
    int choice;
    while (true) {
        system("cls");
        cout
            << "(1) - ������ ����������\n(2) - ���� ���������\n(3) - �������� ��������\n(4) - ������� ��������\n(5) - ������������� ��������";
        cout << "\n(6) - ����� � ������� ����" << endl;
        choice = check::SwitchCheck(6);
        system("cls");
        switch (choice) {
        case 1:
            cout << "(1) - ������ ����������\n--------------\n";
            Restaurant::GetAllInfo();
            system("pause");
            break;
        case 2: {
            cout << "(2) - ������� ���� ���������\n--------------\n";
            Restaurant rest;
            FileFunc<Restaurant> file;
            int i = rest.RestaurantMenu(); //����� ���� ����������, ��������� �� ����������
            if (i == -1) break;
            RestaurantDishInterface(file.GetRestCustName("all", i)); //��������� ����������� ���������
        }
              break;
        case 3: {
            cout << "(3) - �������� ��������\n--------------\n";
            string type;
            string arr[3];
            cout << "������� �������� ���������: ";
            getline(cin, type, '\n');
            cout << "������� 3 ���� ���������: " << endl;
            for (int i = 0; i < 3; i++) {
                cout << '[' << i + 1 << "] : ";
                getline(cin, arr[i], '\n');
            }
            unique_ptr<Restaurant> ptr = make_unique<Restaurant>(type, arr);
            ptr->WriteInfo();
            cout << "������!" << endl;
            system("pause");
        }
              break;
        case 4: {
            cout << "(4) - ������� ��������\n--------------\n";
            int i = Restaurant::GetAllInfo();
            cout << "�������� �������� ��� ��������: ";
            i = check::SwitchCheck(i);
            FileFunc<Restaurant> file;
            file.KillFile("Restaurants\\" + file.GetRestCustName("all", i)); //�������� ����� �� ��� ��������
            file.DeleteFile("all", i - 1);
            cout << "������!" << endl;
            system("pause");
        }
              break;
        case 5: {
            cout << "(5) - ������������� ��������\n--------------\n";
            int i = Restaurant::GetAllInfo();
            cout << "�������� �������� ��� ��������������: ";
            i = check::SwitchCheck(i);
            FileFunc<Restaurant> file;
            string type;
            string arr[3];
            cout << "������� ����� �������� ���������: ";
            getline(cin, type, '\n');
            cout << "������� 3 ���� ���������: " << endl;
            for (int i = 0; i < 3; i++) {
                cout << '[' << i + 1 << "] : ";
                getline(cin, arr[i], '\n');
            }
            unique_ptr<Restaurant> restaurant = make_unique<Restaurant>(type, arr);
            FileFunc<Dish> move;
            move.MoveFile("Restaurants\\" + file.GetRestCustName("all", i), "Restaurants\\" + type);
            file.EditFile("all", *restaurant, i - 1);
            cout << "������!" << endl;
            system("pause");
        }
              break;
        case 6:
            return;

        }
    }

}

//��������� ������ � ��������������
void Admin::CustomerInterface() {
    int choice;
    FileFunc<Customer> file;
    while (true) {
        system("cls");
        cout.clear();
        cout
            << "(1) - ��� ������������\n(2) - �������� ������������\n(3) - ������� ������������\n(4) - ������������� ������������\n";
        cout << "(5) - ������ ������������\n(6) - �����" << endl;
        choice = check::SwitchCheck(6);
        system("cls");
        switch (choice) {
        case 1:
            cout << "(1) - ��� ������������\n--------------\n";
            file.ReadFile("Users");
            system("pause");
            break;
        case 2: {
            cout << "(2) - �������� ������������\n--------------\n";
            string name, pass;
            cout << "������� ���: ";
            getline(cin, name, '\n');
            if (!file.isNameExistInFile("Users", name)) {
                cout << "������� ������: ";
                getline(cin, pass, '\n');
                unique_ptr<Customer> customer = make_unique<Customer>(name, pass);
                customer->UpdateAddress();
                customer->IncludeUser("Customer");
                
                cout << "������!" << endl;
            }
            else cout << "������������ � ������ ������ ��� ����������!" << endl;
            system("pause");
        }
              break;
        case 3: {
            cout << "(3) - ������� ������������\n--------------\n";
            int i = file.ReadFile("Users");
            cout << "�������� ������������ ��� ��������: ";
            i = check::SwitchCheck(i);
            if (file.GetObj("Users", i - 1).GetRole() == "Admin") {
                cout << "������ ������� ������� ������!" << endl;
                system("pause");
                break;
            }
            string name = file.GetRestCustName("Users", i);
            file.KillFile("Receipts\\" + name + "Receipt");
            file.DeleteFile("Users", i - 1);
            cout << "������!" << endl;
            system("pause");
        }
              break;
        case 4: {
            cout << "(4) - ������������� ������������\n--------------\n";
            int i = file.ReadFile("Users");
            cout << "�������� ������������ ��� ��������������: ";
            i = check::SwitchCheck(i);
            cout << "������� ����� ���: ";
            string newname, newpass;
            getline(cin, newname, '\n');
            if (!file.isNameExistInFile("Users", newname)) {
                cout << "������� ����� ������: ";
                getline(cin, newpass, '\n');
                string role = file.GetObj("Users",
                    i - 1).GetRole(); //��������� ������ ���� ����������� ������������
                Customer obj(role, newname, newpass);
                obj.Encoder();      //���������� ������ (�����������)
                if (obj.GetRole() == "Customer") {
                    obj.UpdateAddress();
                    file.MoveFile("Receipts\\" + file.GetRestCustName("Users", i) + "Receipt",
                        "Receipts\\" + newname + "Receipt");
                    
                }
                file.EditFile("Users", obj, i - 1);
                cout << "������!" << endl;
            }
            else cout << "������������ � ������ ������ ��� ����������!" << endl;
            system("pause");
        }
              break;
        case 5: {
            cout << "(5) - ������ ������� ������������\n--------------\n";
            int i = file.ReadFile("Users");
            i = check::SwitchCheck(i);
            
            if (file.GetObj("Users", i - 1).GetRole() == "Admin") {
                cout << "������������ � ����� Admin �� ����� ����� �������!" << endl;
                system("pause");
                break;
            }
            string name = file.GetRestCustName("Users", i);
            cout << "������ ������������ " << name << ':' << endl;
            order.SetOrderName(name);
            order.GetReceipts();
        }
              break;
        case 6:
            return;
        }

    }
}

//��������� ����������� ���������
void Admin::RestaurantDishInterface(string type) {
    int choice;
    FileFunc<Dish> file;
    while (true) {
        system("cls");
        cout << "�������� " << type << endl;
        cout
            << "(1) - ����������� ����\n(2) - �������� �����\n(3) - ������� �����\n(4) - ������������� �����\n(5) - �����"
            << endl;
        choice = check::SwitchCheck(5);
        switch (choice) {
        case 1:
            system("cls");
            cout << "(1) - ���� ��������� "<<type<< "\n--------------\n";
            file.ReadFile("Restaurants\\" + type);
            system("pause");
            break;
        case 2: {
            system("cls");
            cout << "(2) - �������� ����� ��������� " << type << "\n--------------\n";
            string name, restaurant, ingredients;
            float price;
            int kkal;
            cout << "������� ���������� � �����:" << endl;
            cout << "������� �������� �����: ";
            getline(cin, name, '\n');
            cout << "������� ���� �����: ";
            price = check::Check();
            cout << "������� ������������: ";
            kkal = check::Check();
            cout << "������� ����������� �����: ";
            getline(cin, ingredients, '\n');
            unique_ptr<Dish> ptr = make_unique<Dish>(name, price, ingredients, kkal, type);
            file.WriteFile("Restaurants\\" + type, *ptr);
            cout << "������!" << endl;
            system("pause");
        }
              break;
        case 3: {
            cout << "(3) - ������� ����� ��������� " << type << "\n--------------\n";
            system("cls");
            int i = file.ReadFile("Restaurants\\" + type);
            if (i == 0) {
                cout << "���� ����!" << endl;
                system("pause");
                break;
            }
            cout << "�������� ����� ��� ��������: ";
            i = check::SwitchCheck(i);
            file.DeleteFile("Restaurants\\" + type, i - 1);
            cout << "������!" << endl;
            system("pause");
        }
              break;
        case 4: {
            system("cls");
            cout << "(4) - ������������� ����� ��������� " << type << "\n--------------\n";
            int i = file.ReadFile("Restaurants\\" + type);
            if (i == 0) {
                cout << "���� ����!" << endl;
                system("pause");
                break;
            }
            
            
            cout << "�������� ����� ��� ��������������: ";
            i = check::SwitchCheck(i);

            string name, restaurant;
            char ingredients[255];
            float price;
            int kkal;
            cout << "������� ���������� � �����:" << endl;
            cout << "������� �������� �����: ";
            getline(cin, name, '\n');
            cout << "������� ���� �����: ";
            price = check::Check();
            cout << "������� ������������: ";
            kkal = check::Check();
            cout << "������� ����������� �����: ";
            cin.getline(ingredients, 255);
            restaurant = type;
            unique_ptr<Dish> ptr = make_unique<Dish>(name, price, ingredients, kkal, type);

            file.EditFile("Restaurants\\" + type, *ptr, i - 1);
            cout << "������!" << endl;
            system("pause");
        }
              break;
        case 5:
            return;
        }

    }


}

