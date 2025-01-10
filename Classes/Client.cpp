//
// Created by Alexandru Roșca on 04.01.2025.
//

#include "Client.h"

Client::Client() {
    cout << "Enter your first name: ";
    getline(cin, firstName);

    cout << "Enter your last name: ";
    getline(cin, lastName);

    cout << "Client created!" << endl;
}

Client::~Client() {
    order.clear();
    cout << "Client destroyed!" << endl;
}

void Client::setFirstName(std::string firstName) {
    this->firstName = firstName;
}

void Client::setLastName(std::string lastName) {
    this->lastName = lastName;
}

void Client::setTotal(int total) {
    this->total = total;
}

void Client::setOrder(map<string, int> order) {
    this->order = order;
}

string Client::getFirstName() {
    return firstName;
}

string Client::getLastName() {
    return lastName;
}

int Client::getTotal() {
    return total;
}

map<string, int> Client::getOrder() {
    return order;
}

void Client::requestOrder() {
    order = Server::takeOrder();
}

int Client::requestBill(string paymentType) {
    int total = Server::serveBill(paymentType, order);

    return total;
}

void Client::payBill(string paymentType) {
    // write the order to the CSV file
    cout << "Payment sent!" << "(" << paymentType << ")" << endl;
}