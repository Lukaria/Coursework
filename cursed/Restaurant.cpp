//
// Created by Shedory on 04.04.2022.
//

#include "Restaurant.h"

Restaurant::Restaurant(string type, string* arr) {
    this->type = type;
    for (int i = 0; i < 3; i++) tags[i] = arr[i];
}

void Restaurant::WriteInfo() {
    if (type == "N/A") return;
    FileFunc<Restaurant> file;
    file.WriteFile("all", *this);
}

int Restaurant::GetAllInfo() {
    FileFunc<Restaurant> file;
    return file.ReadFile("all");
}

/*void Restaurant::AddDish(Dish dish) {
    dish.SetRestaurant(type);
    FileFunc<Dish> file;
    file.WriteFile(this->type, dish);
}

void Restaurant::DeleteDish(const int pos) {
    FileFunc<Dish> file;
    file.DeleteFile(this->type, pos);
}

void Restaurant::EditDish(Dish dish, const int pos) {
    FileFunc<Dish> file;
    file.EditFile(type, dish, pos);
}
 */

 //����� ���� ����������
int Restaurant::RestaurantMenu() {
    //cout << "������ ����������:" << endl;
    //cout << "-------------------" << endl;
    int i = GetAllInfo(), input;
    cout << '(' << i + 1 << ')' << " - ����� � ������� ����" << endl;
    cout << '(' << i + 2 << ')' << " - ����� �� ����������" << endl;
    input = check::SwitchCheck(i + 2); //��������� ������ ������������
    if (input <= i) return input;
    else if (input == i + 1) return -1;
    else exit(0);

}

//��������� ���� ���������
int Restaurant::GetRestaurantMenu(int pos) {
    FileFunc<Restaurant> file;
    FileFunc<Dish> infile;
    int input;
    int i;
    string str = file.GetRestCustName("all", pos); //��������� �������� ��������� �� ��� ������� (������� ������ ������������)
    while (true) {
        system("cls");
        cout << "���� ��������� " << str << endl;
        cout << "----------------" << endl;
        i = infile.ReadFile("Restaurants\\" + str);

        cout << '(' << i + 1 << ')' << " - ����� � ���� ����������" << endl;
        cout << '(' << i + 2 << ')' << " - ����� �� ����������" << endl;
        input = check::SwitchCheck(i + 2);
        if (input <= i) {
            string astr = infile.GetRestCustName("Restaurants\\" + str, input);
            cout << "�������� " << astr << " � �����?\n(1) - ��\n(2) - ���" << endl;
            i = check::SwitchCheck(2);
            if (i == 1) {
                return input;
            }
        }
        else if (input == i + 1) return -1;
        else exit(0);
    }
}

void Restaurant::TableInfo()
{
    cout <<"        ��� ���������\n";
    cout << "\t   ����\n";
}

void Restaurant::GetData() {
    cout <<"\t" << type << endl;
    cout << "[" << tags[0] << ", " << tags[1] << ", " << tags[2] << "]" << endl;
    
}

ostream& operator<<(ostream& out, const Restaurant& obj) {
    out << '\n' << obj.type << ":" << obj.tags[0] << ";" << obj.tags[1] << ";" << obj.tags[2] << ";";

    return out;
}

istream& operator>>(istream& in, Restaurant& obj) {
    getline(in, obj.type, ':');
    if (obj.type != "") {
        if (obj.type.front() == '\r') obj.type.erase(0, 1);
        obj.type.erase(0, 1);
        for (auto& elt : obj.tags) getline(in, elt, ';');
    }
    return in;
}