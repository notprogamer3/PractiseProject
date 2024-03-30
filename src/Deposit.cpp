//
// Created by rdast on 23.03.2024.
//

#include "Deposit.h"
using namespace std;

//
// Created by rdast on 23.03.2024.
//

#include "Deposit.h"

Deposit::Deposit(std::string Login, std::string Name_Surname, std::string Phone, std::string Email, std::string Type,
                 int TimeInMonths, int Amount, int Percent) {
    this->Login = Login;
    this->Name_Surname = Name_Surname;
    this->Phone = Phone;
    this->Email = Email;
    this->Type = Type;
    this->TimeInMonths = TimeInMonths;
    this->Amount = Amount;
    this->Percent = Percent;
    this->Income = Amount + Amount * Percent / 100 * TimeInMonths / 12;

}


string Deposit::getLogin() const {
    return Login;
}

void Deposit::setLogin(const string &login) {
    Login = login;
}

string Deposit::getName_Surname() const {
    return Name_Surname;
}

void Deposit::setName_Surname(const string &name_surname) {
    Name_Surname = name_surname;
}

string Deposit::getPhone() const {
    return Phone;
}

void Deposit::setPhone(const string &phone) {
    Phone = phone;
}

string Deposit::getEmail() const {
    return Email;
}

void Deposit::setEmail(const string &email) {
    Email = email;
}

string Deposit::getType() const {
    return Type;
}

void Deposit::setType(const string &type) {
    Type = type;
}

int Deposit::getTimeInMonths() const {
    return TimeInMonths;
}

void Deposit::setTimeInMonths(int timeInMonths) {
    TimeInMonths = timeInMonths;
}

int Deposit::getAmount() const {
    return Amount;
}

void Deposit::setAmount(int amount) {
    Amount = amount;
}

int Deposit::getPercent() const {
    return Percent;
}

void Deposit::setPercent(int percent) {
    Percent = percent;
}

int Deposit::getIncome() const {
    return Income;
}

void Deposit::setIncome(int income) {
    Income = income;
}

std::ostream& operator<<(std::ostream& os, const Deposit& dep) {
    os << dep.Login << " " << dep.Name_Surname << " " << dep.Phone << " " << dep.Email << " " << dep.Type << " "
       << dep.TimeInMonths << " " << dep.Amount << " " << dep.Percent << " " << dep.Income;
    return os;
}

std::istream& operator>>(std::istream& is, Deposit& dep) {
    is >> dep.Login >> dep.Name_Surname >> dep.Phone >> dep.Email >> dep.Type
       >> dep.TimeInMonths >> dep.Amount >> dep.Percent >> dep.Income;
    return is;
}