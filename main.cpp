#include "Classes/Employee.h"
#include "Classes/Barista.h"
#include "Classes/Client.h"
#include "Classes/Manager.h"
#include "Utils/CSVHandler.h"

#define CLEAR "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"

using namespace std;

int selectLocation(string* fileStart, string* fileEnd) {
    char location;
    cout << "Please enter the location of the coffee shop: " << endl;
    cout << "1. Brasov" << endl;
    cout << "2. Bucharest" << endl;
    cout << "3. Cluj-Napoca" << endl;
    cout << "4. Iasi" << endl;
    cout << "5. Timisoara" << endl;
    cout << "x. Exit" << endl;
    cin >> location;

    *fileStart = "../Locations/";

    switch (location) {
        case '1':
            *fileStart += "Brasov/";
            *fileEnd = ".brasov.csv";
            break;
        case '2':
            *fileStart += "Bucharest/";
            *fileEnd = ".bucharest.csv";
            break;
        case '3':
            *fileStart += "Cluj-Napoca/";
            *fileEnd = ".clujnapoca.csv";
            break;
        case '4':
            *fileStart += "Iasi/";
            *fileEnd = ".iasi.csv";
            break;
        case '5':
            *fileStart += "Timisoara/";
            *fileEnd = ".timisoara.csv";
            break;
        case 'x':
            return 1;
        default:
            cout << "Invalid location!" << endl;
            break;
    }

    return 0;
}

char selectAccount() {
    char option;
    cout << CLEAR;
    cout << "Choose an account: " << endl;
    cout << "1. Manager" << endl;
    cout << "2. Client" << endl;
    cout << "x. Exit" << endl;
    cin >> option;
    cin.ignore();

    return option;
}

void managerMenu(const string& fileStart, const string& fileEnd, const string& date) {
    char option;
    do {
        cout << CLEAR;
        cout << "Choose an action: " << endl;
        cout << "1. Add employee" << endl;
        cout << "2. Remove employee" << endl;
        cout << "3. Change employee's shift" << endl;
        cout << "4. Change employee's salary" << endl;
        cout << "5. Change employee's position" << endl;
        cout << "6. Buy stock" << endl;
        cout << "7. Delete stock" << endl;
        cout << "8. Create special event" << endl;
        cout << "9. Delete special event" << endl;
        cout << "c. Close day" << endl;
        cout << "b. Back" << endl;
        cin >> option;
        cin.ignore();

        cout << CLEAR;

        Manager manager;
        if(option == '1') {
            CSVHandler::setFileName(fileStart + "employees" + fileEnd);

            manager.addPersonel();
        }
        else if(option == '2') {
            string firstName, lastName;
            cout << "Enter the employee's first name: ";
            getline(cin, firstName);

            cout << "Enter the employee's last name: ";
            getline(cin, lastName);

            CSVHandler::setFileName(fileStart + "employees" + fileEnd);

            manager.removePersonel(new Employee(firstName, lastName));
        }
        else if(option == '3') {
            string firstName, lastName;
            cout << "Enter the employee's first name: ";
            getline(cin, firstName);

            cout << "Enter the employee's last name: ";
            getline(cin, lastName);

            CSVHandler::setFileName(fileStart + "employees" + fileEnd);

            manager.changeShift(new Employee(firstName, lastName));
        }
        else if(option == '4') {
            string firstName, lastName;
            cout << "Enter the employee's first name: ";
            getline(cin, firstName);

            cout << "Enter the employee's last name: ";
            getline(cin, lastName);

            CSVHandler::setFileName(fileStart + "employees" + fileEnd);

            manager.changeSalary(new Employee(firstName, lastName));
        }
        else if(option == '5') {
            string firstName, lastName;
            cout << "Enter the employee's first name: ";
            getline(cin, firstName);

            cout << "Enter the employee's last name: ";
            getline(cin, lastName);

            CSVHandler::setFileName(fileStart + "employees" + fileEnd);

            manager.changePosition(new Employee(firstName, lastName));
        }
        else if(option == '6') {
            CSVHandler::setFileName(fileStart + "stock" + fileEnd);

            manager.buyStock();
        }
        else if(option == '7') {
            CSVHandler::setFileName(fileStart + "stock" + fileEnd);

            manager.deleteStock();
        }
        else if(option == '8') {
            CSVHandler::setFileName(fileStart + "events" + fileEnd);

            manager.createEvent();
        }
        else if(option == '9') {
            CSVHandler::setFileName(fileStart + "events" + fileEnd);

            manager.deleteEvent();
        }
        else if(option == 'c') {
            CSVHandler::setFileName(fileStart + "reports" + fileEnd);

            manager.closeDay(fileStart, fileEnd, date);
        }
    } while(option != 'b');
}

void clientMenu(const string& fileStart, const string& fileEnd, const string& date){
    char option;
    Client client = Client();

    do {
        cout << CLEAR;
        cout << "Choose an action: " << endl;
        cout << "1. Order" << endl;
        cout << "2. Pay bill" << endl;
        cout << "3. Back" << endl;

        cin >> option;
        cin.ignore();

        if(option == '1') {
            client.requestOrder();

            CSVHandler::setFileName(fileStart + "stock" + fileEnd);

            client.setOrder(Barista::prepareOrder(client.getOrder()));

        }
        else if(option == '2') {
            string paymentType;

            cout << "Enter payment type: ";
            cin >> paymentType;

            CSVHandler::setFileName(fileStart + "stock" + fileEnd);
            client.setTotal(client.requestBill(paymentType)) ;

            if(client.getTotal() == 0) {
                cout << "You have no bill to pay!" << endl;
            }
            else {
                CSVHandler::removeStock(client.getOrder());

                CSVHandler::setFileName(fileStart + "orders" + fileEnd);
                CSVHandler::writeOrder(client.getOrder(), client.getFirstName(), client.getLastName(), date,client.getTotal());

                client.payBill(paymentType);
                Server::recievePayment(paymentType, client.getTotal());
                client.setTotal(0);
            }

        }
        else if(client.getTotal() != 0) {
            cout << "You have an unpaid bill!" << endl;
        }
    } while(option != '3' || client.getTotal() != 0);

}

int main() {

    char option;
    string date;

    CSVHandler::setDailyExpenses(0);

    cout << "Welcome to the Coffee Shop App!" << endl;

    cout << "Please enter current date (dd.mm.yyyy): ";
    getline(cin, date);

    do {
        string fileStart;
        string fileEnd;

        if(selectLocation(&fileStart, &fileEnd) == 1)
            break;

        option = selectAccount();

        if(option == '1') {
            managerMenu(fileStart, fileEnd, date);
        }
        else if(option == '2') {
            clientMenu(fileStart, fileEnd, date);
        }

    } while(option != 'x');


    return 0;
}
