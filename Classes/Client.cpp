//
// Created by Alexandru Roșca on 04.01.2025.
//

#include "Client.h"

string Client::language = "";

Client::Client() {
    if(Client::language == "en") {
        cout << "Enter your first name: ";
        getline(cin, firstName);

        cout << "Enter your last name: ";
        getline(cin, lastName);

        cout << "Client created!" << endl;
    }
    else if(Client::language == "ro") {
        cout << "Introduceti prenumele: ";
        getline(cin, firstName);

        cout << "Introduceti numele: ";
        getline(cin, lastName);

        cout << "Client creat!" << endl;
    }

}

Client::~Client() {
    order.clear();
    if(Client::language == "en")
        cout << "Client destroyed!" << endl;
    else if(Client::language == "ro")
        cout << "Client distrus!" << endl;
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
    cout << CLEAR;

    if(Client::language == "en")
        cout << "Payment sent!" << "(" << paymentType << ")" << endl;
    else if(Client::language == "ro")
        cout << "Plata trimisa!" << "(" << paymentType << ")" << endl;

    sleep(3);
}