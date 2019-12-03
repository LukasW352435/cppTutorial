#include "pch.h"
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <string>
#include <sstream>

using namespace std;

#define MAX_EMPLOYEE 500

void printLine();
void printMenu();
int getMenuRequest();
bool isMenuSelectionValid(int request);
int getEmployeeIndexForDelete();
int getEmployeeIndexForTakeHolidays();

class Date {
    // Datum für Geburtsdatum und aktuelles Datum
public:
	int day;
	int month;
	int year;
	Date();
	Date(int day, int month, int year);
	string getAsString();
    void print();
};
Date::Date()
{
}
Date::Date(int day, int month, int year) :day(day), month(month), year(year) {
}
string Date::getAsString() {
    // Datum als string
    stringstream ss;
    ss << day << "." << month << "." << year;
    return ss.str();
}
void Date::print() {
    // Datum auf der Konsole ausgeben
    cout << this->getAsString() << endl;
}

Date *createNewDate();
Date *getCurrentDate();

class Employee {
    // Mitarbeiter 
private:
	string name;
	string firstName;
	Date *birthday;
	int usedHolidayDays;
	int holidayDays;
public:
	Employee();
	Employee(string name, string firstName, Date *birthday);
	void printNameAndFirstName();
	void print();
	void calculateHolidayDays(Date *currentDate);
    void subtractHolidays(int days);
    string getName();
    string getFirstName();
};
Employee::Employee()
{
}
Employee::Employee(string name, string firstName, Date *birthday) :name(name), firstName(firstName), birthday(birthday) {
	usedHolidayDays = 0;
	holidayDays = 0;
}
void Employee::printNameAndFirstName() {
    // einfache ausgebe eines Mitarbeiters auf der Konsole
	cout << "Name: " << name << ", Vorname: " << firstName << endl;
}
void Employee::print() {
    // detalierte ausgebe eines Mitarbeiters auf der Konsole
	cout << "Name: " << name << ", Vorname: " << firstName << ", Geburtstag: " << birthday->getAsString() << ", Resturlaub: " << (holidayDays - usedHolidayDays) << " Tag(e)" << endl;
}
void Employee::calculateHolidayDays(Date *currentDate) {
    // berechnung der Urlaubstage eines Mitarbeiters anhand des alters und des aktuellen Datums
	int age = currentDate->year - birthday->year;
	if (age >= 50) {
		holidayDays = 32;
	}
	else {
		holidayDays = 30;
	}
}
void Employee::subtractHolidays(int days) {
    // Mitarbeiter möchte Urlaub nehmen
    if ((usedHolidayDays + days) <= holidayDays) {
        // der Mitarbeiter hat noch genug Urlaub
        usedHolidayDays += days;
    }
    else {
        // der Mitarbeiter hat nicht mehr genug Urlaubstage
        cout << "Der Mitarbeiter kann leider nicht mehr so viele Urlaubstage nehmen." << endl;
    }
}
string Employee::getName() {
    return name;
}
string Employee::getFirstName() {
    return firstName;
}

