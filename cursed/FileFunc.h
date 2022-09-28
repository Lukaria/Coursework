// использование шаблонов классов и методов
// использование динамического выделения памяти
// использование потоков с++, контролирования работы с потоком
#pragma once

#include <iostream>
#include <fstream>
#include <list>
#include <cstdio>
#include "Exception.h"
#include <map>
#include <string>
using namespace std;

template<class T>
class FileFunc {
private:
    static string PATH;
    fstream file;
    T obj;
    list <T> List;
protected:
    void ListFill(const string& filepath);

    void ListDelete(const string& filepath);

public:

    FileFunc() : file(PATH + ".dat") {};

    explicit FileFunc(const string& filename) : file(PATH + filename + ".dat") { file.close(); };

    bool GetList(const string& filepath, list <T>& update);

    int ReadFile(const string& filepath);

    void WriteFile(const string& filepath, T obj);

    void SortFile(const string& filepath);

    void DeleteFile(const string& filepath, int pos);

    void FilterFile(const string& filepath);

    void EditFile(const string& filepath, T obj, const int pos);

    void MoveFile(const string& filepath1, const string& filepath2);

    void KillFile(const string& filepath);

    void CommitOrder(const string& filepath1, list <T>& order);

    string GetRestCustName(const string& filepath, int pos);

    int GetPos(const string& filepath, string obj_name);

    T GetObj(const string& filepath, int pos);

    bool isExistInFile(const string& filepath, T obj);

    bool isNameExistInFile(const string& filepath, string name);
};

template<class T>
//string FileFunc<T>::PATH = "C:\\ROOT\\CLION\\cursed\\files\\";
//создание пути для всех файлов
string FileFunc<T>::PATH = "DATA\\";

//по не совсем понятным причинам компилятор не может обнаружить реализацию методов шаблонного класса
//в файле .срр, поэтому вся реализация содержится здесь

template<class T>
//заполнение списка данными из файла
void FileFunc<T>::ListFill(const string& filepath) {
    List.clear();//очистка списка на всякий случай
    file.open(PATH + filepath + ".dat", ios::app | ios::in | ios::binary);
    while (file >> obj) List.push_back(obj);
    file.close();
}

template<class T>
//заполнение файла данными из списка
void FileFunc<T>::ListDelete(const string& filepath) {
    file.open(PATH + filepath + ".dat", ios::trunc | ios::out | ios::binary);
    while (!List.empty()) {
        file << List.front();
        List.pop_front();
    }
    file.close();
}

template<class T>
//чтение данных из файла в консоль
int FileFunc<T>::ReadFile(const string& filepath) {
    ListFill(filepath);
    obj.TableInfo();
    int i = 0; //подсчет количества элементов в файле
    for (auto& elt : List) {
        cout << "------------[" << ++i << "]------------\n";
        elt.GetData();
        cout << endl;
    }
    ListDelete(filepath);
    return i;
}

template<class T>
//запись объекта в файл
void FileFunc<T>::WriteFile(const string& filepath, T obj) {
    file.open(PATH + filepath + ".dat", ios::app | ios::out | ios::binary);
    file << obj;
    file.close();
}

template<class T>
void FileFunc<T>::SortFile(const string& filepath) {
    ListFill(filepath);

    list <T> buff = List;

    int control = -1, i = 0;
    for (auto& elt : buff) if (elt.GetKkal() == control) i++; //подсчет количества заказов

    cout << "Сортировать по:\n(1) - Дате заказа\n(2) - Цене" << endl;
    if (check::SwitchCheck(2) == 1) {
        cout << "Сортировка по дате:\n(1) - По возрастанию\n(2) - По убыванию" << endl;
        if (check::SwitchCheck(2) == 1);//ничего не делаем, данные добавляются по возрастанию даты
        else {
            list <T> innerList;
            multimap<T, list < T>, less<T>>
                sorting;
            auto it = buff.begin();

            while (!buff.empty()) {
                if (it->GetKkal() != control) {
                    innerList.push_back(buff.front());
                }
                else {
                    sorting.insert(pair<T, list < T>>
                        (*it, innerList));
                    innerList.clear();
                }
                it = buff.erase(it);
            }

            for (auto elt = sorting.rbegin(); elt != sorting.rend(); ++elt/*auto& elt : sorting*/) {
                for (auto& inelt : elt->second) buff.push_back(inelt);
                buff.push_back(elt->first);
            }
        }
    }
    else {
            list <T> innerList;
            multimap<T, list < T>, greater<T>>
                sorting;
            cout << "Сортировка по общей цене заказа:\n(1) - По возрастанию\n(2) - По убыванию" << endl;
            int h = check::SwitchCheck(2);
            auto it = buff.begin();

            while (!buff.empty()) {
                if (it->GetKkal() != control) {
                    innerList.push_back(buff.front());
                }
                else {
                    sorting.insert(pair<T, list < T>>
                        (*it, innerList));
                    innerList.clear();
                }
                it = buff.erase(it);
            }

            if (h == 2) {
                for (auto& elt : sorting) {
                    for (auto& inelt : elt.second) buff.push_back(inelt);
                    buff.push_back(elt.first);
                }
            }
            else {
                for (auto elt = sorting.rbegin(); elt != sorting.rend(); ++elt/*auto& elt : sorting*/) {
                    for (auto& inelt : elt->second) buff.push_back(inelt);
                    buff.push_back(elt->first);
                }
            }
        }

    system("cls");
    //for (auto& elt : buff) if (elt.GetKkal() == -1) i++; //подсчет количества заказов
    auto it = buff.begin();
    it->TableInfo();
    while (it != buff.end()) {
        it->GetData();
        cout << endl;
        if (it->GetKkal() == -1) { //признак объекта, содержащего общую информацию о заказе
            cout << "\n(1) - Вывести следующий заказ (осталось " << --i << ")\n(2) - Выход" << endl;
            //system("pause");
            if (check::SwitchCheck(2) == 2) return;
            system("cls");
        }
        it++;
    }

    ListDelete(filepath);
}

