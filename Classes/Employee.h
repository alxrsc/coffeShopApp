//
// Created by Alexandru Roșca on 04.01.2025.
//

#ifndef COFFEE_SHOP_APP_EMPLOYEE_H
#define COFFEE_SHOP_APP_EMPLOYEE_H

#include <iostream>
#include <string>
#include <map>

using namespace std;

class Employee {
    string firstName;
    string lastName;
    string position;
    int salary; // dollars per hour
    // working hours map <string, string> day and hours
    vector< pair<string, string> > workingHours;


public:
    static string language;
    Employee();
    Employee(string firstName, string lastName);
    Employee(string firstName, string lastName, string position, int salary, vector< pair<string, string> > workingHours);

    ~Employee();

    void setFirstName(string firstName);
    void setLastName(string lastName);
    void setPosition(string position);
    void setWorkingHours(vector< pair<string, string> > workingHours);
    void setSalary(int salary);

    string getFirstName();
    string getLastName();
    string getPosition();
    vector< pair<string, string> > getWorkingHours();
    int getSalary();

    void addWorkingHours(string day, string hours);
    void removeWorkingHours(string day);
};


#endif //COFFEE_SHOP_APP_EMPLOYEE_H
