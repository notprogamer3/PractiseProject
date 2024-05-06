//
// Created by rdast on 13.04.2024.
//
#include "QtUiTools"
#include "SetupUi.h"
#include "QWidget"
#include "string"
#include "Functions.h"
#include "Deposit.h"
#include "unordered_map"
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
        app->setStyle("windows11"); // fusion other option (win11 currently bugged)
        button->setText("Светлая тема");
    }
}


void Ui::DrawTable() {
    QTableWidget *Table = windows["TableWindow"]->findChild<QTableWidget *>("Table");
    qDebug() << "tavle init" << Table->rowCount();
    for (int i = 0; i < Table->rowCount(); ++i) {
        Table->setRowHidden(i, false);
    }
    Table->sortByColumn(0, Qt::AscendingOrder);
    Table->clear();
    Table->setColumnCount(10);
    Table->setHorizontalHeaderItem(0, new QTableWidgetItem("Логин"));
    Table->setHorizontalHeaderItem(1, new QTableWidgetItem("И.Ф."));
    Table->setHorizontalHeaderItem(2, new QTableWidgetItem("Телефон"));
    Table->setHorizontalHeaderItem(3, new QTableWidgetItem("Email"));
    Table->setHorizontalHeaderItem(4, new QTableWidgetItem("Тип вклада"));
    Table->setHorizontalHeaderItem(5, new QTableWidgetItem("Срок в месяцах"));
    Table->setHorizontalHeaderItem(6, new QTableWidgetItem("Сумма"));
    Table->setHorizontalHeaderItem(7, new QTableWidgetItem("Процент"));
    Table->setHorizontalHeaderItem(8, new QTableWidgetItem("Доход"));
    Table->setHorizontalHeaderItem(9, new QTableWidgetItem(""));
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
        QPushButton *DeleteButton = new QPushButton("Удалить");
        Table->setCellWidget(i, 9, DeleteButton);
        QObject::connect(DeleteButton, &QPushButton::clicked, [=, this]() {
            DepositFunctions::Delete(Deposits, Deposits->at(i)->getLogin());
            DrawTable();
        });
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

void Ui::ResetDepositWindow() {
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
}


void Ui::AddDeposit() {
    QLineEdit *Name = windows["AddDepositWindow"]->findChild<QLineEdit *>("NameLine");
    QLineEdit *Surname = windows["AddDepositWindow"]->findChild<QLineEdit *>("SurnameLine");
    QLineEdit *Phone = windows["AddDepositWindow"]->findChild<QLineEdit *>("PhoneLine");
    QLineEdit *Email = windows["AddDepositWindow"]->findChild<QLineEdit *>("EmailLine");
    QSlider *Time = windows["AddDepositWindow"]->findChild<QSlider *>("TimeSlider");
    QLineEdit *Amount = windows["AddDepositWindow"]->findChild<QLineEdit *>("AmountLine");
    QLabel *Percent = windows["AddDepositWindow"]->findChild<QLabel *>("PercentLabel");
    QLabel *Error = windows["AddDepositWindow"]->findChild<QLabel *>("ErrorLabel");
    QComboBox *Type = windows["AddDepositWindow"]->findChild<QComboBox *>("TypeOption");
    string s = DepositFunctions::AddDeposit(Deposits, Name->text().toStdString(), Surname->text().toStdString(),
                                            Phone->text().toStdString(), Email->text().toStdString(),
                                            Type->currentText().toStdString(), Amount->text().toInt(),
                                            Time->value(), Percent->text().toInt());
    if (s != "1") {
        Error->setText(QString::fromStdString(s));
    } else {
        DepositFunctions::SaveData(Deposits);
        ResetDepositWindow();
    }
}

void Ui::DrawDiagram(QGraphicsScene *scene) {
    QComboBox *DiagramType = windows["DiagramWindow"]->findChild<QComboBox *>("DiagramType");
    if (DiagramType->currentText() == "Сумме") {
        scene->clear();
        int sum = 0;
        // Calculate sum of all deposits and Top10 deposits
        vector<shared_ptr<Deposit> > Top10;
        for (auto &i: *Deposits) {
            if (Top10.size() < 10) {
                Top10.push_back(i);
            } else {
                for (int j = 0; j < Top10.size(); j++) {
                    if (Top10[j]->getAmount() < i->getAmount()) {
                        Top10[j] = i;
                        break;
                    }
                }
            }
        }
        std::sort(Top10.begin(), Top10.end(), [](const shared_ptr<Deposit> &a, const shared_ptr<Deposit> &b) {
            return a->getAmount() > b->getAmount();
        });
        int startAngle = 0;
        for (auto &i: *Deposits) {
            sum += i->getAmount();
        }
        // Draw top 10 deposits in a circle diagram
        QGraphicsEllipseItem *elips;
        QGraphicsTextItem *text;
        double percent;
        const QColor colors[10] = {
            Qt::red, Qt::green, Qt::blue, Qt::yellow, Qt::cyan, Qt::magenta, Qt::gray, Qt::darkRed, Qt::darkGreen,
            Qt::darkBlue
        };
        for (int i = Top10.size() - 1; i != -1; i--) {
            percent = (Top10[i]->getAmount() * 1.0 * 340 * 16) / sum + 32;
            elips = scene->addEllipse(0, -155, 300, 300, QPen(Qt::black), QBrush(colors[i]));
            elips->setStartAngle(startAngle);
            elips->setSpanAngle(percent);
            startAngle += percent;
            text = scene->addText(QString::fromStdString(Top10[i]->getLogin()));
            text->setPos(500, -155 + i * 20);
            text->setDefaultTextColor(colors[i]);
        }
    } else if (DiagramType->currentText() == "Типу") {
        scene->clear();
        int t1 = 0, t2 = 0, t3 = 0;
        for (auto &i: *Deposits) {
            if (i->getType() == "тип_1") {
                t1++;
            } else if (i->getType() == "тип_2") {
                t2++;
            } else {
                t3++;
            }
        }
        // Draw diagram of deposit types
        QGraphicsEllipseItem *elips;
        double percent, startAngle;
        elips = scene->addEllipse(0, -155, 300, 300, QPen(Qt::black), QBrush(Qt::red));
        percent = (t1 * 1.0 * 360 * 16) / (t1 + t2 + t3);
        elips->setSpanAngle(percent);
        startAngle += percent;
        QGraphicsTextItem *text1 = scene->addText(QString::fromStdString("Тип 1"));
        text1->setPos(500, -155);
        text1->setDefaultTextColor(Qt::red);
        elips = scene->addEllipse(0, -155, 300, 300, QPen(Qt::black), QBrush(Qt::green));
        percent = (t2 * 1.0 * 360 * 16) / (t1 + t2 + t3);
        elips->setStartAngle(startAngle);
        elips->setSpanAngle(percent);
        startAngle += percent;
        QGraphicsTextItem *text2 = scene->addText(QString::fromStdString("Тип 2"));
        text2->setPos(500, -135);
        text2->setDefaultTextColor(Qt::green);
        elips = scene->addEllipse(0, -155, 300, 300, QPen(Qt::black), QBrush(Qt::blue));
        percent = (t3 * 1.0 * 360 * 16) / (t1 + t2 + t3);
        elips->setStartAngle(startAngle);
        elips->setSpanAngle(percent);
        QGraphicsTextItem *text3 = scene->addText(QString::fromStdString("Тип 3"));
        text3->setPos(500, -115);
        text3->setDefaultTextColor(Qt::blue);
    }
}


//TODO загнать в отедльные функции все что написано черезе лямбду
void Ui::SetupWindows() {
    // Load all windows and vars
    const std::string windowsNames[] = {"AddDepositWindow", "TableWindow", "DiagramWindow"};
    windows["AddDepositWindow"] = loadUiFile(nullptr, "../Ui/Добавление вклада.ui");
    windows["TableWindow"] = loadUiFile(nullptr, "../Ui/Таблица.ui");
    windows["DiagramWindow"] = loadUiFile(nullptr, "../Ui/Диаграмма.ui");
    QGraphicsScene *scene = new QGraphicsScene;
    main->takeCentralWidget();
    main->setCentralWidget(tabWidget);
    DrawTable();
    tabWidget->addTab(windows["TableWindow"], "Таблица");
    tabWidget->addTab(windows["AddDepositWindow"], "Добавление вклада");
    tabWidget->addTab(windows["DiagramWindow"], "Диаграмма");
    main->show();
    main->setFixedWidth(1250);
    main->setFixedHeight(810);


    // TableWindow buttons and functionality
    qDebug() << "TableWindowINIT";
    //Change theme
    QPushButton *ChangeThemeButton = windows["TableWindow"]->findChild<QPushButton *>("ChangeTheme");
    QObject::connect(ChangeThemeButton, &QPushButton::clicked, [this, ChangeThemeButton] { ChangeTheme(ChangeThemeButton); });
    //Search
    QPushButton *seatchButton = windows["TableWindow"]->findChild<QPushButton *>("SearchButton");
    QObject::connect(seatchButton, &QPushButton::clicked, [this] { TableSearch(); });
    //Sorting
    QTableWidget *Table = windows["TableWindow"]->findChild<QTableWidget *>("Table");
    Table->setSortingEnabled(false);
    QObject::connect(Table->horizontalHeader(), &QHeaderView::sectionClicked, [=, this](const int logicalIndex) {
        if (logicalIndex >= 4 and logicalIndex <= 6) {
            Table->sortByColumn(logicalIndex, Qt::AscendingOrder);
        } else if (logicalIndex == 0) {
            DrawTable();
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
    qDebug() << "DepositWindowINIT";
    QPushButton *ResetFieldsButton = windows["AddDepositWindow"]->findChild<QPushButton *>("ResetFields");
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
    //Resetting fields
    QObject::connect(ResetFieldsButton, &QPushButton::clicked, [=, this]() { ResetDepositWindow(); });
    //Adding deposit
    QPushButton *addButton = windows["AddDepositWindow"]->findChild<QPushButton *>("AddDepositButton");
    QObject::connect(addButton, &QPushButton::clicked, [this] { AddDeposit(); });


    //DiagramWindow buttons and functionality
    qDebug() << "DiagramWindowINIT";
    QComboBox *DiagramType = windows["DiagramWindow"]->findChild<QComboBox *>("DiagramType");
    QGraphicsView *Diagram = windows["DiagramWindow"]->findChild<QGraphicsView *>("Diagram");
    Diagram->setScene(scene);
    QObject::connect(DiagramType, &QComboBox::currentTextChanged, [=, this]() {
        DrawDiagram(scene);
    });



    //Switching tabs events
    QObject::connect(tabWidget, &QTabWidget::tabBarClicked, [=, this](const int index) {
        int current = tabWidget->currentIndex();
        //Save data on table switch and clear fields
        if (current == 0) {
            QLineEdit *SearchLine = windows["TableWindow"]->findChild<QLineEdit *>("SearchLine");
            QComboBox *SearchType = windows["TableWindow"]->findChild<QComboBox *>("SearchType");
            QRadioButton *EditToggle = windows["TableWindow"]->findChild<QRadioButton *>("EditToggle");
            EditToggle->setChecked(false);
            SearchLine->clear();
            SearchType->setCurrentIndex(0);
            DepositFunctions::SaveData(Deposits);
        }
        if (index == 0) {
            DrawTable();
        } else if (index == 1) {
            ResetDepositWindow();
        } else if (index == 2) {
            DrawDiagram(scene);
        }
    });
}
