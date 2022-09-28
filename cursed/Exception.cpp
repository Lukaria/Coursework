//
// Created by Shedory on 03.05.2022.
//
#include "Exception.h"

using namespace check;

//исключение для выбора в меню (имеет ограничение на ввод)
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
            else throw ">>Неправильный ввод данных!\n";
        }
        catch (const char* str) {
            std::cerr << str;
            std::cin.ignore(32767, '\n');
        }
        catch (int a) {
            std::cerr << ">>Неправильный ввод данных! число должно находится в диапазоне от 1 до " << a << std::endl;
            std::cin.ignore(32767, '\n');
        }
    }

    return input;

}

//исключение для ввода числовых значений (не имеет заданного ограничения)
float check::Check() {
    float input;
    while (true) {
        try {
            std::cin >> input;
            if (input < 1) {
                std::cin.clear(/*std::ios::failbit*/);
                throw ">>Неправильный ввод данных!\n";
            }
            if (std::cin.good()) {
                std::cin.ignore(32767, '\n');
                break;
            }
            else throw ">>Неправильный ввод данных!\n";
        }
        catch (const char* str) {
            std::cerr << str;
            std::cin.ignore(32767, '\n');
        }
    }

    return input;

}
