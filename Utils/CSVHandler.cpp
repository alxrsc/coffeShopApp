//
// Created by Alexandru Roșca on 04.01.2025.
//

#include "CSVHandler.h"

string CSVHandler::fileName = "";

int CSVHandler::dailyExpenses = 0;

void CSVHandler::setFileName(string newFileName) {
    fileName = newFileName;
}

string CSVHandler::getFileName() {
    return fileName;
}

void CSVHandler::setDailyExpenses(int expenses) {
    dailyExpenses = expenses;
}

int CSVHandler::getDailyExpenses() {
    return dailyExpenses;
}

void CSVHandler::updateDailyExpenses(int expenses) {
    dailyExpenses += expenses;
}

void CSVHandler::writeEmployee(Employee *employee) {
    ofstream file;

    try{
        file.open(fileName, ios_base::app);
        if(!file.is_open()) {
            throw runtime_error("Could not open file");
        }
    }
    catch(const exception& e){
        cerr << e.what() << '\n';
    }

    file << endl << employee->getFirstName() << "," << employee->getLastName() << "," << employee->getPosition() << "," << employee->getSalary();

    cout << "Writing employee " << employee->getFirstName() << " " << employee->getLastName() << endl;

    for(auto const& [day, hours] : employee->getWorkingHours()) {
        file << "," << day << "," << hours;
    }

    file.close();
}

void CSVHandler::deleteEmployee(Employee *employee) {
    ifstream file;
    file.open(fileName);

    cout << CLEAR;

    if(!file.is_open()) {
        cout << "Could not open file!" << endl;
    }

    ofstream temp;
    temp.open("temp.csv");

    string line;
    string firstName = employee->getFirstName();
    string lastName = employee->getLastName();
    bool found = false;

    getline(file, line); // skip the first line
    temp << line;

    while(getline(file, line)) {
        if(line.find(firstName) != string::npos && line.find(lastName) != string::npos) {
            found = true;
            cout << "Deleted employee: " << line << endl;
            continue;
        }
        string aux;

        temp << endl << line ;


    }

    if(!found) {
        cout << "Employee not found! Nothing to delete." << endl;
    }

    file.close();
    temp.close();

    remove(fileName.c_str());
    rename("temp.csv", fileName.c_str());

    sleep(3);
}

Employee* CSVHandler::readEmployee(string firstName, string lastName) {
    ifstream file;

    try {
        file.open(fileName);
        if(!file.is_open()) {
            throw runtime_error("Could not open file");
        }
    } catch(const exception& e) {
        cerr << e.what() << '\n';
    }

    Employee* employee = new Employee();

    string line;
    string fileFirstName;
    string fileLastName;
    string position;
    int salary;
    vector<pair<string, string>> workingHours;
    string aux;
    bool found = false;

    while(getline(file, line)) {
        fileFirstName = line.substr(0, line.find(","));
        aux = line.substr(line.find(',') + 1);
        fileLastName = aux.substr(0, aux.find(","));

        if(fileFirstName == firstName && fileLastName == lastName) {
            found = true;
            aux = line.substr(line.find(",") + 1);
            aux = aux.substr(aux.find(",") + 1);
            position = aux.substr(0, aux.find(","));
            aux = aux.substr(aux.find(",") + 1);
            salary = stoi(aux.substr(0, aux.find(",")));
            aux = aux.substr(aux.find(",") + 1);

            while(aux.find(",") != string::npos) {
                string day = aux.substr(0, aux.find(","));
                aux = aux.substr(aux.find(",") + 1);
                string hours = aux.substr(0, aux.find(","));
                aux = aux.substr(aux.find(",") + 1);
                workingHours.push_back(make_pair(day, hours));
                cout << "Day: " << day << " Hours: " << hours << endl;
            }

            employee->setFirstName(firstName);
            employee->setLastName(lastName);
            employee->setPosition(position);
            employee->setSalary(salary);
            employee->setWorkingHours(workingHours);

        }

    }

    if(!found) {
        cout << "Employee not found!" << endl;
        return nullptr;
    }

    return employee;
}


