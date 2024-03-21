//
// Created by rdast on 21.03.2024.
//

#ifndef PRACTICA2_QT_MENUITEM_H
#define PRACTICA2_QT_MENUITEM_H

#include <string>
using namespace std;

class MenuItem {
private:
    string text;
    bool hidden;
    int (*func)();

public:
    MenuItem(string text, bool hidden, int (*func)()) : text(text), hidden(hidden), func(func) {}

    // getters and setters
    string getText() const;
    void setText(const string &text);

    bool isHidden() const;
    void setHidden(bool hidden);

    int (*getFunc())();
    void setFunc(int (*func)());
};

#endif //PRACTICA2_QT_MENUITEM_H
