//
// Created by rdast on 21.03.2024.
//

#ifndef PRACTICA2_QT_MENUITEM_H
#define PRACTICA2_QT_MENUITEM_H

#include <string>
#include "Deposit.h"
#include "memory"
#include "vector"


using namespace std;

class MenuItem {
private:
    string text;
    bool hidden;
    void (*func)(vector<shared_ptr<Deposit>> Deps);

public:
    MenuItem(string text, bool hidden, void (*func)(vector<shared_ptr<Deposit>>)) : text(text), hidden(hidden), func(func) {}

    // getters and setters
    string getText() const;
    void setText(const string &text);

    bool isHidden() const;
    void setHidden(bool hidden);

    void (*getFunc())(vector<shared_ptr<Deposit>>);
    void setFunc(void (*func)(vector<shared_ptr<Deposit>>));
};

#endif //PRACTICA2_QT_MENUITEM_H