template<class T>
//удаление объекта в файле по его позиции
void FileFunc<T>::DeleteFile(const string& filepath, int pos) { //в теории понадобится вернуть удаленный объект
    ListFill(filepath);
    auto iter = List.begin();
    for (int i = 0; i != pos; i++, iter++);
    iter = List.erase(iter);
    ListDelete(filepath);
}

template<class T>
//фильтрация данных в файле
void FileFunc<T>::FilterFile(const string& filepath) {
    ListFill(filepath);
    int i = 0, buff;
    for (auto& elt : List) if (elt.GetKkal() == -1) i++; //подсчет количества заказов
    //последний элемент заказа имеет калории == -1

    while (true) {
        system("cls");
        buff = i;
        cout << "Фильтровать по:\n(1) - Ресторану\n(2) - Цене\n(3) - Калорийности\n(4) - Выход" << endl;
        switch (check::SwitchCheck(4)) {
        case 1: {
            system("cls");
            cout << "Введите название ресторана: " << endl;
            string str;
            getline(cin, str, '\n');
            auto it = List.begin();
            bool existsInCurrentOrder = false;
            for (; it != List.end(); it++) {
                if (it->GetRestaurant() == str) {
                    existsInCurrentOrder = true;    //если подходящий элемент присутствует в заказе, переменная "запоминает" это
                    it->GetData();
                    cout << endl;
                }
                if (it->GetKkal() == -1) {
                    if (!existsInCurrentOrder)
                        cout << "В данном заказе нет позиций, подпадающих под данное условие" << endl;
                    existsInCurrentOrder = false;   //сброс для корректной проверки следующего заказа
                    cout << "(1) - Вывести следующий заказ (осталось " << --buff << ")\n(2) - Выход" << endl;
                    if (check::SwitchCheck(2) == 2) break;
                    system("cls");
                }


            }
            system("pause");
        }
              break;
        case 2: {
            system("cls");
            float less, more;
            cout << "Задайте промежуток\nОт: ";
            less = check::Check();
            cout << "До: ";
            more = check::Check();
            if (less >= more) {
                cout << "Минимальное значение [" << less << "] не может быть больше или равно максимальному ["
                    << more << "]!"
                    << endl;
                break;
            }
            bool existsInCurrentOrder = false;
            for (auto& elt : List) {
                if (elt.GetPrice() >= less && elt.GetPrice() <= more && elt.GetKkal() != -1) {
                    existsInCurrentOrder = true; //если подходящий элемент присутствует в заказе, переменная "запоминает" это
                    elt.GetData();
                    cout << endl;
                }
                if (elt.GetKkal() == -1) {
                    if (!existsInCurrentOrder)
                        cout << "В данном заказе нет позиций, подпадающих под данный промежуток" << endl;
                    existsInCurrentOrder = false;   //сброс для корректной проверки следующего заказа
                    cout << "(1) - Вывести следующий заказ (осталось " << --buff << ")\n(2) - Выход" << endl;
                    if (check::SwitchCheck(2) == 2)break;
                    system("cls");
                }
            }
        }
              break;
        case 3: {
            system("cls");
            float less, more;
            cout << "Задайте промежуток\nОт: ";
            less = check::Check();
            cout << "До: ";
            more = check::Check();
            if (less >= more) {
                cout << "Минимальное значение [" << less << "] не может быть больше или равно максимальному ["
                    << more << "]!"
                    << endl;
                break;
            }
            bool existsInCurrentOrder = false;
            cout << endl;
            for (auto& elt : List) {

                if (elt.GetKkal() >= less && elt.GetKkal() <= more && elt.GetKkal() != -1) {
                    existsInCurrentOrder = true;    //если подходящий элемент присутствует в заказе, переменная "запоминает" это
                    elt.GetData();
                    cout << endl;
                }

                if (elt.GetKkal() == -1) {
                    if (!existsInCurrentOrder)
                        cout << "В данном заказе нет позиций, подпадающих под данный промежуток" << endl;
                    existsInCurrentOrder = false; //сброс для корректной проверки следующего заказа
                    cout << "(1) - Вывести следующий заказ (осталось " << --buff << ")\n(2) - Выход"
                        << endl;
                    if (check::SwitchCheck(2) == 2) break;
                    system("cls");
                }

            }
        }
              break;
        case 4:
            ListDelete(filepath);
            return;
        }
    }

}

