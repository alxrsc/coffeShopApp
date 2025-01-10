//
// Created by Alexandru Roșca on 04.01.2025.
//

#ifndef COFFEE_SHOP_APP_SERVER_H
#define COFFEE_SHOP_APP_SERVER_H

#include "Employee.h"
#include "../Utils/CSVHandler.h"


class Server : public Employee {
    int total;
    string paymentType;
    map<string, int> order;

public:
    static map<string, int> takeOrder();
    static int serveOrder(map<string, int> order);
    static int serveBill(string paymentType, map<string, int> order);
    static void recievePayment(string paymentType, int total);
};


#endif //COFFEE_SHOP_APP_SERVER_H
