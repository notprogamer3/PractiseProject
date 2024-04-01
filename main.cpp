#include <iostream>
#include "src/MenuItem.h"
#include "vector"
#include "memory"
#include "fstream"
#include "boost/algorithm/string.hpp"
#include "src/Deposit.h"
#include "src/Functions.h"

using namespace std;

//
int main() {
    ofstream fout("data.txt", ios::app);
    fout.close();
    vector<MenuItem> menuItems;
    vector<shared_ptr<Deposit>> Deposits;
    DepositFunctions::TestingData(&Deposits);
    menuItems.push_back(MenuItem("Добавить вклад", false, &DepositFunctions::AddDeposit));
    menuItems.push_back(MenuItem("Сохранить в базу данных", false, &DepositFunctions::SaveData));
    menuItems.push_back(MenuItem("Загрузить из базы данных", false, &DepositFunctions::LoadData));
    menuItems.push_back(MenuItem("Вывод Данных", false, &DepositFunctions::TestingData));
    menuItems.push_back(MenuItem("Поиск", false, &DepositFunctions::Search));
    menuItems.push_back(MenuItem("Удалить", false, &DepositFunctions::Delete));
    int *skip = new int[menuItems.size()]();
    while (true) {
        for (int i = 0; i < menuItems.size(); i++) {
            if (menuItems[i].isHidden()) {
                skip[i] = 1;
            } else {
                cout << i + 1 << ". " << menuItems[i].getText() << endl;
            }
        }
        cout << "0. Выход" << endl;
        int option;
        InputIntCheck(option, 0, menuItems.size(), skip);
        if (option == 0) {
            break;
        }
        if (option > 0 && option <= menuItems.size()) {
            void (*func)(vector<shared_ptr<Deposit>> *) = menuItems[option - 1].getFunc();
            if (func != nullptr) {
                func(&Deposits);
            }
        }
    }
    return 0;
}
