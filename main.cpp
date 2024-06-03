#include <iostream>
#include <qstylefactory.h>
#include <QtTest/qtest.h>

#include "vector"
#include "memory"
#include "fstream"
#include "boost/algorithm/string.hpp"
#include "src/Deposit.h"
#include "src/Functions.h"
#include "QtCore"
#include "src/SetupUi.h"
#include "Qt_test/tests.h"



using namespace std;


int maind(int argc, char *argv[]) {
    ofstream fout("data.txt", ios::app);
    fout.close();

    vector<shared_ptr<Deposit>> Deposits;
    DepositFunctions::LoadData(&Deposits);
    // QApplication app(argc, argv);
    // QTest::qExec(new TestDeposit, argc, argv);
    qDebug()<<QStyleFactory::keys();
    //qDebug()<<app.style();
    //app.setStyle("windowsvista");
    // Ui ui(&app, &Deposits);


    return 1;
}
