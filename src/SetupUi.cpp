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

void Ui::OpenDepositWindow(){
    windows["MainWindow"]->hide();
    windows["AddDepositWindow"]->show();
}

void Ui::OpenTableWindow(){
    windows["MainWindow"]->hide();
    windows["TableWindow"]->show();
    QTableWidget *Table = windows["TableWindow"]->findChild<QTableWidget *>("Table");
    qDebug()<<"tavle init"<<Table->rowCount();
    for (int i = 0; i < Table->rowCount(); ++i) {
        Table->setRowHidden(i, false);
    }
    Table->clear();
    Table->setColumnCount(9);

    Table->setHorizontalHeaderItem(0, new QTableWidgetItem("Логин"));
    Table->setHorizontalHeaderItem(1, new QTableWidgetItem("И.Ф."));
    Table->setHorizontalHeaderItem(2, new QTableWidgetItem("Телефон"));
    Table->setHorizontalHeaderItem(3, new QTableWidgetItem("Email"));
    Table->setHorizontalHeaderItem(4, new QTableWidgetItem("Тип вклада"));
    Table->setHorizontalHeaderItem(5, new QTableWidgetItem("Срок в месяцах"));
    Table->setHorizontalHeaderItem(6, new QTableWidgetItem("Сумма"));
    Table->setHorizontalHeaderItem(7, new QTableWidgetItem("Процент"));
    Table->setHorizontalHeaderItem(8, new QTableWidgetItem("Доход"));
    Table->setRowCount(Deposits->size());
    qDebug() << Deposits->size()<<"Table init";
    for (int i = 0; i < Deposits->size(); i++) {
        QTableWidgetItem *Login = new QTableWidgetItem(QString::fromStdString(Deposits->at(i)->getLogin()));
        QTableWidgetItem *Name_Surname = new QTableWidgetItem(QString::fromStdString(Deposits->at(i)->getName_Surname()));
        QTableWidgetItem *Phone = new QTableWidgetItem(QString::fromStdString(Deposits->at(i)->getPhone()));
        QTableWidgetItem *Email = new QTableWidgetItem(QString::fromStdString(Deposits->at(i)->getEmail()));
        QTableWidgetItem *Type = new QTableWidgetItem(QString::fromStdString(Deposits->at(i)->getType()));
        QTableWidgetItem *Time = new QTableWidgetItem;
        Time->setData(Qt::EditRole, Deposits->at(i)->getTimeInMonths());
        QTableWidgetItem *Amount = new QTableWidgetItem;
        Amount->setData(Qt::EditRole, Deposits->at(i)->getAmount());
        QTableWidgetItem *Percent = new QTableWidgetItem;
        Percent->setData(Qt::EditRole, Deposits->at(i)->getPercent());
        QTableWidgetItem *Income = new QTableWidgetItem;
        Income->setData(Qt::EditRole, Deposits->at(i)->getIncome());
        Table->setItem(i, 0, Login);
        Table->setItem(i, 1, Name_Surname);
        Table->setItem(i, 2, Phone);
        Table->setItem(i, 3, Email);
        Table->setItem(i, 4, Type);
        Table->setItem(i, 5, Time);
        Table->setItem(i, 6, Amount);
        Table->setItem(i, 7, Percent);
        Table->setItem(i, 8, Income);
    }
}

void Ui::TableSearch() {
    QString type = windows["TableWindow"]->findChild<QComboBox *>("SearchType")->currentText();
    QString data = windows["TableWindow"]->findChild<QLineEdit *>("SearchLine")->text();
    QTableWidget *Table = windows["TableWindow"]->findChild<QTableWidget *>("Table");
    int temp2;
    if (type == "Сумма") {
        temp2 = 6;
    } else if (type == "Сроку") {
        temp2 = 5;
    } else if (type == "Типу") {
        temp2 = 4;
    }
    for (int i = 0; i < Table->rowCount(); ++i) {
        if (Table->item(i, temp2)->text() != data) { // 4 is the column index for "Type"
            Table->setRowHidden(i, true);
        } else {
            Table->setRowHidden(i, false);
        }
    }
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
    QObject::connect(addDepositButton, &QPushButton::clicked, [=, this](){OpenDepositWindow();});
    QObject::connect(tableButton, &QPushButton::clicked, [=, this](){OpenTableWindow();});


    QPushButton *backButton = windows["TableWindow"]->findChild<QPushButton *>("BackToMenu");
    qDebug()<<"Here";
    QObject::connect(backButton, &QPushButton::clicked, [=, this](){GetBackToMainWindow("TableWindow");});
    QPushButton *seatchButton = windows["TableWindow"]->findChild<QPushButton *>("SearchButton");
    QObject::connect(seatchButton, &QPushButton::clicked, [=, this](){TableSearch();});
}