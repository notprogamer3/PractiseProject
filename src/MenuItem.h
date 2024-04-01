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

//--------------------------------------------------------
//MenuItem
//Класс являющейся единицей меню.

class MenuItem {
private:
    string text; // Навзание пункта
    bool hidden; // спрятан ли пункт

    typedef void (*Func)(vector<shared_ptr<Deposit>> *); //Определение макроса для указателя на функцию
    Func func; // Указатель на функцию где происходит работа с данными

public:



    // Конструктор с параметрами инициализации: text, hidden, func
    MenuItem(string text, bool hidden, void (*func)(vector<shared_ptr<Deposit>> *)) : text(text), hidden(hidden),
                                                                                      func(func) {}


     // получить наименование пункта
    string getText() const;

    // установить наименование пункта
    void setText(const string &text);

    // получить статус видимости пункта
    bool isHidden() const;

    // установить статус видимости пункта
    void setHidden(bool hidden);

    // получить указатель на функцию пункта
    void (*getFunc())(vector<shared_ptr<Deposit>> *);

    // установить указатель на функцию пункта
    void setFunc(void (*func)(vector<shared_ptr<Deposit>> *));
};

#endif //PRACTICA2_QT_MENUITEM_H