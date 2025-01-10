#include "Classes/Employee.h"
#include "Classes/Barista.h"
#include "Classes/Client.h"
#include "Classes/Manager.h"
#include "Utils/CSVHandler.h"

#define CLEAR "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"

using namespace std;

int selectLanguage() {
    char language;
    cout << "Please select a language: " << endl;
    cout << "1. English" << endl;
    cout << "2. Romanian" << endl;
    cout << "x. Exit" << endl;
    cin >> language;
    cin.ignore();

    if (language == '1') {
        return 1;
    } else if (language == '2') {
        return 2;
    } else if (language == 'x') {
        return 3;
    } else {
        cout << "Invalid language!" << endl;
        return 0;
    }
}

int selectLocationEN(string* fileStart, string* fileEnd) {
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
            *fileStart += "Brasov/EN/";
            *fileEnd = ".brasov.csv";
            break;
        case '2':
            *fileStart += "Bucharest/EN/";
            *fileEnd = ".bucharest.csv";
            break;
        case '3':
            *fileStart += "Cluj-Napoca/EN/";
            *fileEnd = ".clujnapoca.csv";
            break;
        case '4':
            *fileStart += "Iasi/EN/";
            *fileEnd = ".iasi.csv";
            break;
        case '5':
            *fileStart += "Timisoara/EN/";
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

int selectLocationRO(string* fileStart, string* fileEnd) {
    char location;
    cout << "Va rugam sa introduceti locatia cafenelei: " << endl;
    cout << "1. Brasov" << endl;
    cout << "2. Bucuresti" << endl;
    cout << "3. Cluj-Napoca" << endl;
    cout << "4. Iasi" << endl;
    cout << "5. Timisoara" << endl;
    cout << "x. Iesire" << endl;
    cin >> location;

    *fileStart = "../Locations/";

    switch (location) {
        case '1':
            *fileStart += "Brasov/RO/";
            *fileEnd = ".ro.brasov.csv";
            break;
        case '2':
            *fileStart += "Bucharest/RO/";
            *fileEnd = ".ro.bucuresti.csv";
            break;
        case '3':
            *fileStart += "Cluj-Napoca/RO/";
            *fileEnd = ".ro.clujnapoca.csv";
            break;
        case '4':
            *fileStart += "Iasi/RO";
            *fileEnd = ".ro.iasi.csv";
            break;
        case '5':
            *fileStart += "Timisoara/RO/";
            *fileEnd = ".ro.timisoara.csv";
            break;
        case 'x':
            return 1;
        default:
            cout << "Locatie invalida!" << endl;
            break;
    }

    return 0;
}

char selectAccountEN() {
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

char selectAccountRO() {
    char option;
    cout << CLEAR;
    cout << "Alegeti un cont: " << endl;
    cout << "1. Manager" << endl;
    cout << "2. Client" << endl;
    cout << "x. Iesire" << endl;
    cin >> option;
    cin.ignore();

    return option;
}

void managerMenuEN(const string& fileStart, const string& fileEnd, const string& date) {
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

void managerMenuRO(const string& fileStart, const string& fileEnd, const string& date) {
    char option;
    do {
        cout << CLEAR;
        cout << "Alegeti o actiune: " << endl;
        cout << "1. Adauga angajat" << endl;
        cout << "2. Sterge angajat" << endl;
        cout << "3. Schimba tura unui angajat" << endl;
        cout << "4. Schimba salariul unui angajat" << endl;
        cout << "5. Schimba postul unui angajat" << endl;
        cout << "6. Cumpara produse" << endl;
        cout << "7. Sterge produse" << endl;
        cout << "8. Creaza eveniment special" << endl;
        cout << "9. Sterge eveniment special" << endl;
        cout << "c. Inchide casa" << endl;
        cout << "b. Inapoi" << endl;
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

void clientMenuEN(const string& fileStart, const string& fileEnd, const string& date){
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

void clientMenuRO(const string& fileStart, const string& fileEnd, const string& date){
    char option;
    Client client = Client();

    do {
        cout << CLEAR;
        cout << "Alegeti o actiune: " << endl;
        cout << "1. Comanda" << endl;
        cout << "2. Plateste nota" << endl;
        cout << "3. Inapoi" << endl;

        cin >> option;
        cin.ignore();

        if(option == '1') {
            client.requestOrder();

            CSVHandler::setFileName(fileStart + "stock" + fileEnd);

            client.setOrder(Barista::prepareOrder(client.getOrder()));

        }
        else if(option == '2') {
            string paymentType;

            cout << "Introduceti tipul platii: ";
            cin >> paymentType;

            CSVHandler::setFileName(fileStart + "stock" + fileEnd);
            client.setTotal(client.requestBill(paymentType)) ;

            if(client.getTotal() == 0) {
                cout << "Nu aveti nimic de platit!" << endl;
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
            cout << "Aveti o nota neplatita!" << endl;
        }
    } while(option != '3' || client.getTotal() != 0);

}

void englishMenu() {
    Employee::language = "en";
    Manager::language = "en";
    Server::language = "en";
    Barista::language = "en";
    Client::language = "en";

    char option;
    string date;

    cout << "Welcome to the Coffee Shop App!" << endl;

    cout << "Please enter current date (dd.mm.yyyy): ";
    getline(cin, date);

    do {
        string fileStart;
        string fileEnd;

        if(selectLocationEN(&fileStart, &fileEnd) == 1)
            break;

        option = selectAccountEN();

        if(option == '1') {
            managerMenuEN(fileStart, fileEnd, date);
        }
        else if(option == '2') {
            clientMenuEN(fileStart, fileEnd, date);
        }

    } while(option != 'x');
}

void romanianMenu() {
    Employee::language = "ro";
    Manager::language = "ro";
    Server::language = "ro";
    Barista::language = "ro";
    Client::language = "ro";

    char option;
    string date;

    cout << CLEAR;
    cout << "Bun venit in aplicatia cafenelei!" << endl;
    sleep(2);

    cout << CLEAR;
    cout << "Va rugam sa introduceti data de azi (zz.ll.aaaa): ";
    getline(cin, date);
    sleep(1);

    do {
        string fileStart;
        string fileEnd;

        cout << CLEAR;
        if(selectLocationRO(&fileStart, &fileEnd) == 1)
            break;
        sleep(1);

        option = selectAccountRO();
        sleep(1);

        if(option == '1') {
            cout << CLEAR;
            managerMenuRO(fileStart, fileEnd, date);
            sleep(1);
        }
        else if(option == '2') {
            cout << CLEAR;
            clientMenuRO(fileStart, fileEnd, date);
            sleep(1);
        }

    } while(option != 'x');
}

int main() {

    int language;


    CSVHandler::setDailyExpenses(0);

    do {
        language = selectLanguage();

        if(language == 1) { englishMenu(); }
        else if (language == 2) { romanianMenu(); }
        else if(language == 3) { return 0; }

    } while(language == 0);






    return 0;
}