void CSVHandler::editEmployee(Employee* employee) {
    CSVHandler::deleteEmployee(employee);
    CSVHandler::writeEmployee(employee);
}


int CSVHandler::addStock(vector< tuple<string, int, int, int>> productsToAdd) {
    ofstream file;
    file.open(fileName, ios_base::app);

    int costs = 0;

    for(auto const& [productName, quantity, sellPrice, buyPrice] : productsToAdd) {
        file << endl << productName << "," << quantity << "," << sellPrice << "," << buyPrice;
        costs += quantity*buyPrice;
    }

    file.close();

    return costs;
}

map<string, int> CSVHandler::removeStock(map<string, int> productsToRemove) {
    // first search for already existing stock
    ifstream file;
    file.open(fileName);

    ofstream temp;
    temp.open("temp.csv");

    string line;
    string productName;
    string aux;
    int quantity;
    int sellPrice;
    int buyPrice;

    while(getline(file, line)) {
        productName = line.substr(0, line.find(","));
        aux = line.substr(line.find(",") + 1);
        // if product exists in the stocks, remove the quantity
        if( productsToRemove.count(productName) > 0)
        {

            quantity = stoi(aux.substr(0, aux.find(",")));
            cout << "TEST QUANTITY " << quantity << endl;
            quantity -= productsToRemove[productName];
            cout << "TEST QUANTITY " << quantity << endl;

            aux = aux.substr(aux.find(",") + 1);
            sellPrice = stoi(aux.substr(0, aux.find(",")));

            aux = aux.substr(aux.find(",") + 1);
            buyPrice = stoi(aux);

            temp << productName << "," << quantity << "," << sellPrice << "," << buyPrice << endl;
            productsToRemove.erase(productName);
        }
        else
        {
            temp << line << endl;
        }

    }

    file.close();
    temp.close();

    remove(fileName.c_str());
    rename("temp.csv", fileName.c_str());

    return productsToRemove;
}

map<string, int> CSVHandler::deleteStock(map<string, int> productsToDelete) {
    // first search for already existing stock
    ifstream file;
    file.open(fileName);

    ofstream temp;
    temp.open("temp.csv");

    string line;
    string productName;

    getline(file, line); // skip the header
    temp << line;

    while(getline(file, line)) {

        productName = line.substr(0, line.find(","));
        // if product exists in the stocks, remove the quantity
        if( productsToDelete.count(productName) > 0) { productsToDelete.erase(productName); }
        else { temp << endl << line; }

    }

    file.close();
    temp.close();

    remove(fileName.c_str());
    rename("temp.csv", fileName.c_str());

    return productsToDelete;
}

int CSVHandler::refillStock(string productName, int quantity, int sellPrice, int buyPrice) {
    ifstream file;
    file.open(fileName);

    ofstream temp;
    temp.open("temp.csv");

    string line;
    string product;
    int aux;

    while(getline(file, line)) {
        product = line.substr(0, line.find(","));
        if(product == productName) {
            aux = stoi(line.substr(line.find(",") + 1, line.find(",")));

            cout << "Refilling " << productName << " in stock. Quantity: " << aux << endl;

            temp << productName << "," << aux + quantity << "," << sellPrice << "," << buyPrice << endl;
        }
        else {
            temp << line << endl;
        }
    }

    file.close();
    temp.close();

    remove(fileName.c_str());
    rename("temp.csv", fileName.c_str());

    return quantity*buyPrice;
}

bool CSVHandler::checkStock(string productName, int quantity) {
    ifstream file;
    try {
        file.open(fileName);
        if(!file.is_open()) {
            throw runtime_error("Could not open file");
        }
    } catch(const exception& e) {
        cerr << e.what() << '\n';
        return false;
    }


    string line;
    string tempProductName;
    string aux;
    bool found = false;
    int tempQuantity;

    getline(file, line);

    while(getline(file, line)) {
        tempProductName = line.substr(0, line.find(","));
        aux = line.substr(line.find(",") + 1);
        cout << "Checking " << tempProductName << endl;
        // if product exists in the stocks, check if the needed quantity is available
        if( tempProductName == productName )
        {
            found = true;

            tempQuantity = stoi(aux.substr(0, aux.find(',')));
            cout << "Checking " << productName << " in stock. Quantity: " << tempQuantity << endl;

            if(tempQuantity < quantity) {
                cout << "There is not enough " << productName << " in stock!" << endl;
                return false;
            }
        }
    }

    if(!found) {
        cout << "Product not found in stock!" << endl;
        return false;
    }

    file.close();
    return true;
}

