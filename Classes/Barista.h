//
// Created by Alexandru Roșca on 04.01.2025.
//

#ifndef COFFEE_SHOP_APP_BARISTA_H
#define COFFEE_SHOP_APP_BARISTA_H

#include "Employee.h"
#include "Server.h"
#include "../Utils/CSVHandler.h"

#include <iostream>

// Concept POO: mostenire
class Barista : public Employee {

public:
    static string language;
    static map<string, int> prepareOrder(map<string, int> order);
};

#endif //COFFEE_SHOP_APP_BARISTA_H
