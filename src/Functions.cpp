//
// Created by rdast on 24.03.2024.
//

#include "Functions.h"
#include "Deposit.h"
#include <fstream>
#include <vector>
#include "memory"
#include <iostream>

using namespace std;



void InputIntCheck(int &Number, int left, int right, int *skip) {
    string test;
    while (true) {
        cin >> test;
        if (test.find_first_not_of("-0123456789") != string::npos) {
            cout << "Invalid input. Please enter a number." << endl;
            continue;
        } else {
            Number = stoi(test);
            if (Number < left or Number > right or (skip != nullptr and skip[Number - 1] == 0 and skip[1])) {
                cout << "Invalid input. Please enter a number between " << left << " and " << right << "." << endl;
                continue;
            }
            break;
        }

    }
}

void DepositFunctions::SaveData(vector<shared_ptr<Deposit>> Deps) {
    ofstream fout("data.txt", ios::binary);
    for (auto &i : Deps) {
        fout.write((char *) &i, sizeof(Deposit));
    }
    fout.close();
}

void DepositFunctions::LoadData(vector<shared_ptr<Deposit>> Deps) {
    ifstream fin("data.txt");
    while (!fin.eof()) {
        shared_ptr<Deposit> temp( new Deposit("", "", "", "", "", 0, 0, 0));
        fin.read((char *) &temp, sizeof(Deposit));
        Deps.push_back(temp);
    }
    fin.close();
}

void DepositFunctions::AddDeposit(vector<shared_ptr<Deposit>> Deps) {
    string Login;
    string Name_Surname;
    string Phone;
    string Email;
    string Type;
    int TimeInMonths;
    int Amount;
    int Percent = 5;
    cout << "Enter login: ";
    cin >> Login;
    cout << "Enter name and surname: ";
    cin >> Name_Surname;
    cout << "Enter phone: ";
    cin >> Phone;
    cout << "Enter email: ";
    cin >> Email;
    cout << "Enter type: ";
    cin >> Type;
    cout << "Choose time in months: ";
    for (int i = 0; i < 6; ++i) {
        switch (i) {
            case 0:
                cout << "1. 3 months" << endl;
                break;
            case 1:
                cout << "2. 6 months" << endl;
                break;
            case 2:
                cout << "3. 9 months" << endl;
                break;
            case 3:
                cout << "4. 12 months" << endl;
                break;
            case 4:
                cout << "5. 18 months" << endl;
                break;
            case 5:
                cout << "6. 24 months" << endl;
                break;
        }
    }
    int temp;
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
    shared_ptr<Deposit> Dep(new Deposit(Login, Name_Surname, Phone, Email, Type, TimeInMonths, Amount, Percent));
    Deps.push_back(Dep);
}

void TestingData(vector<shared_ptr<Deposit>> Deps) {
    cout<<"Testing data: "<<endl;
    for (auto &i : Deps) {
        cout << i->getLogin() << endl;
        cout << i->getName_Surname() << endl;
        cout << i->getPhone() << endl;
        cout << i->getEmail() << endl;
        cout << i->getType() << endl;
        cout << i->getTimeInMonths() << endl;
        cout << i->getAmount() << endl;
        cout << i->getPercent() << endl;
        cout << i->getIncome() << endl;
    }
}