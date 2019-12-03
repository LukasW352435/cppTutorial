#include "pch.h"
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <string>
#include <sstream>
#include <list>
#include <fstream>
using namespace std;

// Funktionsr�mpfe
void printMenu();
void printLine();
int getMenuRequest();
bool isMenuSelectionValid(int request);

// Motorrad
class Motorbike {
private:
    string name;
    bool isReserved;
    bool isBorrowed;
public:
    Motorbike(string name);
    friend ostream& operator<< (ostream& os, const Motorbike& motorbike);
    bool reserve();
    bool giveOut();
    bool takeBack();
};
Motorbike::Motorbike(string name) :name(name) {
    isReserved = false;
    isBorrowed = false;
}
// �berladen von << um das Motorrad zB. auf der Konsole ausgeben zu k�nnen
ostream& operator<<(ostream& os, const Motorbike& motorbike) {
    os << motorbike.name;
    return os;
}
// Motorrad Reservieren
bool Motorbike::reserve() {
    if (isReserved) {
        return false;
    }
    else
    {
        isReserved = true;
        return true;
    }
}
// Motorrad Herrausgeben
bool Motorbike::giveOut() {
    if (isBorrowed || !isReserved) {
        return false;
    }
    else
    {
        isBorrowed = true;
        isReserved = false;
        return true;
    }
}
// Motorrad Zur�cknehmen
bool Motorbike::takeBack() {
    if (isBorrowed) {
        isBorrowed = false;
        return true;
    }
    else
    {
        return false;
    }
}

//Kunde
class Customer {
private:
    string name;
    string firstName;
    string street;
    string houseNumber;
    int zipCode;
    string city;
    int birthyear;
    string telephoneNumber;
    bool hasLicenseA;
public:
    friend istream& operator>> (istream& is, Customer& customer);
    friend ostream& operator<< (ostream& os, const Customer& customer);
    string getName();
    string getFistName();
    bool checkLicense();
};
// �berladen von >> und << zum einlesen von Kunden bzw. ausgeben von Kunden
istream& operator>>(istream& is, Customer& customer) {
    cout << "Name:" << endl;
    is >> customer.name;
    cout << "Vorname:" << endl;
    is >> customer.firstName;
    cout << "Adresse" << endl;
    cout << "Strasse:" << endl;
    is >> customer.street;
    cout << "Hausnummer" << endl;
    is >> customer.houseNumber;
    cout << "Postleitzahl:" << endl;
    is >> customer.zipCode;
    cout << "Stadt/Ort:" << endl;
    is >> customer.city;
    cout << "Geburtsjahr:" << endl;
    is >> customer.birthyear;
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
    os << "Name: " << customer.name << ", Vorname:" << customer.firstName << ", Geburtsjahr: " << customer.birthyear << endl << "Adresse:" << endl << "Strasse: " << customer.street << ", Hausnummer: " << customer.houseNumber << ", PLZ: " << customer.zipCode << ", Stadt: " << customer.city << endl << "Hat F\x81hrerschein der Klasse A: " << license << endl;
    return os;
}
// Name und Vorname zur�ckgeben
string Customer::getName() {
    return name;
}
string Customer::getFistName() {
    return firstName;
}
// Pr�fen ob der Kunde einen F�hrerschein besitzt
bool Customer::checkLicense() {
    if (hasLicenseA) {
        return true;
    }
    else
    {
        return false;
    }
}

// Reservierung
class Reservation {
private:
    Motorbike *motorbike;
    Customer *customer;
public:
    Reservation();
    Reservation(Customer *customer, Motorbike *motorbike);
    ~Reservation();
    friend ostream& operator<< (ostream& os, const Reservation& reservation);
    Customer* getCustomer();
    Motorbike* getMotorbike();
};
// Konstruktoren
Reservation::Reservation() {

}
Reservation::Reservation(Customer *customer, Motorbike *motorbike) :customer(customer), motorbike(motorbike) {
}
// Dekonstruktor
Reservation::~Reservation() {

}
// �berladen von << wird f�rs schreiben in die Datei verwendet
ostream& operator<<(ostream& os, const Reservation& reservation) {
    os << "Kunde:" << endl << *(reservation.customer) << "Motorrad:" << endl << *(reservation.motorbike) << endl;
    return os;
}
// Kunde bzw. Motorrad einer Reservierung zur�ckgeben
Customer* Reservation::getCustomer() {
    return customer;
}
Motorbike* Reservation::getMotorbike() {
    return motorbike;
}

