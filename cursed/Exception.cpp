//
// Created by Shedory on 03.05.2022.
//
#include "Exception.h"

using namespace check;

//���������� ��� ������ � ���� (����� ����������� �� ����)
int check::SwitchCheck(int limit) {
    float input;
    while (true) {
        try {
            std::cin >> input;
            if (input < 1 || input > limit) {
                std::cin.clear(/*std::ios::failbit*/);
                throw limit;
            }
            if (std::cin.good()) {
                std::cin.ignore(32767, '\n');
                break;
            }
            else throw ">>������������ ���� ������!\n";
        }
        catch (const char* str) {
            std::cerr << str;
            std::cin.ignore(32767, '\n');
        }
        catch (int a) {
            std::cerr << ">>������������ ���� ������! ����� ������ ��������� � ��������� �� 1 �� " << a << std::endl;
            std::cin.ignore(32767, '\n');
        }
    }

    return input;

}

//���������� ��� ����� �������� �������� (�� ����� ��������� �����������)
float check::Check() {
    float input;
    while (true) {
        try {
            std::cin >> input;
            if (input < 1) {
                std::cin.clear(/*std::ios::failbit*/);
                throw ">>������������ ���� ������!\n";
            }
            if (std::cin.good()) {
                std::cin.ignore(32767, '\n');
                break;
            }
            else throw ">>������������ ���� ������!\n";
        }
        catch (const char* str) {
            std::cerr << str;
            std::cin.ignore(32767, '\n');
        }
    }

    return input;

}
