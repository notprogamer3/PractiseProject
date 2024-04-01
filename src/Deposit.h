//
// Created by rdast on 23.03.2024.
//

#ifndef PRACTICA2_QT_DEPOSIT_H
#define PRACTICA2_QT_DEPOSIT_H

#include "string"
#include "iostream"

using namespace std;

//-----------------------------------------------------
// Основная единца баззы данных - вклад
class Deposit {
private:
    string Login; // логин вклада
    string Name_Surname; // ФИ клиента
    string Phone; // телефон клиента
    string Email; // почта клиента
    string Type; // тип вклада
    int TimeInMonths; // срок в месяцах
    int Amount; // сумма вклада
    int Percent; // процентная ставка
    int Income; // доход

public:
    // конструктор
    Deposit(string Login, string Name_Surname, string Phone, string Email, string Type, int TimeInMonths, int Amount, int Percent);

    // перегрузка операторов ввода и вывода в файл
    friend std::ostream& operator<<(std::ostream& os, const Deposit& dep);
    friend std::istream& operator>>(std::istream& is, Deposit& dep);

    // получение логина вклада
    string getLogin() const;
    // установка логина вклада
    void setLogin(const string &Login);
    // получение ФИ клиента
    string getName_Surname() const;
    // установка ФИ клиента
    void setName_Surname(const string &Name_Surname);
    // получение телефона клиента
    string getPhone() const;
    // установка телефона клиента
    void setPhone(const string &Phone);
    // получение почты клиента
    string getEmail() const;
    // установка почты клиента
    void setEmail(const string &Email);
    // получение типа вклада
    string getType() const;
    // установка типа вклада
    void setType(const string &Type);
    // получение срока в месяцах
    int getTimeInMonths() const;
    // установка срока в месяцах
    void setTimeInMonths(int TimeInMonths);
    // получение суммы вклада
    int getAmount() const;
    // установка суммы вклада
    void setAmount(int Amount);
    // получение процентной ставки
    int getPercent() const;
    // установка процентной ставки
    void setPercent(int Percent);
    // получение дохода
    int getIncome() const;
    // установка дохода
    void setIncome(int Income);
};


#endif //PRACTICA2_QT_DEPOSIT_H
