//
// Created by rdast on 31.05.2024.
//

#include <QtTest/QtTest>
#include "../src/Deposit.h"
#include "tests.h"
#include "../src/Functions.h"
#include <sstream>
#include <iomanip>



void TestDeposit::test_deposit_getters_and_setters(){
    std::string test_login = "test_login";
    std::string test_name_surname = "test_name_surname";
    std::string test_phone = "test_phone";
    std::string test_email = "test_email";
    std::string test_type = "test_type";
    int test_time_in_months = 12;
    int test_amount = 1000;
    int test_percent = 5;
    int test_income = 50;

    Deposit deposit(test_login, test_name_surname, test_phone, test_email, test_type, test_time_in_months, test_amount, test_percent);

    QCOMPARE(deposit.getLogin(), test_login);
    QCOMPARE(deposit.getName_Surname(), test_name_surname);
    QCOMPARE(deposit.getPhone(), test_phone);
    QCOMPARE(deposit.getEmail(), test_email);
    QCOMPARE(deposit.getType(), test_type);
    QCOMPARE(deposit.getTimeInMonths(), test_time_in_months);
    QCOMPARE(deposit.getAmount(), test_amount);
    QCOMPARE(deposit.getPercent(), test_percent);
    QCOMPARE(deposit.getIncome(), test_income);
}

void TestDeposit::test_Search() {
    // Test seatch
    string type = "Сумма";
    string data = "1000";
    vector<shared_ptr<Deposit>> Deposits;
    shared_ptr<Deposit> Dep = make_shared<Deposit>("test_login", "test_name_surname", "test_phone", "test_email", "test_type", 12, 1000, 5);
    Deposits.push_back(Dep);
    vector<int> Finded = DepositFunctions::Search(&Deposits, type, data);
    for (int i : Finded) {
        QCOMPARE(Deposits[i]->getAmount(), 1000);
    }
}
