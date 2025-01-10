//
// Created by Alexandru Roșca on 04.01.2025.
//

#ifndef COFFEE_SHOP_APP_CLIENT_H
#define COFFEE_SHOP_APP_CLIENT_H

#include "Server.h"
#include <string>
#include <map>

using namespace std;

class Client {
    int fidelityScore;
    string firstName;
    string lastName;
    int total;
    map<string, int> order;

public:
    static string language;

    Client();
    ~Client();

    void setFirstName(string firstName);
    void setLastName(string lastName);
    void setTotal(int total);
    void setOrder(map<string, int> order);
    string getFirstName();
    string getLastName();
    int getTotal();
    map<string, int> getOrder();
    void requestOrder();
    int requestBill(string paymentType);
    void payBill(string paymentType);
};


#endif //COFFEE_SHOP_APP_CLIENT_H
