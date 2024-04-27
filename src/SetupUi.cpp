//
// Created by rdast on 13.04.2024.
//
#include "QtUiTools"
#include "SetupUi.h"
#include "QWidget"
#include "string"
#include "Functions.h"
#include "Deposit.h"
#include "boost/container/string.hpp"


using namespace std;

static QWidget *loadUiFile(QWidget *parent, const std::string &path) {
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
        app->setStyle("windows11");
        button->setText("Светлая тема");
    }
}

void Ui::GetBackToMainWindow(string name) {
    windows[name]->hide();
    windows["MainWindow"]->show();
}

void Ui::OpenDepositWindow() {
    windows["MainWindow"]->hide();
    windows["AddDepositWindow"]->show();
}

void Ui::OpenTableWindow() {
    windows["MainWindow"]->hide();
    windows["TableWindow"]->show();
    QTableWidget *Table = windows["TableWindow"]->findChild<QTableWidget *>("Table");
    qDebug() << "tavle init" << Table->rowCount();
    for (int i = 0; i < Table->rowCount(); ++i) {
        Table->setRowHidden(i, false);
    }
    Table->sortByColumn(0, Qt::AscendingOrder);
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
    qDebug() << Deposits->size() << "Table init";
    for (int i = 0; i < Deposits->size(); i++) {
        QTableWidgetItem *Login = new QTableWidgetItem(QString::fromStdString(Deposits->at(i)->getLogin()));
        QTableWidgetItem *Name_Surname = new QTableWidgetItem(
            QString::fromStdString(Deposits->at(i)->getName_Surname()));
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
        if (Table->item(i, temp2)->text() != data) {
            // 4 is the column index for "Type"
            Table->setRowHidden(i, true);
        } else {
            Table->setRowHidden(i, false);
        }
    }
}

void Ui::CloseDepositWindow() {
    QLineEdit *Name = windows["AddDepositWindow"]->findChild<QLineEdit *>("NameLine");
    QLineEdit *Surname = windows["AddDepositWindow"]->findChild<QLineEdit *>("SurnameLine");
    QLineEdit *Phone = windows["AddDepositWindow"]->findChild<QLineEdit *>("PhoneLine");
    QLineEdit *Email = windows["AddDepositWindow"]->findChild<QLineEdit *>("EmailLine");
    QSlider *Time = windows["AddDepositWindow"]->findChild<QSlider *>("TimeSlider");
    QLineEdit *Amount = windows["AddDepositWindow"]->findChild<QLineEdit *>("AmountLine");
    QLabel *Percent = windows["AddDepositWindow"]->findChild<QLabel *>("PercentLabel");
    QLabel *Error = windows["AddDepositWindow"]->findChild<QLabel *>("ErrorLabel");
    QLabel *TimeLabel = windows["AddDepositWindow"]->findChild<QLabel *>("TimeNumLabel");
    QComboBox *Type = windows["AddDepositWindow"]->findChild<QComboBox *>("TypeOption");
    Name->clear();
    Surname->clear();
    Phone->clear();
    Email->clear();
    Type->setCurrentIndex(0);
    Time->setValue(1);
    Amount->clear();
    Percent->setText("5");
    Error->clear();
    TimeLabel->setText("1");
    GetBackToMainWindow("AddDepositWindow");
}


void Ui::AddDepositUi() {
    QLineEdit *Name = windows["AddDepositWindow"]->findChild<QLineEdit *>("NameLine");
    QLineEdit *Surname = windows["AddDepositWindow"]->findChild<QLineEdit *>("SurnameLine");
    QLineEdit *Phone = windows["AddDepositWindow"]->findChild<QLineEdit *>("PhoneLine");
    QLineEdit *Email = windows["AddDepositWindow"]->findChild<QLineEdit *>("EmailLine");
    QSlider *Time = windows["AddDepositWindow"]->findChild<QSlider *>("TimeSlider");
    QLineEdit *Amount = windows["AddDepositWindow"]->findChild<QLineEdit *>("AmountLine");
    QLabel *Percent = windows["AddDepositWindow"]->findChild<QLabel *>("PercentLabel");
    QLabel *Error = windows["AddDepositWindow"]->findChild<QLabel *>("ErrorLabel");
    QLabel *TimeLabel = windows["AddDepositWindow"]->findChild<QLabel *>("TimeNumLabel");
    QComboBox *Type = windows["AddDepositWindow"]->findChild<QComboBox *>("TypeOption");
    string s = DepositFunctions::AddDeposit(Deposits, Name->text().toStdString(), Surname->text().toStdString(),
                                            Phone->text().toStdString(), Email->text().toStdString(),
                                            Type->currentText().toStdString(), Amount->text().toInt(),
                                            Percent->text().toInt(), Time->value());
    if (s != "1") {
        Error->setText(QString::fromStdString(s));
    } else {
        DepositFunctions::SaveData(Deposits);
        Name->clear();
        Surname->clear();
        Phone->clear();
        Email->clear();
        Type->setCurrentIndex(0);
        Time->setValue(1);
        Amount->clear();
        Percent->setText("");
        Error->clear();
        TimeLabel->setText("1");
        GetBackToMainWindow("AddDepositWindow");
    }
}




