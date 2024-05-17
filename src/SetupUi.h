//
// Created by rdast on 13.04.2024.
//

#ifndef SETUPUI_H
#define SETUPUI_H
#include <vector>
#include "Deposit.h"
#include <QtWidgets>

using namespace std;

class Ui {
    std::map<std::string, QWidget*> windows;
    QApplication *app;
    std::vector<shared_ptr<Deposit>> *Deposits;
    QMainWindow *main = new QMainWindow();
    QTabWidget *tabWidget = new QTabWidget();

public:

    void ChangeTheme(QPushButton *button);
    void SetupWindows();
    void ResetDepositWindow();
    void AddDeposit();
    void TableSearch();
    void DrawTable();
    void DrawDiagram(QGraphicsScene *scene);
    void MakeReport(QGraphicsScene *scene, vector<string> Logins);

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
