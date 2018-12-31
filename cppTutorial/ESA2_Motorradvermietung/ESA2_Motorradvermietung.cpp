#include "pch.h"
#include <iostream>
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <string>
#include <sstream>
#include <list>
using namespace std;

void printMenu();
void printLine();
int getMenuRequest();
bool isMenuSelectionValid(int request);

class Motorbike {
public:
    string name;
    bool isReserved;
    bool isBorrowed;
    Motorbike(string name);
    void print();
};
Motorbike::Motorbike(string name) :name(name) {
    isReserved = false;
    isBorrowed = false;
}
void Motorbike::print() {
    cout << name<<endl;
}





class Customer {
public:
    string name;
    string firstName;
    string street;
    string zipCode;
    string city;
    string birthdate;
    string telephoneNumber;
    bool hasLicenseA;
    friend istream& operator>> (istream& is, Customer& customer);
    friend ostream& operator<< (ostream& os, const Customer& customer);
};
istream& operator>>(istream& is, Customer& customer) {
    cout << "Name:" << endl;
    is >> customer.name;
    cout << "Vorname:" << endl;
    is >> customer.firstName;
    cout << "Adresse" << endl;
    cout << "Strasse:" << endl;
    is >> customer.street;
    cout << "Postleitzahl:" << endl;
    is >> customer.zipCode;
    cout << "Stadt/Ort:" << endl;
    is >> customer.city;
    cout << "Geburtstag:" << endl;
    is >> customer.birthdate;
    cout << "F\x81hrerschein der Klasse A? [y] ja, [n] nein" << endl;
    string license;
    is >> license;
    if (license == "y") {
        customer.hasLicenseA = true;
    }
    else
    {
        customer.hasLicenseA = false;
    }
    return is;
}
ostream& operator<<(ostream& os, const Customer& customer) {
    string license;
    if (customer.hasLicenseA) {
        license = "Ja";
    }
    else
    {
        license = "Nein";
    }
    os << "Name: " << customer.name << ", Vorname:" << customer.firstName << ", Geburtstag: " << customer.birthdate << endl<<"Adresse:" <<endl<<"Strasse: " << customer.street << ", PLZ: " << customer.zipCode << ", Stadt: " << customer.city << endl<<"Hat Führerschein der Klasse A: " << license << endl;
    return os;
}
class Reservation {
public:
    Motorbike *motorbike;
    Customer customer;
    Reservation(Customer customer);
    void addMororbike(Motorbike *motorbike);
};
Reservation::Reservation(Customer customer) :customer(customer) {
    motorbike = NULL;
}
void Reservation::addMororbike(Motorbike * motorbike) {
    this->motorbike = motorbike;
}

int main()
{
    cout << "Motorradvermietung von Lukas Wagenlehner" << endl << endl;

    Customer customer;
    Motorbike *m1 = new Motorbike("Suzuki Bandit");
    Motorbike *m2 = new Motorbike("Honda TransAlp");
    Motorbike *m3 = new Motorbike("BMW F 650 GS");
    Motorbike *m4 = new Motorbike("Kawasaki ZZR1400");

    list<Reservation*> r;
    list<Reservation*>::iterator it;

    Motorbike *motorbikes[] = { m1,m2,m3,m4 };

    bool loop = true;
    int selection;

    while (loop)
    {
        // Menu ausgeben
        printMenu();
        // auswahl erfragen
        if (isMenuSelectionValid(selection = getMenuRequest())) {
            printLine();
            switch (selection)
            {
            case 1:
                cin >> customer;
                if (!customer.hasLicenseA) {
                    cout << "Leider kann die Reservierung nicht vortgesetzt werden, da kein passender Führerschein vorliegt." << endl;
                    break;
                }
                for (int i = 0; i < 4; i++) {
                    cout << "[" << i << "] ";
                    motorbikes[i]->print();
                }
                cout << "Bitte Motorrad auswählen:" << endl;
                int m;
                cin >> m;
                if (motorbikes[m]->isReserved) {
                    cout << "Leider kann die Reservierung nicht vortgesetzt werden, da das Mororrad bereits ausgeliehen ist." << endl;
                    break;
                }
                motorbikes[m]->isReserved = true;
                Reservation *temp = new Reservation(customer);
                temp->addMororbike(motorbikes[m]);
                r.push_front(temp);
                break;
            case 2:
                string name;
                string firstName;
                cout << "Bitte Namen eingeben:" << endl;
                cin >> name;
                cout << "Bitte Vornamen eingeben:" << endl;
                cin >> firstName;
                for (it = r.begin(); it != r.end(); it++) {
                    if ((*it)->customer.name == name && (*it)->customer.firstName == firstName) {
                        r.remove((*it));
                    }
                }
                break;
            case 3:
                
                break;
            case 4:
                
                break;
            default:
                loop = false;
                break;
            }
        }
        else {
            break;
        }
    }
    system("pause");
    return EXIT_SUCCESS;
}
// für Gestalltung für das Menu
void printLine() {
    cout << "-----------------------------------------------------------------------------------" << endl;
}
void printMenu() {
    printLine();
    cout << "[1] Neue Reservierung" << endl;
    cout << "[2] Motorrad herausgeben" << endl;
    cout << "[3] Motorrad wurde abgegeben" << endl;
    cout << "[4] Aktuellen Stand der Reservierungen speichern" << endl;
    cout << "[5] Programm beenden" << endl;
    printLine();
}
int getMenuRequest() {
    // Menu auswahl erfragen
    int request;
    if (!(cin >> request)) {
        return -1;
    }
    return request;
}
bool isMenuSelectionValid(int request) {
    // ist der Ausgewählte Menu Punkt gültig?
    if (request > 0 && request < 6) {
        return true;
    }
    else {
        return false;
    }
}
