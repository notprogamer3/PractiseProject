//
// Created by rdast on 13.04.2024.
//

#ifndef SETUPUI_H
#define SETUPUI_H



#include <vector>
#include <QPushButton>
#include <QObject>

using namespace std;

class Ui {
    std::map<std::string, QWidget*> windows;
    QApplication *app;

public:

    void ChangeTheme(QPushButton *button);
    void GetBackToMainWindow(string name);
    void SetupWindows();
    void OpenWindow(string name);

    Ui(QApplication *app = nullptr) {
        this->app = app;
        SetupWindows();
    }


    QWidget* &operator[](const std::string &key) {
        return windows[key];
    }

};



#endif //SETUPUI_H
