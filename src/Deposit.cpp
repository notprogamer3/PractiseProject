//
// Created by rdast on 23.03.2024.
//

#include "Deposit.h"

using namespace std;

//
// Created by rdast on 23.03.2024.
//

#include "Deposit.h"

// конструктор
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

// получение логина вклада
string Deposit::getLogin() const {
    return Login;
}

// установка логина вклада
void Deposit::setLogin(const string &login) {
    Login = login;
}

// получение ФИ клиента
string Deposit::getName_Surname() const {
    return Name_Surname;
}

// установка ФИ клиента
void Deposit::setName_Surname(const string &name_surname) {
    Name_Surname = name_surname;
}
// получение телефона клиента
string Deposit::getPhone() const {
    return Phone;
}

// установка телефона клиента
void Deposit::setPhone(const string &phone) {
    Phone = phone;
}

// получение почты клиента
string Deposit::getEmail() const {
    return Email;
}

// установка почты клиента
void Deposit::setEmail(const string &email) {
    Email = email;
}

// получение типа вклада
string Deposit::getType() const {
    return Type;
}

// установка типа вклада
void Deposit::setType(const string &type) {
    Type = type;
}

// получение срока в месяцах
int Deposit::getTimeInMonths() const {
    return TimeInMonths;
}

//  установка срока в месяцах
void Deposit::setTimeInMonths(int timeInMonths) {
    TimeInMonths = timeInMonths;
}

// получение суммы вклада
int Deposit::getAmount() const {
    return Amount;
}

// установка суммы вклада
void Deposit::setAmount(int amount) {
    Amount = amount;
}

// получение процентной ставки
int Deposit::getPercent() const {
    return Percent;
}


// установка процентной ставки
void Deposit::setPercent(int percent) {
    Percent = percent;
}

// получение дохода
int Deposit::getIncome() const {
    return Income;
}

// установка дохода
void Deposit::setIncome(int income) {
    Income = income;
}

// перегрузка операторов ввода и вывода в файл
std::ostream& operator<<(std::ostream& os, const Deposit& dep) {
    os << dep.Login << " " << dep.Name_Surname << " " << dep.Phone << " " << dep.Email << " " << dep.Type << " "
       << dep.TimeInMonths << " " << dep.Amount << " " << dep.Percent << " " << dep.Income;
    return os;
}


// перегрузка операторов ввода и вывода в файл
std::istream& operator>>(std::istream& is, Deposit& dep) {
    is >> dep.Login >> dep.Name_Surname >> dep.Phone >> dep.Email >> dep.Type
       >> dep.TimeInMonths >> dep.Amount >> dep.Percent >> dep.Income;
    return is;
}