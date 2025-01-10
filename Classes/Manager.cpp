//
// Created by Alexandru Roșca on 04.01.2025.
//

#include "Manager.h"
#include "../Utils/CSVHandler.h"

string Manager::language = "";

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

    if(Manager::language == "en") {
        cout << "Enter the first name: ";
        getline(cin, firstName);
        cout << "Enter the last name: ";
        getline(cin, lastName);
        cout << "Enter the position: ";
        getline(cin, position);

        cout << "Enter the working hours " << endl;
        do {
            cout << "Enter the day: ";
            getline(cin, day);
            cout << "Enter the hours (hh-hh): ";
            getline(cin, hours);
            workingHours.push_back(make_pair(day, hours));

            cout << "Do you want to add another day? (y/n): ";
            cin >> option;
        } while (option != 'n');

        cout << "Enter the salary: ";
        cin >> salary;
    }
    else if(Manager::language == "ro") {
        cout << "Introduceti prenumele: ";
        getline(cin, firstName);
        cout << "Introduceti numele: ";
        getline(cin, lastName);
        cout << "Introduceti postul: ";
        getline(cin, position);

        cout << "Introduceti programul angajatului " << endl;
        do {
            cout << "Introduceti ziua: ";
            getline(cin, day);
            cout << "Introduceti orele (hh-hh): ";
            getline(cin, hours);
            workingHours.push_back(make_pair(day, hours));

            cout << "Doriti sa adaugati alta zi? (d/n) ";
            cin >> option;
        } while (option != 'n');

        cout << "Introduceti salariul: ";
        cin >> salary;
    }


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
    if(Manager::language == "en") {
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
    else if(Manager::language == "ro") {
        try {
            employee = CSVHandler::readEmployee(employee->getFirstName(), employee->getLastName());
            if (employee == nullptr) {
                throw runtime_error("Angajatul nu a fost gasit");
            }
            cout << "Introduceti noul salariu: ";

            int newSalary;
            cin >> newSalary;

            employee->setSalary(newSalary);
            CSVHandler::editEmployee(employee);
        } catch (const exception& e) {
            cout << e.what() << '\n';
        }
    }

}

void Manager::changePosition(Employee *employee) {
    try {
        employee = CSVHandler::readEmployee(employee->getFirstName(), employee->getLastName());

        if(Manager::language == "en") {
            if(employee == nullptr) {
                throw runtime_error("Employee not found");
            }

            cout << "Enter the new position: ";
        }
        else if(Manager::language == "ro") {
            if(employee == nullptr) {
                throw runtime_error("Angajatul nu a fost gasit");
            }

            cout << "Introduceti noul post: ";
        }

        string newPosition;
        getline(cin, newPosition);

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

        if(Manager::language == "en") {
            if(employee == nullptr) {
                throw runtime_error("Employee not found");
            }

            cout << "Enter the day: ";
            getline(cin, day);
            cout << "Enter the hours: ";
            getline(cin, hours);
        }
        else if(Manager::language == "ro") {
            if(employee == nullptr) {
                throw runtime_error("Angajatul nu a fost gasit");
            }

            cout << "Introduceti ziua: ";
            getline(cin, day);
            cout << "Introduceti orele de lucru (hh-hh): ";
            getline(cin, hours);
        }

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

    if(Manager::language == "en") {
        cout << "Enter the product name: ";
        getline(cin, productName);
        cout << "Enter the quantity: ";
        cin >> quantity;
        cout << "Enter the sell price: ";
        cin >> sellPrice;
        cout << "Enter the buy price: ";
        cin >> buyPrice;
    }
    else if(Manager::language == "ro") {
        cout << "Introduceti numele produsului: ";
        getline(cin, productName);
        cout << "Introduceti cantitatea: ";
        cin >> quantity;
        cout << "Introduceti pretul de vanzare: ";
        cin >> sellPrice;
        cout << "Introduceti pretul de cumparare: ";
        cin >> buyPrice;
    }

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
        if(Manager::language == "en")
            cout << "Enter the product name: ";
        else if(Manager::language == "ro")
            cout << "Introduceti numele produsului: ";

        getline(cin, productName);
        quantity = 0;

        productsToRemove[productName] = quantity;

        if(Manager::language == "en")
            cout << "Do you want to remove another product? (y/n): ";
        else if(Manager::language == "ro")
            cout << "Doriti sa stergeti un alt produs? (d/n): ";
        cin >> option;

    } while(option != 'n');

    CSVHandler::deleteStock(productsToRemove);
}

void Manager::createEvent() {
    if(Manager::language == "en")
        cout << "Enter the date of the event (dd.mm.yyyy): ";
    else if(Manager::language == "ro")
        cout << "Introduceti data evenimentului (zz.ll.aaaa): ";
    string date;
    getline(cin, date);

    if(Manager::language == "en")
        cout << "Enter the name of the event: ";
    else if(Manager::language == "ro")
        cout << "Introduceti numele evenimentului: ";
    string name;
    getline(cin, name);

    if(Manager::language == "en")
        cout << "Enter the total cost: ";
    else if(Manager::language == "ro")
        cout << "Introduceti costul total: ";
    int cost;
    cin >> cost;

    CSVHandler::writeSpecialEvent(name, date, cost);
}

void Manager::deleteEvent() {
    if(Manager::language == "en")
        cout << "Enter the date of the event (dd.mm.yyyy): ";
    else if(Manager::language == "ro")
        cout << "Introduceti data evenimentului (zz.ll.aaaa): ";
    string date;
    getline(cin, date);

    if(Manager::language == "en")
        cout << "Enter the name of the event: ";
    else if(Manager::language == "ro")
        cout << "Introduceti numele evenimentului: ";
    string name;
    getline(cin, name);

    CSVHandler::deleteSpecialEvent(name, date);
}

int Manager::closeDay(string fileStart, string fileEnd, string date) {
    CSVHandler::writeDailyReport(fileStart, fileEnd, date);
}