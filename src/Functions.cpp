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

using namespace std;



void InputIntCheck(int &Number, int left, int right, int *skip) {
    string test;
    while (true) {
        cin >> test;
        if (test.find_first_not_of("-0123456789") != string::npos) {
            cout << "Неправильный ввод. Попробуйте снова" << endl;
            continue;
        } else {
            cout<<"test: "<<endl;
            Number = stoi(test);
            if (Number < left or Number > right or (skip != nullptr and skip[Number - 1] == 0 and skip[1])) {
                cout << "Неправильный ввод. Введите число между " << left << " и " << right << "." << endl;
                continue;
            }
            break;
        }

    }
}

void DepositFunctions::SaveData(vector<shared_ptr<Deposit>> *Deps) {
    ofstream fout("data.txt");
    for (auto &i : *Deps) {
        fout << *i << endl;
    }
    fout.close();
}

void DepositFunctions::LoadData(vector<shared_ptr<Deposit>> *Deps) {
    ifstream fin("data.txt");
    while (!fin.eof()) {
        shared_ptr<Deposit> temp(new Deposit("", "", "", "", "", 0, 0, 0));
        fin >> *temp;
        if(fin) {
            Deps->push_back(temp);
        }
    }
    fin.close();
}

void DepositFunctions::AddDeposit(vector<shared_ptr<Deposit>> *Deps) {
    string Login;
    string Name_Surname;
    string Phone;
    string Email;
    string Type;
    int TimeInMonths;
    int Amount;
    int temp;
    int Percent = 5;
    Login = "login" + to_string(Deps->size());
    cout << "Введите имя и фамилию: ";
    cin >> Name_Surname;
    cout << "Введите номер: ";
    cin >> Phone;
    regex russiaPhoneRegex(R"(^(?:\+7|7|8|9)?(\d{10})$)");
//    while (!regex_match(Phone, russiaPhoneRegex)) {
//        cout << "Введет неправильный номер телефона. Попробуйте снова: " << endl;
//        cin >> Phone;
//    }
    cout << "Enter email: ";
    cin >> Email;
    regex emailRegex(R"(^[a-zA-Z0-9_.+-]+@[a-zA-Z0-9-]+\.[a-zA-Z0-9-.]+$)");
//    while (!regex_match(Email, emailRegex)) {
//        cout << "Введена неправильная электронная почта. Попробуйте снова: " << endl;
//        cin >> Email;
//    }
    cout << "Choose type: \n";
    for (int i = 0; i < 6; ++i) {
        switch (i) {
            case 0:
                cout << "1. Тип 1" << endl;
                break;
            case 1:
                cout << "2. тип 2" << endl;
                break;
            case 2:
                cout << "3. тип 3" << endl;
                break;
        }
    }
    InputIntCheck(temp, 1, 3);
        switch (temp) {
            case 1:
                Type = "Тип 1";
                break;
            case 2:
                Type = "Тип 2";
                break;
            case 3:
                Type = "Тип 3";
                break;
        }
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
    auto Dep = make_shared<Deposit>(Login, Name_Surname, Phone, Email, Type, TimeInMonths, Amount, Percent);
    Deps->push_back(Dep);
}

void DepositFunctions::TestingData(vector<shared_ptr<Deposit>> *Deps) {
    cout << left << setw(10) << "Login" << setw(20) << "Name_Surname" << setw(15) << "Phone"
         << setw(20) << "Email" << setw(10) << "Type" << setw(15) << "TimeInMonths"
         << setw(10) << "Amount" << setw(10) << "Percent" << setw(10) << "Income" << endl;
    cout << string(110, '-') << endl;

    for (const auto& dep : *Deps) {
        cout << left << setw(10) << dep->getLogin() << setw(20) << dep->getName_Surname()
             << setw(15) << dep->getPhone() << setw(20) << dep->getEmail()
             << setw(20) << dep->getType() << setw(15) << dep->getTimeInMonths()
             << setw(10) << dep->getAmount() << setw(10) << dep->getPercent()
             << setw(10) << dep->getIncome() << endl;
    }
}

void DepositFunctions::Search(vector<shared_ptr<Deposit>> *Deps) {
    cout << "Введите логин: ";
    string Login;
    cin >> Login;
    shared_ptr<Deposit> temp;
    bool flag = false;
    for (auto &i : *Deps) {
        if (i->getLogin() == Login) {
            cout << i->getLogin() << endl;
            cout << i->getName_Surname() << endl;
            cout << i->getPhone() << endl;
            cout << i->getEmail() << endl;
            cout << i->getType() << endl;
            cout << i->getTimeInMonths() << endl;
            cout << i->getAmount() << endl;
            cout << i->getPercent() << endl;
            cout << i->getIncome() << endl;
            flag = true;
            temp = i;
            break;
        }
    }
    if (!flag) {
        cout << "данный логин не найден" << endl;
    } else {
        cout << "Выберите действие: \n1.Удалить действие \n2.Выйти в меню\n" << endl;
        int temp1;
        InputIntCheck(temp1, 1, 2);
        if (temp1 == 1) {
            temp.reset();
            Deps->erase(find(Deps->begin(), Deps->end(), temp));
            return;
        } else
            return;
    }
}

void DepositFunctions::Delete(vector<shared_ptr<Deposit>> *Deps) {
    cout << "Введите логин: ";
    string Login;
    cin >> Login;
    for (auto i = Deps->begin(); i != Deps->end(); i++) {
        if ((*i)->getLogin() == Login) {
            i->reset();
            Deps->erase(i);
            break;
        }
    }
}