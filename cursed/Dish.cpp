//
// Created by Shedory on 16.04.2022.
//

#include "Dish.h"

void Dish::SetPrice(float price) { this->price = price; }

float Dish::GetPrice() const { return price; }

void Dish::SetKkal(int kkal) { this->kkal = kkal; }

int Dish::GetKkal() { return kkal; }

void Dish::SetIngredients() {
    cin.ignore();
    cin >> ingredients;
}

string Dish::GetIngredients() {
    return ingredients;
}

void Dish::TableInfo()
{
    cout << "�������� �����\t" << "����\t" << "������������";
    cout << "\n�����������" << endl;
}

//��������� ������
void Dish::GetData() {
    if (kkal == -1) { //� ������ kkal == -1 (������� ��_�����) ����� ����������
        cout << "#######################" << endl;
        cout << "����� ����: " << price << endl;
        cout << "���� ������: " << ingredients << endl;
        cout << "����� ��������: " << restaurant << endl;
        cout << "#######################" << endl;
    }
    else {
        /*cout << type << endl;
        cout << "����: " << price << endl;
        cout << "�����������: " << ingredients << endl;
        cout << "������������: " << kkal << endl;*/
        cout << type << '\t' << price << '\t' << kkal << endl;
        cout << ingredients << endl;
    }

}

Dish::Dish(const Dish& obj) {
    this->type = obj.type;
    this->price = obj.price;
    this->ingredients = obj.ingredients;
    //strcpy(this->ingredients, obj.ingredients);
    this->kkal = obj.kkal;
    this->restaurant = obj.restaurant;
}

istream& operator>>(istream& stream, Dish& obj) {
    getline(stream, obj.type, ':');
    while(obj.type[0] == '\n' || obj.type[0] == '\r') obj.type.erase(0, 1);
    getline(stream, obj.ingredients, ';');
    getline(stream, obj.restaurant, ';');
    stream >> obj.price >> obj.kkal;
    return stream;
}

ostream& operator<<(ostream& stream, Dish& obj) {
    stream << "\n" << obj.type << ":" << obj.ingredients << ";" << obj.restaurant << ";" << obj.price << endl
        << obj.kkal;
    return stream;
}