bool CSVHandler::existsInMenu(string productName) {
    ifstream file;
    file.open(fileName);

    string line;
    string aux;

    while(getline(file, line)) {
        aux = line.substr(0, line.find(","));
        if(aux == productName) {
            return true;
        }
    }

    return false;
}

bool CSVHandler::getPrices(string productName, int *sellPrice, int *buyPrice) {
    ifstream file;
    file.open(fileName);

    string line;
    string aux;

    while(getline(file, line)) {
        aux = line.substr(0, line.find(","));
        if(aux == productName) {
            aux = line.substr(line.find(",") + 1);
            aux = aux.substr(aux.find(",") + 1);
            *sellPrice = stoi(aux.substr(0, aux.find(",")));

            aux = aux.substr(aux.find(",") + 1);
            *buyPrice = stoi(aux);
            cout << "Sell price: " << *sellPrice << " Buy price: " << *buyPrice << endl;
            return true;
        }
    }

    return false;
}

void CSVHandler::writeOrder(map<string, int> order, string clientFirstName, string clientLastName, string date, int total) {
    ofstream file;
    file.open(fileName, ios_base::app);

    file << endl << clientFirstName << "," << clientLastName << "," << date << "," << total;

    for(auto const& [product, quantity] : order) {
        file << "," << product << "," << quantity;
    }

    file.close();
}

int CSVHandler::calculateTotal(map<string, int> order) {
    ifstream file;
    file.open(fileName);

    string line;
    string productName;
    int quantity;
    int temp;
    int sellPrice;
    int total = 0;

    while(getline(file, line)) {
        productName = line.substr(0, line.find(","));

        if( order.contains(productName) )
        {
            quantity = order[productName];
            // skip unwanted data
            temp = line.find(",");
            temp = line.find(",", temp + 1);
            sellPrice = stoi(line.substr(temp + 1, line.find(",")));

            cout << "Product: " << productName << " Quantity: " << quantity << " Price: " << sellPrice << endl;
            total += quantity * sellPrice;
        }
    }

    file.close();

    return total;
}

int CSVHandler::calculateFidelityScore(string clientFirstName, string clientLastName) {
    // find how much the client has spent in the past
    ifstream file;
    file.open(fileName);

    string line;
    string firstName;
    string lastName;
    int total;
    int score = 0;

    while(getline(file, line)) {
        firstName = line.substr(0, line.find(","));
        lastName = line.substr(line.find(",") + 1, line.find(","));
        if(firstName == clientFirstName && lastName == clientLastName) {
            total = stoi(line.substr(line.find(",") + 1, line.find(",")));
            score += total;
        }
    }

    file.close();

    // return x% off for the current order
    if(score > 100) {
        return 10;
    }
    else if(score > 50) {
        return 5;
    }
    else {
        return 0;
    }
}

void CSVHandler::writeSpecialEvent(string eventName, string date, int cost) {
    ofstream file;

    try {
        file.open(fileName, ios_base::app);
        if(!file.is_open()) {
            throw runtime_error("Could not open file");
        }
    } catch(const exception& e) {
        cerr << e.what() << '\n';
    }

    file << endl << eventName << "," << date << "," << cost;
}

