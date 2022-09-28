//
// Created by Shedory on 17.04.2022.
//

#include "Customer.h"
#include "User.h"


string User::Encoder() {
    for (char& i : password) i += 1;//посимвольное кодирование
    return this->password;
}

string User::Decoder() {
    for (char& i : password) i -= 1;
    return this->password;
}

int User::Authorization(string username, string password) {
    FileFunc<Customer> file;
    password = Encoder();
    if (file.isExistInFile("Users", Customer("Customer", username, password))) {
        password = Decoder();
        return 1;
    }
    if (file.isExistInFile("Users", Customer("Admin", username, password))) {
        password = Decoder();
        return 2;
    }
    return 0;
}

//добавление пользователя
bool User::IncludeUser(string role) {
    FileFunc<Customer> file;
    password = Encoder();
    if (file.isExistInFile("Users", Customer(role, username, password))) {
        password = Decoder();
        cout << "Данный пользователь уже существует!" << endl;
        return false;
    }
    else {
        file.WriteFile("Users", Customer(role, username, password, address));
        return true;
    }
}

void User::TableInfo()
{
    cout << "Роль\tИмя\tПароль\t" << endl;
    cout << "   Адрес доставки" << endl;
}

void User::GetData() {
   /* cout << "Пользователь: " << username << endl;
    cout << "Пароль: " << Decoder() << endl;
    cout << "Роль: " << role << endl;
    if (role == "Customer")cout << "Адрес: " << address << endl;*/
    cout << role << '\t' << username << '\t' << password << "\n  " << address << endl;
}

ostream& operator<<(ostream& out, const User& obj) {
    out << "\n" << obj.role << ":" << obj.address << ';' << obj.username << endl << obj.password;
    return out;
}

istream& operator>>(istream& in, User& obj) {
    getline(in, obj.role, ':');
    if (obj.role.front() == '\r') obj.role.erase(0, 1);
    obj.role.erase(0, 1);

    getline(in, obj.address, ';');

    in >> obj.username;
    in >> obj.password;


    return in;
}

string User::UpdateAddress() {
    if (role == "Admin") return "--";
    string str = "";
    cout
        << "Выберите регион:\n(1) - Брестская область\n(2) - Витебская область\n(3) - Гомельская область\n(4) - Гродненская область";
    cout << "\n(5) - Минская область\n(6) - Могилевская область\n(7) - Минск" << endl;
    switch (check::SwitchCheck(7)) {
    case 1:
        str += "Брестская обл.";
        break;
    case 2:
        str += "Витебская обл.";
        break;
    case 3:
        str += "Гомельская обл.";
        break;
    case 4:
        str += "Гродненская обл.";
        break;
    case 5:
        str += "Минская обл.";
        break;
    case 6:
        str += "Могилевская обл.";
        break;
    case 7: {
        str += "г. Минск";
        cout << "Выберите район:\n(1) - Центральный\n(2) - Советский\n(3) - Первомайский\n(4) - Партизанский";
        cout << "\n(5) - Заводской\n(6) - Ленинский\n(7) - Октябрьский\n(8) - Московский\n(9) - Фрунзенский"
            << endl;
        switch (check::SwitchCheck(9)) {
        case 1:
            str += ", Центральный р-н";
            break;
        case 2: {
            str += ", Советский р-н";
            cout << "Выберите улицу:\n(1) - Амурская\n(2) -Усадебная\n(3) - Скорины\n(4) - Тургенева";
            cout << "\n(5) - Мележа\n(6) - Гало" << endl;
            switch (check::SwitchCheck(6)) {
            case 1:
                str += ", Амурская ул.";
                break;
            case 2:
                str += ", Усадебная ул.";
                break;
            case 3:
                str += ", ул. Скорины";
                break;
            case 4:
                str += ", ул. Тургенева";
                break;
            case 5:
                str += ", ул. Мележа";
                break;
            case 6:
                str += ", ул. Гало";
                break;
            }

        }
              break;
        case 3:
            str += ", Первомайский р-н";
            break;
        case 4:
            str += ", Партизанский р-н";
            break;
        case 5:
            str += ", Заводской р-н";
            break;
        case 6:
            str += ", Ленинский р-н";
            break;
        case 7:
            str += ", Октябрьский р-н";
            break;
        case 8:
            str += ", Московский р-н";
            break;
        case 9:
            str += ", Фрунзенский р-н";
            break;

        }
    }
          break;
    }

    cout << "Введите номер дома: ";
    int number = check::Check();
    str += ", д." + to_string(number);
    this->address = str;
    return address;
}



User::User(string role, string username, string password, string address) {
    this->role = role;
    this->username = username;
    this->password = password;
    this->address = address;


}

string User::Encoder(string str) {
    for (char& i : str) i += 0;//посимвольное кодирование
    this->password = str;
    return this->password;
}
