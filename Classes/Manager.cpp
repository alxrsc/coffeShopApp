//
// Created by Alexandru Roșca on 04.01.2025.
//

#include "Manager.h"
#include "../Utils/CSVHandler.h"

void Manager::addPersonel() {
    Employee *employee = new Employee();
    // input from the user the first name, last name, working hours and salary
    string firstName;
    string lastName;
    vector< pair<string, string> > workingHours;
    string day;
    string hours;
    string position;
    int salary;
    char option;

    cout << "Enter the first name: ";
    cin >> firstName;
    cout << "Enter the last name: ";
    cin >> lastName;
    cout << "Enter the position: ";
    cin >> position;

    cout << "Enter the working hours: " << endl;
    do {
        cout << "Enter the day: ";
        cin >> day;
        cout << "Enter the hours (hh-hh): ";
        cin >> hours;
        workingHours.push_back(make_pair(day, hours));

        cout << "Do you want to add another day? (y/n): ";
        cin >> option;
    } while (option != 'n');

    cout << "Enter the salary: ";
    cin >> salary;

    employee->setFirstName(firstName);
    employee->setLastName(lastName);
    employee->setPosition(position);
    employee->setWorkingHours(workingHours);
    employee->setSalary(salary);

    // write the employee to the csv using
    CSVHandler::writeEmployee(employee);
}

void Manager::removePersonel(Employee *employee) {
    // remove the employee from the csv using CSVHandler::deleteEmployee(employee)
    CSVHandler::deleteEmployee(employee);
}

void Manager::changeSalary(Employee *employee) {
    try {
        employee = CSVHandler::readEmployee(employee->getFirstName(), employee->getLastName());
        if (employee == nullptr) {
            throw runtime_error("Employee not found");
        }
        cout << "Enter the new salary: ";

        int newSalary;
        cin >> newSalary;

        employee->setSalary(newSalary);
        CSVHandler::editEmployee(employee);
    } catch (const exception& e) {
        cout << e.what() << '\n';
    }

}

void Manager::changePosition(Employee *employee) {
    try {
        employee = CSVHandler::readEmployee(employee->getFirstName(), employee->getLastName());

        if(employee == nullptr) {
            throw runtime_error("Employee not found");
        }

        cout << "Enter the new position: ";

        string newPosition;
        cin >> newPosition;

        employee->setPosition(newPosition);
        CSVHandler::editEmployee(employee);
    } catch(const exception& e) {
        cout << e.what() << '\n';
    }


}

void Manager::changeShift(Employee* employee) {
    // input from the user the new working hours
    vector< pair<string, string> > newWorkingHours;
    string day;
    string hours;

    try {
        employee = CSVHandler::readEmployee(employee->getFirstName(), employee->getLastName());

        if(employee == nullptr) {
            throw runtime_error("Employee not found");
        }

        cout << "Enter the day: ";
        cin >> day;
        cout << "Enter the hours: ";
        cin >> hours;



        newWorkingHours = employee->getWorkingHours();

        bool found = false;
        for(auto &workingHour : newWorkingHours) {
            if(workingHour.first == day) {
                workingHour.second = hours;
                found = true;
            }
        }

        if(!found) {
            newWorkingHours.push_back(make_pair(day, hours));
        }

        employee->setWorkingHours(newWorkingHours);
        CSVHandler::editEmployee(employee);
        
    } catch (const exception& e) {
        cout << e.what() << '\n';
    }


}

void Manager::buyStock() {
    vector< tuple<string, int, int, int>> productToBuy;
    string productName;
    int quantity;
    int sellPrice;
    int buyPrice;

    cout << "Enter the product name: ";
    getline(cin, productName);
    cout << "Enter the quantity: ";
    cin >> quantity;
    cout << "Enter the sell price: ";
    cin >> sellPrice;
    cout << "Enter the buy price: ";
    cin >> buyPrice;

    productToBuy.push_back(make_tuple(productName, quantity, sellPrice, buyPrice));

    int expenses = 0;

    if ( CSVHandler::existsInMenu(productName) ) {
        expenses = CSVHandler::refillStock(productName, quantity, sellPrice, buyPrice);
    }else {
        CSVHandler::addStock(productToBuy);
    }

    CSVHandler::updateDailyExpenses(expenses);
}

void Manager::deleteStock() {
    // input from the user the products to remove
    map<string, int> productsToRemove;
    string productName;
    int quantity;
    char option;

    do {
        cout << "Enter the product name: ";
        getline(cin, productName);
        quantity = 0;

        productsToRemove[productName] = quantity;

        cout << "Do you want to remove another product? (y/n): ";
        cin >> option;
    } while(option != 'n');

    CSVHandler::deleteStock(productsToRemove);
}

void Manager::createEvent() {
    cout << "Enter the date of the event (dd.mm.yyyy): ";
    string date;
    getline(cin, date);

    cout << "Enter the name of the event: ";
    string name;
    getline(cin, name);

    cout << "Enter the total cost: ";
    int cost;
    cin >> cost;

    CSVHandler::writeSpecialEvent(name, date, cost);
}

void Manager::deleteEvent() {
    cout << "Enter the date of the event (dd.mm.yyyy): ";
    string date;
    getline(cin, date);

    cout << "Enter the name of the event: ";
    string name;
    getline(cin, name);

    CSVHandler::deleteSpecialEvent(name, date);
}

int Manager::closeDay(string fileStart, string fileEnd, string date) {
    CSVHandler::writeDailyReport(fileStart, fileEnd, date);
}