void CSVHandler::deleteSpecialEvent(string eventName, string date) {
    ifstream file;

    try {
        file.open(fileName);
        if(!file.is_open()) {
            throw runtime_error("Could not open file");
        }
    } catch(const exception& e) {
        cerr << e.what() << '\n';
    }

    ofstream temp;
    temp.open("temp.csv");

    string line;
    string aux;
    string name;
    string eventDate;

    getline(file, line); // skip the header
    temp << line;

    while(getline(file, line)) {
        eventDate = line.substr(0, line.find(","));
        aux = line.substr(line.find(",") + 1);
        name = aux.substr(0, aux.find(","));

        if(eventDate != date || name != eventName) {
            temp << endl << line;
        }
    }

}

string getDayOfWeek(const string& date) {
    // Parse the input date string (dd.mm.yyyy)
    istringstream dateStream(date);
    int day, month, year;
    char dot;
    dateStream >> day >> dot >> month >> dot >> year;

    tm timeStruct = {};
    timeStruct.tm_mday = day;
    timeStruct.tm_mon = month - 1;
    timeStruct.tm_year = year - 1900;

    mktime(&timeStruct);

    const string daysOfWeek[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    return daysOfWeek[timeStruct.tm_wday];
}

int CSVHandler::readSalariesForToday(string date) {
    // Extract the day of the week from the date
    string dayOfWeek = getDayOfWeek(date);

    // Open the file
    ifstream file(fileName);
    if (!file.is_open()) {
        throw runtime_error("Could not open the file.");
    }

    string line;
    int totalSalaries = 0;

    // Process the file line by line
    while (getline(file, line)) {
        stringstream ss(line);
        string field;

        // Extract fields from the CSV line
        vector<string> fields;
        while (getline(ss, field, ',')) {
            fields.push_back(field);
        }

        // Ensure we have enough fields to process
        if (fields.size() < 5) {
            continue; // Skip malformed lines
        }

        string firstName = fields[0];
        string lastName = fields[1];
        string position = fields[2];

        int baseSalary = 0;
        stringstream salaryStream(fields[3]);
        salaryStream >> baseSalary;

        // Extract the working hours
        vector<pair<string, string>> workingHours;
        for (size_t i = 4; i < fields.size(); i += 2) {
            workingHours.emplace_back(fields[i], fields[i + 1]);
        }

        // Find the working hours for the current day of the week
        for (const auto& [day, hours] : workingHours) {
            if (day == dayOfWeek) {
                // Calculate the salary for the current day
                int salary = baseSalary * (stoi(hours.substr(3, 5)) - stoi(hours.substr(0, 2)));
                totalSalaries += salary;
                break;
            }
        }
    }

    return totalSalaries;
}

int CSVHandler::readDaysIncome(string date) {
    ifstream file;

    try{
        file.open(fileName);
        if(!file.is_open()) {
            throw runtime_error("Could not open file");
        }
    } catch(const exception& e){
        cerr << e.what() << '\n';
        return -1;
    }

    string line;
    string aux;
    int total = 0;
    string day;

    // firstName,lastName,date,totalPrice,product,units,product,units...

    while(getline(file, line)) {
        aux = line.substr( line.find(",") + 1);
        aux = aux.substr( aux.find(",") + 1);
        day = aux.substr(0, aux.find(","));
        cout << "Date: " << date << " Day: " << day << endl;

        if(date == day) {
            aux = aux.substr( aux.find(",") + 1, aux.find(","));
            total += stoi(aux);
            cout << "Income: " << total << endl;
        }
    }

    file.close();

    return total;
}

void CSVHandler::writeDailyReport(string fileStart, string fileEnd, string date) {
    ofstream file;

    try {
        file.open(fileName, ios_base::app);
        if(!file.is_open()) {
            throw runtime_error("Could not open file");
        }
    } catch(const exception& e) {
        cerr << e.what() << '\n';
        return;
    }

    int expenses = CSVHandler::getDailyExpenses();

    CSVHandler::setFileName(fileStart + "employees" + fileEnd);
    int salaries = CSVHandler::readSalariesForToday(date);

    CSVHandler::setFileName(fileStart + "orders" + fileEnd);
    int income = CSVHandler::readDaysIncome(date);

    string line;

    file << endl << date << "," << income << "," << expenses << "," << salaries << "," << income - expenses - salaries;

    file.close();
}