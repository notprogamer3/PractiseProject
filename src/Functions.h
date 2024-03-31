//
// Created by rdast on 24.03.2024.
//

#ifndef PRACTICA2_QT_FUNCTIONS_H
#define PRACTICA2_QT_FUNCTIONS_H
#include "Deposit.h"
#include "vector"
#include "memory"
#include "iostream"


void InputIntCheck(int &Number, int left = 0, int right = 0, int *skip = nullptr);


namespace DepositFunctions {
    void SaveData(vector<shared_ptr<Deposit>> *Deps);
    void LoadData(vector<shared_ptr<Deposit>> *Deps);
    void AddDeposit(vector<shared_ptr<Deposit>>*);
    void TestingData(vector<shared_ptr<Deposit>> *Deps);
    void Search(vector<shared_ptr<Deposit>> *Deps);
    void Delete(vector<shared_ptr<Deposit>> *Deps);
}

#endif //PRACTICA2_QT_FUNCTIONS_H
