//
// Created by rdast on 13.04.2024.
//

#ifndef SETUPUI_H
#define SETUPUI_H
#include <vector>
#include <QPushButton>
#include <QObject>
#include "Deposit.h"
#include <QtWidgets>

using namespace std;

class Ui {
    std::map<std::string, QWidget*> windows;
    QApplication *app;
    std::vector<shared_ptr<Deposit>> *Deposits;
    QMainWindow *main = new QMainWindow();

public:

    void ChangeTheme(QPushButton *button);
    void GetBackToMainWindow();
    void SetupWindows();
    void OpenTableWindow();
    void OpenDepositWindow();
    void CloseDepositWindow();
    void AddDepositUi();
    void TableSearch();
    void DrawTable();
    void DrawDiagram(QGraphicsScene *scene);

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