class Management {
    // zum verwalten der Mitarbeiter
private:
    // liste(array) von Maximal 500 Mitarbeitern
	Employee *employeeList[MAX_EMPLOYEE];
    // int für die anzahl aller gültigen einträge in der liste "employeeList"
	int amountEmployee;
public:
	Management();
	void createNewEmployee(Date *currentDate);
	void deleteEmployee(int index);
	void printAllEmployee();
    void searchAndPrintEmployee();
    void takeHolidays(int index);

};
Management::Management() {
    // Neues Management
    // hat immer 0 Mitarbeiter
	amountEmployee = 0;
    for (int i = 0; i < MAX_EMPLOYEE; i++) {
        // array mit NULL belegen
        employeeList[i] = NULL;
    }
}
void Management::createNewEmployee(Date *currentDate) {
    // Neuen Mitarbeiter anlegen
	if (amountEmployee == MAX_EMPLOYEE) {
        // das Array ist voll
		cout << "Speicher voll, es können nur " << MAX_EMPLOYEE << " Mitarbeiter gespeichert werden." << endl;
		return;
	}
	string name;
	string firstName;
	Date *birthday;
	Employee *employee;

	cout << "Neuer Mitarbeiter" << endl;
	printLine();

	cout << "Bitte Name eingeben:" << endl;
	cin >> name;

	cout << "Bitte Vorname eingeben:" << endl;
	cin >> firstName;
	cout << "Bitte Geburtsdatum eingeben:" << endl;
	birthday = createNewDate();

    // neues Objekt vom typ Employee erstellen
	employee = new Employee(name, firstName, birthday);
    // für den Mitarbeiter die Urlaubstage berechnen
	employee->calculateHolidayDays(currentDate);

    // Mitarbeiter in das array einfügen, an den nächsten freien Platz
	for (int i = 0; i < MAX_EMPLOYEE; i++) {
		if (employeeList[i] == NULL) {
			employeeList[i] = employee;
			amountEmployee++;
			break;
		}
	}
}
void Management::deleteEmployee(int index) {
    // Mitarbeiter anhand des Indexes im array löschen
	if (index >= 0 || index < MAX_EMPLOYEE) {
		if (employeeList[index] != NULL) {
            // der index existiert, Mitarbeiter Löschen
            cout << "Der Mitarbeiter wurde gel\x94scht:" << endl;
            employeeList[index]->print();
            // eigentliches Löschen, indem der Pointer mit NULL überschrieben wird
			employeeList[index] = NULL;
			amountEmployee--;
        }
        else {
            cout << "Der Mitarbeiter mit dem Index " << index << " existiert nicht." << endl;
        }
    }
    else {
        cout << "Der Index " << index << " ist ung\x81ltig." << endl;
    }
}
void Management::printAllEmployee() {
    // Jeden Mitarbeiter auflisten, jedoch nur Name und Vorname
    if (amountEmployee == 0) {
        cout << "Keine Mitarbeiter im Speicher." << endl;
    }
    else {
        for (int i = 0; i < MAX_EMPLOYEE; i++) {
            if (employeeList[i] != NULL) {
                cout << "[" << i << "] ";
                employeeList[i]->printNameAndFirstName();
            }
        }
    }
}
void Management::searchAndPrintEmployee() {
    // alle Mitarbeiter mit dem gesuchten Namen und Vorname detaliert ausdrucken
    string name;
    string firstName;
    bool found = false;
    
    if (amountEmployee == 0) {
        cout << "Kein Mitarbeiter im Speicher." << endl;
    }
    else {
        // Name und Vorname erfragen
        cout << "Bitte Namen des Mitarbeiters eingeben:" << endl;
        cin >> name;
        cout << "Bitte Vorname des Mitarbeiters eingeben:" << endl;
        cin >> firstName;

        // das gesamte array nach Mitarbeitern durchsuchen mit dem entsprechenden Namen und Vornamen
        for (int i = 0; i < MAX_EMPLOYEE; i++) {
            if (employeeList[i] != NULL) {
                if (employeeList[i]->getName() == name && employeeList[i]->getFirstName() == firstName) {
                    if (!found) {
                        // wenn der erste Mitarbeiter gefunden worden ist
                        found = true;
                        cout << "Alle Mitarbeiter mit dem Namen: " << name << " und dem Vornamen: " << firstName << " detalliert ausgegeben:" << endl;
                    }
                    // gefundenen Mitarbeiter ausdrucken
                    employeeList[i]->print();
                }
            }
        }
    }
    if (!found) {
        // wenn kein Mitarbeiter gefunden worden ist
        cout << "Kein Mitarbeiter mit dem Namen: " << name << " und dem Vornamen: " << firstName << " gefunden." << endl;
    }
}
void Management::takeHolidays(int index) {
    // Abrechnen von Urlaubstagen von einem Mitarbeiter Anhand seines Indexes
    if (index >= 0 || index < MAX_EMPLOYEE) {
        if (employeeList[index] != NULL) {
            // Mitarbeiter existiert
            cout << "Ausgew\x84hlter Mitarbeiter:" << endl;
            employeeList[index]->print();
            cout << "Bitte Anzahl der abzurechnenden Urlaubstage eingeben:" << endl;
            int days;
            // Anzahl der urlaubstage erfragen
            cin >> days;
            // urlaub abziehen
            employeeList[index]->subtractHolidays(days);
            employeeList[index]->print();
        }
        else {
            cout << "Der Mitarbeiter mit dem Index " << index << " existiert nicht." << endl;
        }
    }
    else {
        cout << "Der Index " << index << " ist ung\x81ltig." << endl;
    }
}

