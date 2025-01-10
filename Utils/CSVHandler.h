//
// Created by Alexandru Roșca on 04.01.2025.
//

#ifndef COFFEE_SHOP_APP_CSVHANDLER_H
#define COFFEE_SHOP_APP_CSVHANDLER_H

#define CLEAR "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"

#include "../Classes/Employee.h"
#include "Utils.cpp"
#include <iostream>
#include <fstream>
#include <unistd.h>


class CSVHandler {

    static string fileName;
    static int dailyExpenses;
    
public:
    static void setFileName(string fileName);
    static string getFileName();

    static void setDailyExpenses(int expenses);
    static int getDailyExpenses();
    static void updateDailyExpenses(int expenses);

    static void writeEmployee(Employee* employee);
    static void deleteEmployee(Employee* employee);
    static Employee* readEmployee(string firstName, string lastName);
    static void editEmployee(Employee* employee);

    static int addStock(vector<tuple<string, int, int, int> > productsToAdd);
    static map<string, int> removeStock(map<string, int> productsToRemove);
    static map<string, int> deleteStock(map<string, int> productsToDelete);
    static int refillStock(string productName, int quantity, int sellPrice, int buyPrice);
    static bool checkStock(string productName, int quantity);
    static bool existsInMenu(string productName);
    static bool getPrices(string productName, int* sellPrice, int* buyPrice);


    static void writeOrder(map<string, int> order, string clientFirstName, string clientLastName, string date, int total);
    static int calculateTotal(map<string, int> order);
    static int calculateFidelityScore(string clientFirstName, string clientLastName);

    static void writeSpecialEvent(string eventName, string date, int cost);
    static void deleteSpecialEvent(string eventName, string date);

    static int readSalariesForToday(string date);
    static int readDaysIncome(string date);
    static void writeDailyReport(string fileStart, string fileEnd, string date);
};


#endif //COFFEE_SHOP_APP_CSVHANDLER_H