//TODO загнать в отедльные функции все что написано черезе лямбду
void Ui::SetupWindows() {
    windows["MainWindow"] = loadUiFile(nullptr, "../Ui/Главное окно.ui");
    windows["AddDepositWindow"] = loadUiFile(nullptr, "../Ui/Добавление вклада.ui");
    windows["TableWindow"] = loadUiFile(nullptr, "../Ui/Таблица.ui");
    windows["DiagramWindow"] = loadUiFile(nullptr, "../Ui/Диаграмма.ui");
    windows["MainWindow"]->show();

    // MainWindow buttons and functionality
    QPushButton *button = windows["MainWindow"]->findChild<QPushButton *>("ChangeTheme");
    QPushButton *addDepositButton = windows["MainWindow"]->findChild<QPushButton *>("AddDeposit");
    QPushButton *tableButton = windows["MainWindow"]->findChild<QPushButton *>("ShowTable");
    QPushButton *DiagramButton = windows["MainWindow"]->findChild<QPushButton *>("ShowDiagram");
    QObject::connect(button, &QPushButton::clicked, [=, this]() { ChangeTheme(button); });
    QObject::connect(addDepositButton, &QPushButton::clicked, [=, this]() { OpenDepositWindow(); });
    QObject::connect(tableButton, &QPushButton::clicked, [=, this]() { OpenTableWindow(); });
    QObject::connect(DiagramButton, &QPushButton::clicked, [=, this]() {
        windows["MainWindow"]->hide();
        windows["DiagramWindow"]->show();
    });


    // TableWindow buttons and functionality
    QPushButton *backButton = windows["TableWindow"]->findChild<QPushButton *>("BackToMenu");
    //Closing TableWindow and clearing lines
    QObject::connect(backButton, &QPushButton::clicked, [=, this]() {
        QLineEdit *SearchLine = windows["TableWindow"]->findChild<QLineEdit *>("SearchLine");
        QComboBox *SearchType = windows["TableWindow"]->findChild<QComboBox *>("SearchType");
        SearchLine->clear();
        SearchType->setCurrentIndex(0);
        DepositFunctions::SaveData(Deposits);
        GetBackToMainWindow("TableWindow");
    });
    QPushButton *seatchButton = windows["TableWindow"]->findChild<QPushButton *>("SearchButton");
    QObject::connect(seatchButton, &QPushButton::clicked,  [=, this] {TableSearch();});
    //Sorting lambda
    QTableWidget *Table = windows["TableWindow"]->findChild<QTableWidget *>("Table");
    Table->setSortingEnabled(false);
    QObject::connect(Table->horizontalHeader(), &QHeaderView::sectionClicked, [=, this](const int logicalIndex) {
        if (logicalIndex == 0 or (logicalIndex >=4 and logicalIndex <= 6)){
            Table->sortByColumn(logicalIndex, Qt::AscendingOrder);
    }
    });
    //Edit toggle
    Table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QRadioButton *radioButton = windows["TableWindow"]->findChild<QRadioButton *>("EditToggle");
    QObject::connect(radioButton, &QRadioButton::toggled, [=, this](bool checked) {
        if (checked) {
            Table->setEditTriggers(QAbstractItemView::DoubleClicked);
        } else {
            Table->setEditTriggers(QAbstractItemView::NoEditTriggers);
        }
    });


    // AddDepositWindow buttons and functionality
    QPushButton *backButton2 = windows["AddDepositWindow"]->findChild<QPushButton *>("BackToMenu");
    QLabel *PercentLabel = windows["AddDepositWindow"]->findChild<QLabel *>("PercentLabel");
    QComboBox *Type = windows["AddDepositWindow"]->findChild<QComboBox *>("TypeOption");
    //Dynamic changing of percent label
    QObject::connect(Type, &QComboBox::currentTextChanged, [=, this]() {
        if (Type->currentText() == "тип_1") {
            PercentLabel->setText("5");
        } else if (Type->currentText() == "тип_2") {
            PercentLabel->setText("10");
        }
    });
    QObject::connect(backButton2, &QPushButton::clicked, [=, this] {CloseDepositWindow();});
    QPushButton *addButton = windows["AddDepositWindow"]->findChild<QPushButton *>("AddDepositButton");
    QObject::connect(addButton, &QPushButton::clicked, [=, this] {AddDepositUi();});


    //DiagramWindow buttons and functionality
    QPushButton *backButton3 = windows["DiagramWindow"]->findChild<QPushButton *>("BackToMenu");
    QObject::connect(backButton3, &QPushButton::clicked, [=, this]() { GetBackToMainWindow("DiagramWindow"); });
    QGraphicsView *Diagram = windows["DiagramWindow"]->findChild<QGraphicsView *>("Diagram");
    QGraphicsScene *scene = new QGraphicsScene;
    Diagram->setScene(scene);
    //Draw circle diagram
    int sum = 0;
    for (auto &i: *Deposits) {
        sum += i->getAmount();
    }
    int startAngle = 0;
    for (auto &i: *Deposits) {
        int angle = (i->getAmount() * 360) / sum;
        scene->addEllipse(0, 0, 200, 200, QPen(Qt::black), QBrush(Qt::red))->setStartAngle(startAngle);
        scene->addEllipse(0, 0, 200, 200, QPen(Qt::black), QBrush(Qt::red))->setSpanAngle(angle);
        startAngle += angle;
    }
}
