//
// Created by Alexandru Roșca on 04.01.2025.
//

#include "Employee.h"

string Employee::language = "";

Employee::Employee() {}

Employee::Employee(string firstName, string lastName) {
    this->firstName = firstName;
    this->lastName = lastName;
}

Employee::Employee(string firstName, string lastName, string position, int salary,
                   vector< pair<string, string> > workingHours) {
    this->firstName = firstName;
    this->lastName = lastName;
    this->position = position;
    this->salary = salary;
    this->workingHours = workingHours;
}

Employee::~Employee() {
    this->workingHours.clear();
}

void Employee::setFirstName(string firstName) {
    this->firstName = firstName;
}

void Employee::setLastName(string lastName) {
    this->lastName = lastName;
}

void Employee::setPosition(string position) {
    this->position = position;
}

void Employee::setWorkingHours(vector< pair<string, string> > workingHours) {
    this->workingHours = workingHours;
}

void Employee::setSalary(int salary) {
    this->salary = salary;
}

string Employee::getFirstName() {
    return this->firstName;
}

string Employee::getLastName() {
    return this->lastName;
}

string Employee::getPosition() {
    return this->position;
}

vector< pair<string, string> > Employee::getWorkingHours() {
    return this->workingHours;
}

int Employee::getSalary() {
    return this->salary;
}

void Employee::addWorkingHours(string day, string hours) {
    this->workingHours.push_back(make_pair(day, hours));
}

void Employee::removeWorkingHours(string day) {
    for(auto it = this->workingHours.begin(); it != this->workingHours.end(); it++) {
        if(it->first == day) {
            this->workingHours.erase(it);
            break;
        }
    }
}