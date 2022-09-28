//
// Created by Shedory on 19.04.2022.
//

#include "Order.h"

void Order::GetOrder() {
    std::list<Dish>::iterator it;
    int choice;
    int i;
    if (receipt.empty()) {
        cout << "Здесь пока пусто..." << endl;
        system("pause");
        return;
    }
    while (true) {
        system("cls");
        FileFunc<Dish> file;
        //i = file.ReadFile(username + "Order");
        int i = 1;
        receipt.front().TableInfo();
        for (auto& elt : receipt) {
            cout << '[' << i++ << ']' << endl;
            elt.GetData();
            cout << endl;
        }
        cout << "-------------------------------" << endl;
        cout << "Общая стоимость: " << totalmoney << endl;
        //cout << "Время заказа: " << UpdateTime() << endl;
        cout << "-------------------------------" << endl;
        system("pause");
        cout << "(1) - Удалить позицию\n(2) - Сортировать\n(3) - Оформить заказ\n(4) - Выход"
            << endl;
        choice = check::SwitchCheck(4);
        switch (choice) {
        case 1:
            if (receipt.empty()) {
                cout << "Заказ пуст!" << endl;
                break;
            }
            cout << "Введите номер позиции: ";
            i = check::SwitchCheck(i);
            it = receipt.begin();
            for (int j = 0; j < i - 1; j++, it++);
            totalmoney -= it->GetPrice();
            it = receipt.erase(it);
            cout << "Готово!" << endl;
            system("pause");
            break;
        case 2: {
            cout << "Сортировать по:\n(1) - Возрастанию цены\n(2) - Убыванию цены" << endl;
            if (check::SwitchCheck(2) == 1)
                receipt.sort([](const Dish& obj1, const Dish& obj2) { return obj1.GetPrice() < obj2.GetPrice(); });
            else
                receipt.sort([](const Dish& obj1, const Dish& obj2) { return obj1.GetPrice() >= obj2.GetPrice(); });
            cout << "Готово!" << endl;
            system("cls");
        }
              break;
        case 3: {
            if (receipt.empty()) {
                cout << "Заказ пуст!" << endl;
                break;
            }
            cout << "Цена заказа: " << totalmoney << endl;
            cout << "Оформить заказ? (1) - Да (2) - Нет" << endl;
            if (check::SwitchCheck(2) == 1) {
                Push(Dish(totalmoney,
                    UpdateTime(), address));//запись общей цены и времени оформления под видом объекта Dish

                file.CommitOrder("Receipts\\" + username + "Receipt", receipt);
                cout << "Заказ успешно оформлен!" << endl;
                cout << "Вы можете просмотреть чек в своем профиле" << endl;
                totalmoney = 0;
                receipt.clear();
                system("pause");
                return;
            }
            else cout << "Оформление отменено" << endl;
            system("pause");
        }
              break;
        case 4:
            return;
        }
    }

}

//добавление в корзину
void Order::Push(Dish dish) {
    receipt.push_back(dish);
    totalmoney += dish.GetPrice();
}

void Order::GetReceipts() {
    FileFunc<Dish> file;
    list<Dish> buff;
    if (!file.GetList("Receipts\\" + username + "Receipt", buff)) {
        cout << "Нет оформленных заказов!" << endl;
        system("pause");
    }
    else {
        while (true) {
            system("cls");
            cout << "Заказы " << username << endl;
            cout << "(1) - Вывести все заказы\n(2) - Сортировать\n(3) - Фильтровать\n(4) - Выход" << endl;
            switch (check::SwitchCheck(4)) {
            case 1: {
                system("cls");
                int i = 0;
                for (auto& elt : buff) if (elt.GetKkal() == -1) i++; //подсчет количества заказов
                auto it = buff.begin();
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
            }
                  break;
            case 2:
                file.SortFile("Receipts\\" + username + "Receipt");
                break;
            case 3:
                file.FilterFile("Receipts\\" + username + "Receipt");
                break;
            case 4:
                return;
            }
        }

    }
}

//обновление времени
string Order::UpdateTime() {
    time_t currentTime = time(nullptr);
    datetime = asctime(localtime(&currentTime));
    datetime.pop_back();
    return datetime;
    //return "today";
};


