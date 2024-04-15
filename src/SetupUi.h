//
// Created by rdast on 13.04.2024.
//

#ifndef SETUPUI_H
#define SETUPUI_H



#include <vector>
#include <QPushButton>
#include <QObject>
#include "Deposit.h"

using namespace std;

class Ui {
    std::map<std::string, QWidget*> windows;
    QApplication *app;
    std::vector<shared_ptr<Deposit>> *Deposits;

public:

    void ChangeTheme(QPushButton *button);
    void GetBackToMainWindow(string name);
    void SetupWindows();
    void OpenTableWindow();
    void OpenDepositWindow();
    void TableSearch();

    Ui(QApplication *app = nullptr, std::vector<shared_ptr<Deposit>> *Deps = nullptr) {
        this->app = app;
        this->Deposits = Deps;
        SetupWindows();
    }


    QWidget* &operator[](const std::string &key) {
        return windows[key];
    }

};



#endif //SETUPUI_H