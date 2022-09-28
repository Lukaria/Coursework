//
// Created by Shedory on 17.04.2022.
//

#include "Customer.h"
#include "User.h"


string User::Encoder() {
    for (char& i : password) i += 1;//������������ �����������
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

//���������� ������������
bool User::IncludeUser(string role) {
    FileFunc<Customer> file;
    password = Encoder();
    if (file.isExistInFile("Users", Customer(role, username, password))) {
        password = Decoder();
        cout << "������ ������������ ��� ����������!" << endl;
        return false;
    }
    else {
        file.WriteFile("Users", Customer(role, username, password, address));
        return true;
    }
}

void User::TableInfo()
{
    cout << "����\t���\t������\t" << endl;
    cout << "   ����� ��������" << endl;
}

void User::GetData() {
   /* cout << "������������: " << username << endl;
    cout << "������: " << Decoder() << endl;
    cout << "����: " << role << endl;
    if (role == "Customer")cout << "�����: " << address << endl;*/
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
        << "�������� ������:\n(1) - ��������� �������\n(2) - ��������� �������\n(3) - ���������� �������\n(4) - ����������� �������";
    cout << "\n(5) - ������� �������\n(6) - ����������� �������\n(7) - �����" << endl;
    switch (check::SwitchCheck(7)) {
    case 1:
        str += "��������� ���.";
        break;
    case 2:
        str += "��������� ���.";
        break;
    case 3:
        str += "���������� ���.";
        break;
    case 4:
        str += "����������� ���.";
        break;
    case 5:
        str += "������� ���.";
        break;
    case 6:
        str += "����������� ���.";
        break;
    case 7: {
        str += "�. �����";
        cout << "�������� �����:\n(1) - �����������\n(2) - ���������\n(3) - ������������\n(4) - ������������";
        cout << "\n(5) - ���������\n(6) - ���������\n(7) - �����������\n(8) - ����������\n(9) - �����������"
            << endl;
        switch (check::SwitchCheck(9)) {
        case 1:
            str += ", ����������� �-�";
            break;
        case 2: {
            str += ", ��������� �-�";
            cout << "�������� �����:\n(1) - ��������\n(2) -���������\n(3) - �������\n(4) - ���������";
            cout << "\n(5) - ������\n(6) - ����" << endl;
            switch (check::SwitchCheck(6)) {
            case 1:
                str += ", �������� ��.";
                break;
            case 2:
                str += ", ��������� ��.";
                break;
            case 3:
                str += ", ��. �������";
                break;
            case 4:
                str += ", ��. ���������";
                break;
            case 5:
                str += ", ��. ������";
                break;
            case 6:
                str += ", ��. ����";
                break;
            }

        }
              break;
        case 3:
            str += ", ������������ �-�";
            break;
        case 4:
            str += ", ������������ �-�";
            break;
        case 5:
            str += ", ��������� �-�";
            break;
        case 6:
            str += ", ��������� �-�";
            break;
        case 7:
            str += ", ����������� �-�";
            break;
        case 8:
            str += ", ���������� �-�";
            break;
        case 9:
            str += ", ����������� �-�";
            break;

        }
    }
          break;
    }

    cout << "������� ����� ����: ";
    int number = check::Check();
    str += ", �." + to_string(number);
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
    for (char& i : str) i += 0;//������������ �����������
    this->password = str;
    return this->password;
}
