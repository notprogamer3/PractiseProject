#include <iostream>
#include "src/MenuItem.h"
#include "vector"
#include "src/Deposit.h"
#include "src/Functions.h"

using namespace std;


//TODO By priority:
//TODO optimize shit in MenuItem.h since it looks ass but adding now working (maybe use typedef?????)
//TODO add adding in and out file operations (<< and >>) in class decloration since it is nedded
//TODO add search
//TODO Delete
//TODO make a table print
//TODO check int works bad if left=0 and right=1


int main() {
    vector<MenuItem> menuItems;
    vector<shared_ptr<Deposit>> Deposits;
    menuItems.push_back(MenuItem("Добавить вклад", false, &DepositFunctions::AddDeposit));
    int *skip = new int[menuItems.size()]();
    while (true) {
        for (int i = 0; i < menuItems.size(); i++) {
            if (menuItems[i].isHidden()) {
                skip[i] = 1;
            } else {
                cout << i + 1 << ". " << menuItems[i].getText() << endl;
            }
        }
        cout << "0. Exit" << endl;
        int option;
        InputIntCheck(option, 0, menuItems.size(), skip);
        if (option == 0) {
            break;
        }
        if (option > 0 && option <= menuItems.size()) {
            void (*func)(vector<shared_ptr<Deposit>>*) = menuItems[option - 1].getFunc();
            if (func != nullptr) {
                func(&Deposits);
            }
        }
    }
    return 0;
}
