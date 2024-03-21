//
// Created by rdast on 21.03.2024.
//

#include "MenuItem.h"

string MenuItem::getText() const {
    return text;
}

void MenuItem::setText(const string &text) {
    MenuItem::text = text;
}

bool MenuItem::isHidden() const {
    return hidden;
}

void MenuItem::setHidden(bool hidden) {
    MenuItem::hidden = hidden;
}

int (*MenuItem::getFunc())() {
    return func;
}

void MenuItem::setFunc(int (*func)()) {
    MenuItem::func = func;
}
