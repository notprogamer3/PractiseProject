//
// Created by rdast on 21.03.2024.
//

#include "MenuItem.h"


// Получить наименование пункта
string MenuItem::getText() const {
    return text;
}

// Установить наименование пункта
void MenuItem::setText(const string &text) {
    MenuItem::text = text;
}


// Получить статус видимости пункта
bool MenuItem::isHidden() const {
    return hidden;
}

// Установить статус видимости пункта
void MenuItem::setHidden(bool hidden) {
    MenuItem::hidden = hidden;
}

// Получить указатель на функцию пункта
void (*MenuItem::getFunc())(vector<shared_ptr<Deposit>> *) {
    return this->func;
}

// Установить указатель на функцию пункта
void MenuItem::setFunc(void (*func)(vector<shared_ptr<Deposit>> *)) {
    MenuItem::func = func;
}