int main()
{
	cout << "Urlaubsverwaltung von Lukas Wagenlehner" << endl << endl;

	Management *management;
	Date *currentDate;
	int selection;
	bool loop = true;
    printLine();
    // aktuelles Datum erfragen
	currentDate = getCurrentDate();
    printLine();
    currentDate->print();
	management = new Management();

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
                // neuen Mitarbeiter anlegen
				management->createNewEmployee(currentDate);
				break;
			case 2:
                // Mitarbeiter Löschen
                management->deleteEmployee(getEmployeeIndexForDelete());
				break;
			case 3:
                // Mitarbeiter Ausdrucken
				management->printAllEmployee();
				break;
			case 4:
                // Mitarbeiter suchen und ausgeben
                management->searchAndPrintEmployee();
				break;
			case 5:
                // Mitarbeiter nimmt Urlaub
                management->takeHolidays(getEmployeeIndexForTakeHolidays());
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

void printLine() {
    // für Gestalltung für das Menu
	cout << "-----------------------------------------------------------------------------------" << endl;
}
void printMenu() {
    // Menu ausgeben
	printLine();
	cout << "[1] Neuen Mitarbeiter anlegen" << endl;
	cout << "[2] Mitarbeiter l\x94schen" << endl;
	cout << "[3] Alle Mitarbeiter auflisten" << endl;
	cout << "[4] Mitarbeiter suchen und detallierte Ausgabe" << endl;
	cout << "[5] Mitarbeiter Urlaubstage anrechnen" << endl;
	cout << "[6] Programm beenden" << endl;
	printLine();
}
int getMenuRequest() {
    // Menu auswahl erfragen
	int request;
	if(!(cin >> request)){
		return -1;
	}
	return request;
}
int getEmployeeIndexForDelete() {
    // index zum löschen eines Mitarbeiters erfragen
    cout << "Bitte Index des zu l\x94schenden Mitarbeiters eingeben:" << endl;
    int index;
    if (!(cin >> index)) {
        return -1;
    }
    return index;
}
int getEmployeeIndexForTakeHolidays() {
    // index zum urlaub nehmen eines Mitarbeiters erfragen
    cout << "Bitte Index des Mitarbeiters eingeben:" << endl;
    int index;
    if (!(cin >> index)) {
        return -1;
    }
    return index;
}
bool isMenuSelectionValid(int request) {
    // ist der Ausgewählte Menu Punkt gültig?
	if (request > 0 && request < 7) {
		return true;
	}
	else {
		return false;
	}
}
Date *createNewDate() {
    // Neues Datum erfragen
	int day;
	int month;
	int year;

	cout << "Tag:" << endl;
	cin >> day;
	cout << "Monat:" << endl;
	cin >> month;
	cout << "Jahr:" << endl;
	cin >> year;
	return new Date(day, month, year);
}
Date *getCurrentDate() {
    // Aktuelles Datum Erfragen
	cout << "Bitte aktuelles Datum eingeben:" << endl;
	return createNewDate();
}