//
// Created by rdast on 24.03.2024.
//

#include "Functions.h"
#include "Deposit.h"
#include <fstream>
#include <vector>
#include "memory"
#include <iostream>
#include "regex"
#include <iomanip>
#include <algorithm>
#include <string>
#include <cmath>

//Печатание пробелов для таблицы
void PrintSpaces(int n) {
    for (int i = 0; i < n; i++) {
        cout << " ";
    }
}


using namespace std;

// Проверка ввода числа в заданном диапазоне (также число ли вообще)
void InputIntCheck(int &Number, int left, int right, int *skip) {
    string test;
    while (true) {
        cin >> test;
        if (test.find_first_not_of("-0123456789") != string::npos) {
            cout << "Неправильный ввод. Попробуйте снова" << endl;
            continue;
        } else {
            cout << "test: " << endl;
            Number = stoi(test);
            if (Number < left or Number > right or (skip != nullptr and skip[Number - 1] == 0 and skip[1])) {
                cout << "Неправильный ввод. Введите число между " << left << " и " << right << "." << endl;
                continue;
            }
            break;
        }

    }
}

// Сохранение данных в файл
void DepositFunctions::SaveData(vector<shared_ptr<Deposit>> *Deps) {
    ofstream fout("data.txt");
    for (auto &i: *Deps) {
        fout << *i << endl;
    }
    fout.close();
}

// Загрузка данных из файла
void DepositFunctions::LoadData(vector<shared_ptr<Deposit>> *Deps) {
    ifstream fin("data.txt");
    Deps->clear();
    while (!fin.eof()) {
        // Динамическое создание объекта и добавление его в вектор
        shared_ptr<Deposit> temp(new Deposit("", "", "", "", "", 0, 0, 0));
        fin >> *temp;
        if (fin) {
            Deps->push_back(temp);
        }
    }
    fin.close();
}

// Добавление вклада
void DepositFunctions::AddDeposit(vector<shared_ptr<Deposit>> *Deps) {
    //-------------------------------------------------------
    // Временные переменные для создания депозита
    string Login;
    string Name_Surname;
    string Phone;
    string Email;
    string Type;
    int TimeInMonths;
    int Amount;
    int temp;
    int Percent = 5;
    string name;
    string surname;
    // логин генерируется автоматически для более простого обращения после к записям
    Login = "login" + to_string(Deps->size());
    // ввод имен и фамилии
    cout << "Введите имя: ";
    cin >> name;
    cout << "Введите фамилию: ";
    cin >> surname;
    Name_Surname = name + "_" + surname;
    // ввод номера телефона
    cout << "Введите номер: ";
    cin >> Phone;
    regex russiaPhoneRegex(R"(^(?:\+7|7|8|9)?(\d{10})$)");
    // проверка вода номера телефона
    //    while (!regex_match(Phone, russiaPhoneRegex)) {
//        cout << "Введет неправильный номер телефона. Попробуйте снова: " << endl;
//        cin >> Phone;
//    }
    // ввод почты
    cout << "Enter email: ";
    cin >> Email;
    regex emailRegex(R"(^[a-zA-Z0-9_.+-]+@[a-zA-Z0-9-]+\.[a-zA-Z0-9-.]+$)");
    // проверка вода почты
//    while (!regex_match(Email, emailRegex)) {
//        cout << "Введена неправильная электронная почта. Попробуйте снова: " << endl;
//        cin >> Email;
//    }
    // выбор типа вклада
    cout << "Choose type: \n";
    for (int i = 0; i < 6; ++i) {
        switch (i) {
            case 0:
                cout << "1. Тип 1" << endl;
            break;
            case 1:
                cout << "2. тип 2" << endl;
            break;
        }
    }
    InputIntCheck(temp, 1, 2);
    switch (temp) {
        case 1:
            Type = "Тип_1";
            break;
        case 2:
            Type = "Тип_2";
            Percent+=5;
            break;
    }
    // выбор срока вклада
    cout << "Выберите промежуток: \n";
    for (int i = 0; i < 6; ++i) {
        switch (i) {
            case 0:
                cout << "1. 3 месяцев" << endl;
                break;
            case 1:
                cout << "2. 6 месяцев" << endl;
                break;
            case 2:
                cout << "3. 9 месяцев" << endl;
                break;
            case 3:
                cout << "4. 12 месяцев" << endl;
                break;
            case 4:
                cout << "5. 18 месяцев" << endl;
                break;
            case 5:
                cout << "6. 24 месяцев" << endl;
                break;
        }
    }
    InputIntCheck(temp, 1, 6);
    switch (temp) {
        case 1:
            TimeInMonths = 3;
            break;
        case 2:
            TimeInMonths = 6;
            break;
        case 3:
            TimeInMonths = 9;
            break;
        case 4:
            TimeInMonths = 12;
            break;
        case 5:
            TimeInMonths = 18;
            break;
        case 6:
            TimeInMonths = 24;
            break;

    }
    cout << "Enter amount: ";
    InputIntCheck(Amount, 0, 1000000);
    // Динамическое создание объекта и добавление его в вектор
    auto Dep = make_shared<Deposit>(Login, Name_Surname, Phone, Email, Type, TimeInMonths, Amount, Percent);
    Deps->push_back(Dep);
}

