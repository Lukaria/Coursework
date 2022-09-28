//
// Created by Shedory on 19.04.2022.
//

#include "Order.h"

void Order::GetOrder() {
    std::list<Dish>::iterator it;
    int choice;
    int i;
    if (receipt.empty()) {
        cout << "����� ���� �����..." << endl;
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
        cout << "����� ���������: " << totalmoney << endl;
        //cout << "����� ������: " << UpdateTime() << endl;
        cout << "-------------------------------" << endl;
        system("pause");
        cout << "(1) - ������� �������\n(2) - �����������\n(3) - �������� �����\n(4) - �����"
            << endl;
        choice = check::SwitchCheck(4);
        switch (choice) {
        case 1:
            if (receipt.empty()) {
                cout << "����� ����!" << endl;
                break;
            }
            cout << "������� ����� �������: ";
            i = check::SwitchCheck(i);
            it = receipt.begin();
            for (int j = 0; j < i - 1; j++, it++);
            totalmoney -= it->GetPrice();
            it = receipt.erase(it);
            cout << "������!" << endl;
            system("pause");
            break;
        case 2: {
            cout << "����������� ��:\n(1) - ����������� ����\n(2) - �������� ����" << endl;
            if (check::SwitchCheck(2) == 1)
                receipt.sort([](const Dish& obj1, const Dish& obj2) { return obj1.GetPrice() < obj2.GetPrice(); });
            else
                receipt.sort([](const Dish& obj1, const Dish& obj2) { return obj1.GetPrice() >= obj2.GetPrice(); });
            cout << "������!" << endl;
            system("cls");
        }
              break;
        case 3: {
            if (receipt.empty()) {
                cout << "����� ����!" << endl;
                break;
            }
            cout << "���� ������: " << totalmoney << endl;
            cout << "�������� �����? (1) - �� (2) - ���" << endl;
            if (check::SwitchCheck(2) == 1) {
                Push(Dish(totalmoney,
                    UpdateTime(), address));//������ ����� ���� � ������� ���������� ��� ����� ������� Dish

                file.CommitOrder("Receipts\\" + username + "Receipt", receipt);
                cout << "����� ������� ��������!" << endl;
                cout << "�� ������ ����������� ��� � ����� �������" << endl;
                totalmoney = 0;
                receipt.clear();
                system("pause");
                return;
            }
            else cout << "���������� ��������" << endl;
            system("pause");
        }
              break;
        case 4:
            return;
        }
    }

}

//���������� � �������
void Order::Push(Dish dish) {
    receipt.push_back(dish);
    totalmoney += dish.GetPrice();
}

void Order::GetReceipts() {
    FileFunc<Dish> file;
    list<Dish> buff;
    if (!file.GetList("Receipts\\" + username + "Receipt", buff)) {
        cout << "��� ����������� �������!" << endl;
        system("pause");
    }
    else {
        while (true) {
            system("cls");
            cout << "������ " << username << endl;
            cout << "(1) - ������� ��� ������\n(2) - �����������\n(3) - �����������\n(4) - �����" << endl;
            switch (check::SwitchCheck(4)) {
            case 1: {
                system("cls");
                int i = 0;
                for (auto& elt : buff) if (elt.GetKkal() == -1) i++; //������� ���������� �������
                auto it = buff.begin();
                while (it != buff.end()) {
                    it->GetData();
                    cout << endl;
                    if (it->GetKkal() == -1) { //������� �������, ����������� ����� ���������� � ������
                        cout << "\n(1) - ������� ��������� ����� (�������� " << --i << ")\n(2) - �����" << endl;
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

//���������� �������
string Order::UpdateTime() {
    time_t currentTime = time(nullptr);
    datetime = asctime(localtime(&currentTime));
    datetime.pop_back();
    return datetime;
    //return "today";
};