// Funktionsr�mpfe, stehen hier da zb. Customer oben noch nicht bekannt ist, 
// normalerweise w�rde jede Klasse seine eigene Datei bekommen und dann w�rden alle Funktionsr�mpfe beieinander stehen
Customer* getCustomerWithRequest(list<Customer*> customers);
int getMotorbikeWithRequest(Motorbike *motorbikes[]);
Reservation* getReservationWithCustomer(list<Reservation*> reservations, Customer *customer);

int main()
{
    cout << "Motorradvermietung von Lukas Wagenlehner" << endl << endl;

    // Motorr�der erstellen
    Motorbike *m1 = new Motorbike("Suzuki Bandit");
    Motorbike *m2 = new Motorbike("Honda TransAlp");
    Motorbike *m3 = new Motorbike("BMW F 650 GS");
    Motorbike *m4 = new Motorbike("Kawasaki ZZR1400");

    // Listen f�r Kunden und Reservierungen anlegen
    // und Pointer zum zwischenspeichern von Reservierungen bzw. Kunden
    list<Reservation*> reservations;
    Reservation *reservation;

    list<Customer*> customers;
    Customer *customer;

    // Array f�r die Motorr�der
    Motorbike *motorbikes[] = { m1,m2,m3,m4 };
    int index_motorbike;

    // F�rs schreiben der Datei reservierungen.txt
    fstream fstream;

    // F�r die Main loop
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
                // neuen Kunden erstellen
                customer = new Customer();
                cin >> *customer;
                // Kunden zur liste hinzuf�gen
                customers.push_back(customer);
                break;
            case 2:
                // alle Kunden ausgeben
                if (customers.size() == 0) {
                    cout << "Kein Kunde im Speicher." << endl;
                }
                // durch die Liste customers iterieren und alle Elemente ausgeben
                for (list<Customer*>::iterator it = customers.begin(); it != customers.end(); it++) {
                    cout << **it << endl;
                }
                break;
            case 3:
                // neue Reservierung erstellen
                // Kunden mit einer Abfrage von Name und Vorname aus der Liste custemers hollen
                customer = getCustomerWithRequest(customers);
                // Pr�fen ob der Kunde g�ltig ist
                if (customer == NULL) {
                    break;
                }
                // �berpr�fen ob der Kunde einen F�hrerschein besitzt
                if (customer->checkLicense()) {
                    // schauen ob f�r den Kunden bereits eine Reservierung gespeichert ist
                    reservation = getReservationWithCustomer(reservations, customer);
                    if (reservation != NULL) {
                        cout << "Leider hat der Kunde bereits eine Reservierung." << endl;
                        break;
                    }
                    // Motorrad auswahl ausgeben und zur�ckgegebenen index pr�fen
                    index_motorbike = getMotorbikeWithRequest(motorbikes);
                    if (index_motorbike == -1) {
                        cout << "Falsche eingebe." << endl;
                        break;
                    }
                    // versuchen das Motorrad zu reservieren
                    if (motorbikes[index_motorbike]->reserve()) {
                        // das Motorrad kann reserviert werden
                        // neue Reservierung zur liste reservations hinzuf�gen
                        reservations.push_back(new Reservation(customer, motorbikes[index_motorbike]));
                        cout << "Reservierung erfolgreich erstellt." << endl;
                    }
                    else
                    {
                        // das Motorrad kann nicht reserviert werden
                        cout << "Das Motorrad kann leider nicht ausgeliehen werden, da es bereits jemand reserviert hat." << endl;
                    }
                }
                else
                {
                    cout << "Leider hat der Kunde keinen F\x81hrerschein." << endl;
                }
                break;
            case 4:
                // Motorrad herrausgeben
                // Kunden mit Name und Vorname suchen und ergebnis �berpr�fen
                customer = getCustomerWithRequest(customers);
                if (customer == NULL) {
                    break;
                }
                // Schauen ob der Kunde das Motorrad vorher reserviert hat
                reservation = getReservationWithCustomer(reservations, customer);
                if (reservation == NULL) {
                    // Kunde hat das Motorrad nicht reserviert
                    cout << "Leider hat der Kunde kein Motorrad reserviert." << endl;
                }
                else {
                    // Das Motorrad dem Kunden �bergeben
                    if (reservation->getMotorbike()->giveOut()) {
                        cout << "Das Motorrad " << *(reservation->getMotorbike()) << " wird dem volgenden Kunden ausgeliehen:" << endl << *customer;
                        // Reservierung aus der Liste L�schen, danach das Objekt reservation l�schen
                        reservations.remove(reservation);
                        reservation->~Reservation();
                    }
                    else {
                        // Falls das Motorrad Reserviert worden ist, jedoch noch in besitz des vorherigem Kunden ist
                        cout << "Das Motorrad ist noch ausgeliehen." << endl;
                    }
                }
                break;
            case 5:
                // Motorrad zur�ckgeben
                // Abfragen welches Motorrad zur�ckgegeben werden soll
                index_motorbike = getMotorbikeWithRequest(motorbikes);
                if (index_motorbike == -1) {
                    cout << "Falsche eingebe." << endl;
                    break;
                }
                // Motorrad zur�ckgeben
                if (motorbikes[index_motorbike]->takeBack()) {
                    cout << "Motorrad erfolgreich zur\x81\ck genommen." << endl;
                }
                else {
                    cout << "Das Motorrad wurde bereits zur\x81\ck gegeben." << endl;
                }
                break;
            case 6:
                // Reservierung Speichern
                try {
                    // Datei �ffnen und immer ans ende der Datei schreiben
                    fstream.open("reservierungen.txt", ios::app);
                    // Alle Reservierungen in die Datei schreiben
                    for (list<Reservation*>::iterator it = reservations.begin(); it != reservations.end(); it++) {
                        fstream << **it << endl;
                    }
                    // Datei schlie�en
                    fstream.close();
                    cout << "Erfolgreich gespeichert." << endl;
                }
                catch (...) {
                    cout << "Fehler beim schreiben der Reservierungen." << endl;
                }
                break;
            default:
                // Programm beenden
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

// f�r Gestalltung f�r das Menu
void printLine() {
    cout << "-----------------------------------------------------------------------------------" << endl;
}
// Menu auf der Konsole ausgeben
void printMenu() {
    printLine();
    cout << "[1] Neuen Kunden erstellen" << endl;
    cout << "[2] Alle Kunden ausgeben" << endl;
    cout << "[3] Neue Reservierung" << endl;
    cout << "[4] Motorrad herrausgeben" << endl;
    cout << "[5] Motorrad zur\x81\cknehmen" << endl;
    cout << "[6] Reservierungen speichern" << endl;
    cout << "[7] Programm beenden" << endl;
    printLine();
}
// Nutzer fragen was er machen m�chte
int getMenuRequest() {
    // Menu auswahl erfragen
    int request;
    if (!(cin >> request)) {
        return -1;
    }
    return request;
}
// Nutzer eingabe �berpr�fen
bool isMenuSelectionValid(int request) {
    // ist der Ausgew�hlte Menu Punkt g�ltig?
    if (request > 0 && request < 8) {
        return true;
    }
    else {
        return false;
    }
}

// Alle Motorr�der ausgeben und eines vom Nutzer ausw�hlen lassen
int getMotorbikeWithRequest(Motorbike *motorbikes[]) {
    cout << "Bitte ein Motorrad ausw\x84hlen:" << endl;
    for (int i = 0; i < 4; i++) {
        cout << "[" << i << "] " << *motorbikes[i] << endl;
    }
    int request;
    if (!(cin >> request)) {
        return -1;
    }
    if (request < 0 || request > 3) {
        return -1;
    }
    return request;
}
// Einen Kunden anhand vom Namen und Vorname finden und zur�ckgeben
Customer* getCustomerWithRequest(list<Customer*> customers) {
    Customer *customer = new Customer();
    string name, firstName;
    bool found = false;
    if (customers.size() == 0) {
        cout << "Kein Kunde im Speicher." << endl;
        return NULL;
    }
    else {
        cout << "Bitte Namen des Kunden eingeben:" << endl;
        cin >> name;
        cout << "Bitte Vorname des Kunden eingeben:" << endl;
        cin >> firstName;

        for (list<Customer*>::iterator it = customers.begin(); it != customers.end(); it++) {
            customer = *it;
            if (customer->getName() == name && customer->getFistName() == firstName) {
                found = true;
                return customer;
            }
        }
    }
    if (!found) {
        cout << "Kein Kunde mit dem Namen: " << name << " und dem Vornamen: " << firstName << " gefunden." << endl;
        return NULL;
    }
}
// Eine Reservierung anhand von einem Kunden finden und zur�ckgeben
Reservation* getReservationWithCustomer(list<Reservation*> reservations, Customer *customer) {
    Reservation *reservation = new Reservation();
    for (list<Reservation*>::iterator it = reservations.begin(); it != reservations.end(); it++) {
        reservation = *it;
        if (reservation->getCustomer() == customer) {
            return reservation;
        }
    }
    return NULL;
}
