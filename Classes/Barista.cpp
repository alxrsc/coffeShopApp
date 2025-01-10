//
// Created by Alexandru Roșca on 04.01.2025.
//

#include "Barista.h"

int Barista::makeCoffee(string coffeeType, string milkType) {
    map<string, int> requiredStock;
    requiredStock["coffee"] = 18;
    requiredStock["milk"] = 150;


    if( !CSVHandler::checkStock(coffeeType, 18) || !CSVHandler::checkStock(milkType, 150) ) {
        cout << "Not enough coffee or milk in stock" << endl;
        return 1;
    }

    // remove the stock used for making the coffee
    CSVHandler::removeStock(requiredStock);

    cout << "Coffee made (" << coffeeType << "," << milkType << ")"<< endl;

    return 0;
}

map<string, int> Barista::prepareOrder(map<string, int> order) {

    map<string, int> auxOrder = order;

    for(auto const& [product, quantity] : order) {
        sleep(1);
        cout << "Preparing " << quantity << " " << product << endl;
        // if the client ordered coffee, check the type of coffee and milk wanted
        // if there is not enough coffee or milk in stock, remove the product from the order
        if(product == "coffee") {
            // input from the user the type of coffee and type of meal wished
            string coffeeType;
            string milkType;

            cout << "Enter the type of coffee: ";
            cin >> coffeeType;
            cout << "Enter the type of milk: ";
            cin >> milkType;

            if(!CSVHandler::checkStock(coffeeType, 18) || !CSVHandler::checkStock(milkType, 150))
            {
                cout << "Not enough coffee or milk in stock" << endl;
                auxOrder.erase(product);
            }
            else {
                Barista::makeCoffee(coffeeType, milkType);
            }

        }
        else if (CSVHandler::existsInMenu(product)) {
            if(!CSVHandler::checkStock(product, quantity)) {
                int sellPrice;
                int buyPrice;
                CSVHandler::getPrices(product, &sellPrice, &buyPrice);

                int expenses = CSVHandler::refillStock(product, quantity, sellPrice, buyPrice);
                CSVHandler::updateDailyExpenses(expenses);
            }
        }
        else {
            cout << "Product " << product << " does not exist in the menu" << endl;
            auxOrder.erase(product);
        }

    }

    if(!auxOrder.empty()) {
        cout << "Order prepared!" << endl;
    }
    else {
        cout << "No order to prepare!" << endl;
    }

    return auxOrder;
}