template<class T>
//редактирование объекта файла по позиции
void FileFunc<T>::EditFile(const string& filepath, T obj, const int pos) {
    ListFill(filepath);

    auto iter = List.begin();
    for (int i = 0; i != pos; i++, iter++);
    iter = List.erase(iter); //удаление старого объекта
    List.insert(iter, obj);//вставка нового объекта

    ListDelete(filepath);

}

template<class T>
//проверка объекта на существование в файле
bool FileFunc<T>::isExistInFile(const string& filepath, T obj) {
    ListFill(filepath);
    for (auto& elt : List) {
        if (elt == obj) {
            ListDelete(filepath); //как только объект найден, очистить список
            return true;
        }
    }
    ListDelete(filepath);
    return false;
}

template<class T>
//проверка имени объекта на существование в файле
bool FileFunc<T>::isNameExistInFile(const string& filepath, string name) {
    ListFill(filepath);
    for (auto& elt : List) {
        if (elt.GetUsername() == name) {
            ListDelete(filepath);
            return true;
        }
    }
    ListDelete(filepath);
    return false;
}

template<class T>
//получение имени объекта по позиции
string FileFunc<T>::GetRestCustName(const string& filepath, int pos) {
    //метод был нужен только для объектов Restaurant (Rest) и Customer (Cust)
    string type;
    ListFill(filepath);
    auto it = List.begin();
    type = it->GetType();
    for (int i = 0; i < pos; i++, it++) type = it->GetType();
    ListDelete(filepath);

    return type;
}

template<class T>
//изменение имени файла
void FileFunc<T>::MoveFile(const string& filepath1, const string& filepath2) {
    fstream infile;
    infile.open(PATH + filepath1 + ".dat", ios::in);
    infile.seekg(0, ios::end);
    if((int)infile.tellg() != 0){ ListFill(filepath1); }
    infile.close();//получение информации из старого файла        
    ListDelete(filepath2);  //запись информации в новый файл
    KillFile(filepath1);    //удаление старого файла
}

template<class T>
//получение объекта из файла по индексу
T FileFunc<T>::GetObj(const string& filepath, int pos) {
    ListFill(filepath);
    auto it = List.begin();
    for (int i = 0; i < pos + 1; i++, it++)
        obj = *it; //идем до позиции + 1 из-за инкрементаций (в вызове pos - 1, возвращаем это назад)
    ListDelete(filepath);
    return obj;
}

template<class T>
//получение позиции по имени объекта
int FileFunc<T>::GetPos(const string& filepath, string obj_name) {
    //нужна для получения меню ресторана (название файла с меню соответствует названию ресторана)
    //и для получения имени пользователя (название файла с заказами пользователя начинается с его имени)
    ListFill(filepath);
    auto it = List.begin();
    int pos = 0;
    for (; it != List.end(); pos++, it++) if (it->GetUsername() == obj_name) break;
    ListDelete(filepath);
    return pos;
}

template<class T>
//подтверждение заказа пользователя
void FileFunc<T>::CommitOrder(const string& filepath, list <T>& order) {
    ListFill(filepath);//получение старой информации (старых заказов)

    while (!order.empty()) {
        List.push_back(order.front());  //добавление к старым заказам новых
        order.pop_front();
    }

    ListDelete(filepath);
}

template<class T>
//получение информации из файла в виде списка
bool FileFunc<T>::GetList(const string& filepath, list <T>& update) {
    //не лучший способ, используется только в одном месте, заменить (не заменил))
    file.open(PATH + filepath + ".dat", ios::app | ios::in | ios::binary);
    while (file >> obj) List.push_back(obj);
    file.close();
    update = List;
    if (List.empty()) return false;
    return true;
}

template<class T>
//удаление файла
void FileFunc<T>::KillFile(const string& filepath) {
    remove((PATH + filepath + ".dat").c_str());
}


