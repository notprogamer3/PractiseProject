//
// Created by rdast on 13.04.2024.
//
#include "QtUiTools"
#include "SetupUi.h"
#include "QWidget"
#include "string"
#include "Functions.h"
#include "Deposit.h"


using namespace std;

static QWidget *loadUiFile(QWidget *parent, const std::string& path)
{
    QString qPath = QString::fromStdString(path);
    QFile file(qPath);
    file.open(QIODevice::ReadOnly);

    QUiLoader loader;
    return loader.load(&file, parent);
}

void Ui::ChangeTheme(QPushButton *button) {
    if (button->text() == "Светлая тема") {
        app->setStyle("windowsvista");
        button->setText("Темная тема");
    } else {
        app->setStyle("fusion");
        button->setText("Светлая тема");
    }
}

void Ui::GetBackToMainWindow(string name){
    windows[name]->hide();
    windows["MainWindow"]->show();
}

void Ui::OpenWindow(string name){
    windows["MainWindow"]->hide();
    windows[name]->show();
}

void Ui::SetupWindows()
{

    windows["MainWindow"] = loadUiFile(nullptr, "../Ui/Главное окно.ui");
    windows["AddDepositWindow"] = loadUiFile(nullptr, "../Ui/Добавление вклада.ui");
    windows["TableWindow"] = loadUiFile(nullptr, "../Ui/Таблица.ui");

    windows["MainWindow"]->show();
    QPushButton *button = windows["MainWindow"]->findChild<QPushButton *>("ChangeTheme");
    QPushButton *addDepositButton = windows["MainWindow"]->findChild<QPushButton *>("AddDeposit");
    QPushButton *tableButton = windows["MainWindow"]->findChild<QPushButton *>("ShowTable");
    QObject::connect(button, &QPushButton::clicked, [=, this](){ChangeTheme(button);});
    QObject::connect(addDepositButton, &QPushButton::clicked, [=, this](){OpenWindow("AddDepositWindow");});
    QObject::connect(tableButton, &QPushButton::clicked, [=, this](){OpenWindow("TableWindow");});


    QPushButton *backButton = windows["TableWindow"]->findChild<QPushButton *>("BackToMenu");
    qDebug()<<"Here";
    QObject::connect(backButton, &QPushButton::clicked, [=, this](){GetBackToMainWindow("TableWindow");});

}