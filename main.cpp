#include <iostream>
#include <qstylefactory.h>
#include "vector"
#include "memory"
#include "fstream"
#include "boost/algorithm/string.hpp"
#include "src/Deposit.h"
#include "src/Functions.h"
#include "QtCore"
#include "src/SetupUi.h"





using namespace std;

//TODO отчет делать через выбор записей по кнопке в таблице и делать его просто в виде текстовом

int main(int argc, char *argv[]) {
    ofstream fout("data.txt", ios::app);
    fout.close();

    vector<shared_ptr<Deposit>> Deposits;
    DepositFunctions::LoadData(&Deposits);
    QApplication app(argc, argv);
    qDebug()<<QStyleFactory::keys();
    qDebug()<<app.style();
    app.setStyle("windowsvista");
    Ui ui(&app, &Deposits);

    return app.exec();
}
