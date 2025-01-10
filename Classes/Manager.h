//
// Created by Alexandru Roșca on 04.01.2025.
//

#ifndef COFFEE_SHOP_APP_MANAGER_H
#define COFFEE_SHOP_APP_MANAGER_H

#include "Employee.h"
#include "../Utils/CSVHandler.h"

class Manager : public Employee {

public:

    void addPersonel();
    void removePersonel(Employee* employee);
    void changeSalary(Employee* employee);
    void changePosition(Employee* employee);
    void changeShift(Employee* employee);
    void buyStock();
    void deleteStock();
    void createEvent();
    void deleteEvent();
    int closeDay(string fileStart, string fileEnd, string date);
};


#endif //COFFEE_SHOP_APP_MANAGER_H
