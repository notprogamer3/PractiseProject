//
// Created by rdast on 31.05.2024.
//

#ifndef TEST_QLINEEDIT_H
#define TEST_QLINEEDIT_H

#include <QtTest/QtTest>
#include "../src/Deposit.h"

class TestDeposit : public QObject {
    Q_OBJECT

private slots:
    void test_deposit_getters_and_setters();

    void test_Search();
};

#endif // TEST_QLINEEDIT_H
