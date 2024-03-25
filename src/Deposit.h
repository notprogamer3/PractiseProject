//
// Created by rdast on 23.03.2024.
//

#ifndef PRACTICA2_QT_DEPOSIT_H
#define PRACTICA2_QT_DEPOSIT_H

#include "string"

using namespace std;


class Deposit {
private:
    string Login;
    string Name_Surname;
    string Phone;
    string Email;
    string Type;
    int TimeInMonths;
    int Amount;
    int Percent;
    int Income;

public:
    Deposit(string Login, string Name_Surname, string Phone, string Email, string Type, int TimeInMonths, int Amount, int Percent);

    // getters and setters
    string getLogin() const;
    void setLogin(const string &Login);

    string getName_Surname() const;
    void setName_Surname(const string &Name_Surname);

    string getPhone() const;
    void setPhone(const string &Phone);

    string getEmail() const;
    void setEmail(const string &Email);

    string getType() const;
    void setType(const string &Type);

    int getTimeInMonths() const;
    void setTimeInMonths(int TimeInMonths);

    int getAmount() const;
    void setAmount(int Amount);

    int getPercent() const;
    void setPercent(int Percent);

    int getIncome() const;
    void setIncome(int Income);

    friend ostream &operator<<(ostream &os, const Deposit &deposit) {
        os << deposit.Login
           << deposit.Name_Surname
           << deposit.Phone
           << deposit.Email
           << deposit.Type
           << to_string(deposit.TimeInMonths)
           << to_string(deposit.Amount)
           << to_string(deposit.Percent)
           << to_string(deposit.Income);
        return os;
    };

};


#endif //PRACTICA2_QT_DEPOSIT_H