// Вывод данных таблицой
void DepositFunctions::TestingData(vector<shared_ptr<Deposit>> *Deps) {
    cout << left << setw(10) << "Login" << setw(20) << "Name_Surname" << setw(30) << "Phone"
         << setw(20) << "Email" << setw(10) << "Type" << setw(15) << "TimeInMonths"
         << setw(10) << "Amount" << setw(10) << "Percent" << setw(10) << "Income" << endl;
    cout << string(133, '-') << endl;
    string temp;
    for (const auto &dep: *Deps) {
        cout << dep->getLogin();
        PrintSpaces(10 - dep->getLogin().length());

        cout << dep->getName_Surname();
        PrintSpaces(19 - dep->getName_Surname().length() / 2);

        cout << dep->getPhone();
        PrintSpaces(30 - dep->getPhone().length());

        cout << dep->getEmail();
        PrintSpaces(20 - dep->getEmail().length());

        cout << dep->getType();
        PrintSpaces(9 - dep->getType().length() / 2);

        cout << dep->getTimeInMonths();
        PrintSpaces(15 - to_string(dep->getTimeInMonths()).length());

        cout << dep->getAmount();
        PrintSpaces(10 - to_string(dep->getAmount()).length());

        cout << dep->getPercent();
        PrintSpaces(10 - to_string(dep->getPercent()).length());

        cout << dep->getIncome();
        PrintSpaces(10 - to_string(dep->getIncome()).length());
        cout << endl;
    }
}

// Поиск вклада по параметру
vector<shared_ptr<Deposit>> *DepositFunctions::Search(vector<shared_ptr<Deposit>> *Deps, string type, string data) {
    cout << "Введите параметр по которому хотите найти вклад: \n1.Логин\n2.Email\n3.Дата\n4.Тип\n";
    vector<shared_ptr<Deposit>> Finded;
    int temp2;
    // выбор параметра по которому будет производиться поиск
    if (type == "Сумма") {
        temp2 = 1;
    } else if (type == "Сроку") {
        temp2 = 2;
    } else if (type == "Типу") {
        temp2 = 3;
    }
    shared_ptr<Deposit> temp;
    bool flag = false;
    // поиск вклада по параметру
    for (auto &i: *Deps) {
        if ((to_string(i->getAmount()) == data and temp2 == 1) or (to_string(i->getTimeInMonths()) == data and temp2 == 2) or (i->getType() == data and temp2 == 3)) {
            cout << "Login: "<<i->getLogin() << endl;
            cout << "Имя_фам: "<<i->getName_Surname() << endl;
            cout << "Номер: "<<i->getPhone() << endl;
            cout << "Email: "<<i->getEmail() << endl;
            cout << "тип: "<<i->getType() << endl;
            cout << "срок в месяцах: "<<i->getTimeInMonths() << endl;
            cout << "Размер: " <<i->getAmount() << endl;
            cout << "Процент: " <<i->getPercent() << endl;
            cout << "Доход: " <<i->getIncome() << endl;
            Finded.push_back(i);
            flag = true;
        }
    }
    if (!flag) {
        cout << "Совпадение не найдено" << endl;
    }
    return &Finded;
//    } else {
//        cout << "Выберите действие: \n1.Удалить действие \n2.Выйти в меню\n" << endl;
//        int temp1;
//        InputIntCheck(temp1, 1, 2);
//        if (temp1 == 1) {
//            temp.reset();
//            Deps->erase(find(Deps->begin(), Deps->end(), temp));
//            return;
//        } else
//            return;
//    }
}

// Удаление вклада
void DepositFunctions::Delete(vector<shared_ptr<Deposit>> *Deps) {
    cout << "Введите логин: ";
    string Login;
    cin >> Login;
    for (auto i = Deps->begin(); i != Deps->end(); i++) {
        if ((*i)->getLogin() == Login) {
            // Динамическое удаление объекта и удаление его из вектора
            (*i).reset();
            Deps->erase(i);
            break;
        }
    }
}