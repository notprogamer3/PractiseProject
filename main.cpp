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


int main(int argc, char *argv[]) {
    ofstream fout("data.txt", ios::app);
    fout.close();

    vector<shared_ptr<Deposit>> Deposits;
    DepositFunctions::LoadData(&Deposits);
    QApplication app(argc, argv);
    qDebug()<<QStyleFactory::keys();
    app.setStyle("windowsvista");
    Ui ui(&app, &Deposits);

    app.exec();

    return 1;
}
