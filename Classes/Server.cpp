//
// Created by Alexandru Roșca on 04.01.2025.
//

#include "Server.h"

map<string, int> Server::takeOrder() {
    map<string, int> order;
    string product;
    int quantity;
    char option;

    do {
        cout << "Enter the product: ";
        cin >> product;
        cout << "Enter the quantity: ";
        cin >> quantity;
        order[product] = quantity;

        cout << "Do you want to add another product? (y/n): ";
        cin >> option;
    } while(option != 'n');

    return order;
}

int Server::serveOrder(map<string, int> order) {
    if(!order.empty()) {
        cout << "Order served to the client!";
        return 0;
    }
    else {
        cout << "No order to serve!";
        return 1;
    }
}

int Server::serveBill(string paymentType, map<string, int> order) {
    // create method to calculate total
    int total = CSVHandler::calculateTotal(order);

    cout << "The total is: " << total << " dollars" << endl;
    cout << "The payment type is: " << paymentType << endl;

    return total;
}

void Server::recievePayment(string paymentType, int total) {
    cout << "Payment received!" << endl;
    cout << "The total was: " << total << " dollars" << endl;
    cout << "The payment type was: " << paymentType << endl;
}