//
// Created by Alexandru Roșca on 04.01.2025.
//

#include "Barista.h"

string Barista::language = "";

map<string, int> Barista::prepareOrder(map<string, int> order) {

    map<string, int> auxOrder = order;

    for(auto const& [product, quantity] : order) {
        sleep(2);

        if(Barista::language == "en")
            cout << "Preparing " << quantity << " " << product << endl;
        else if(Barista::language == "ro")
            cout << "Se pregateste " << quantity << " " << product << endl;


        if (CSVHandler::existsInMenu(product)) {
            if(!CSVHandler::checkStock(product, quantity)) {
                int sellPrice;
                int buyPrice;
                CSVHandler::getPrices(product, &sellPrice, &buyPrice);

                int expenses = CSVHandler::refillStock(product, quantity, sellPrice, buyPrice);
                CSVHandler::updateDailyExpenses(expenses);
            }
        }
        else {
            if(Barista::language == "en")
                cout << "Product " << product << " does not exist in the menu" << endl;
            else if(Barista::language == "ro")
                cout << "Produsul " << product << " nu exista in meniu" << endl;

            auxOrder.erase(product);
        }

    }

    if(!auxOrder.empty()) {
        if(Barista::language == "en")
            cout << "Order prepared!" << endl;
        else if(Barista::language == "ro")
            cout << "Comanda pregatita!" << endl;
    }
    else {
        if(Barista::language == "en")
            cout << "Order could not be prepared!" << endl;
        else if(Barista::language == "ro")
            cout << "Comanda nu a putut fi pregatita!" << endl;
    }

    return auxOrder;
}
