//
// Created by Alexandru Roșca on 04.01.2025.
//

#include "Server.h"

string Server::language = "";

map<string, int> Server::takeOrder() {
    map<string, int> order;
    string product;
    int quantity;
    char option;

    do {
        if(Server::language == "en") {
            cout << "Enter the product: ";
            getline(cin, product);
            cout << "Enter the quantity: ";
            cin >> quantity;
            order[product] = quantity;

            cout << "Do you want to add another product? (y/n): ";
            cin >> option;
        }
        else if(Server::language == "ro") {
            cout << "Introduceti produsul: ";
            getline(cin, product);
            cout << "Introduceti cantitatea: ";
            cin >> quantity;
            order[product] = quantity;

            cout << "Doriti sa adaugati un alt produs? (d/n): ";
            cin >> option;
        }
    } while(option != 'n');

    return order;
}

int Server::serveOrder(map<string, int> order) {
    if(!order.empty()) {
        cout << CLEAR;
        if(Server::language == "en")
            cout << "Order served to the client!";
        else if(Server::language == "ro")
            cout << "Comanda servita clientului!";
        sleep(2);
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

    cout << CLEAR;

    if(Server::language == "en") {
        cout << "The total is: " << total << " dollars" << endl;
        cout << "The payment type is: " << paymentType << endl;
    }
    else if(Server::language == "ro") {
        cout << "Totalul este: " << total << " dolari" << endl;
        cout << "Tipul platii este: " << paymentType << endl;
    }

    sleep(2);
    return total;
}

void Server::recievePayment(string paymentType, int total) {
    cout << CLEAR;

    if(Server::language == "en") {
        cout << "Payment received!" << endl;
        cout << "Total: " << total << " dollars" << endl;
        cout << "Payment type: " << paymentType << endl;
    }
    else if(Server::language == "ro") {
        cout << "Plata primita!" << endl;
        cout << "Total: " << total << " dolari" << endl;
        cout << "Tipul platii: " << paymentType << endl;
    }

    sleep(2);
}