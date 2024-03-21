#include <iostream>
#include "Data/MenuItem.h"
#include "vector"

using namespace std;


void InputIntCheck(int &Number, int left = 0, int right = 0) {
    string test;
    while (true) {
        cin >> test;
        if (test.find_first_not_of("0123456789") != string::npos) {
            cout << "Invalid input. Please enter a number." << endl;
            continue;
        } else {
            Number = stoi(test);
            if (Number < left || Number > right) {
                cout << "Invalid input. Please enter a number between " << left << " and " << right << "." << endl;
                continue;
            }
            break;
        }

    }
}


int main() {
    vector<MenuItem> menuItems;
    menuItems.push_back(MenuItem("Item 1", false, nullptr));
    menuItems.push_back(MenuItem("Item 2", false, nullptr));
    menuItems.push_back(MenuItem("Item 3", false, nullptr));
    menuItems.push_back(MenuItem("Item 4", false, nullptr));
    while (true) {
        for (int i = 0; i < menuItems.size(); i++) {
            cout << i + 1 << ". " << menuItems[i].getText() << endl;
        }
        cout << "0. Exit" << endl;
        int option;
        InputIntCheck(option, 0, menuItems.size());
        if (option == 0) {
            break;
        }
        if (option > 0 && option <= menuItems.size()) {
            int (*func)() = menuItems[option - 1].getFunc();
            if (func != nullptr) {
                func();
            }
        }
    }
    return 0;
}
