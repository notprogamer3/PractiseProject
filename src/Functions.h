//
// Created by rdast on 24.03.2024.
//

#ifndef PRACTICA2_QT_FUNCTIONS_H
#define PRACTICA2_QT_FUNCTIONS_H
#include "Deposit.h"
#include "vector"
#include "memory"
#include "iostream"

//---------------------------------------------------------
// Функция для проверки ввода целого числа (диапозон и введено ли число)
void InputIntCheck(int &Number, int left = 0, int right = 0, int *skip = nullptr);

//---------------------------------------------------------
// Пространство имен функций для работы с вкладами
// Все функции принимают указатель на массив указателей на вклады
namespace DepositFunctions {

    // Сохранение данных в файл
    void SaveData(vector<shared_ptr<Deposit>> *Deps);

    // Загрузка данных из файла
    void LoadData(vector<shared_ptr<Deposit>> *Deps);

    // Добавление вклада
    string AddDeposit(vector<shared_ptr<Deposit>> *, string login, string name, string surname, string phone, string email, string type, int sum, int percent, int time);

    // Вывод данных
    void TestingData(vector<shared_ptr<Deposit>> *Deps);

    // Поиск вклада
    vector<shared_ptr<Deposit>> *Search(vector<shared_ptr<Deposit>> *Deps, string type, string data);

    // Удаление вклада
    void Delete(vector<shared_ptr<Deposit>> *Deps, string Login);

}

#endif //PRACTICA2_QT_FUNCTIONS_H
