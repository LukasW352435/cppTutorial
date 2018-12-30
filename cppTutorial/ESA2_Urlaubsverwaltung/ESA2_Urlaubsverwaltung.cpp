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


class Date {
public:
	int day;
	int month;
	int year;
	Date();
	Date(int day, int month, int year);
	string getAsString();
};
Date::Date()
{
}
Date::Date(int day, int month, int year) :day(day), month(month), year(year) {
}
string Date::getAsString() {
	return day + "." + month + '.' + year;
}

Date *createNewDate();
Date *getCurrentDate();

class Employee {
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
};
Employee::Employee()
{
}
Employee::Employee(string name, string firstName, Date *birthday) :name(name), firstName(firstName), birthday(birthday) {
	usedHolidayDays = 0;
	holidayDays = 0;
}
void Employee::printNameAndFirstName() {
	cout << "Name: " << name << ", Vorname: " << firstName << endl;
}
void Employee::print() {
	cout << "Name: " << name << ", Vorname: " << firstName << ", Geburtstag: " << birthday->getAsString() << ", Resturlaub: " << (holidayDays - usedHolidayDays) << " Tag(e)" << endl;
}
void Employee::calculateHolidayDays(Date *currentDate) {
	int age = currentDate->year - birthday->year;
	if (age >= 50) {
		holidayDays = 32;
	}
	else {
		holidayDays = 30;
	}
}

class Management {
private:
	Employee *employeeList[MAX_EMPLOYEE];
	int amountEmployee;
public:
	Management();
	void createNewEmployee(Date *currentDate);
	void deleteEmployee(int index);
	void printEmployee(int index);
	void printAllEmplyee();

};
Management::Management() {
	amountEmployee = 0;
}
void Management::createNewEmployee(Date *currentDate) {
	if (amountEmployee == MAX_EMPLOYEE) {
		cout << "Speicher voll, es können nur " << MAX_EMPLOYEE << "Mitarbeiter gespeichert werden." << endl;
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

	employee = new Employee(name, firstName, birthday);
	employee->calculateHolidayDays(currentDate);

	for (int i = 0; i < MAX_EMPLOYEE; i++) {
		if (employeeList[i] == NULL) {
			employeeList[i] = employee;
			amountEmployee++;
			break;
		}
	}
}
void Management::deleteEmployee(int index) {
	if (index >= 0 || index < MAX_EMPLOYEE) {
		if (employeeList[index] != NULL) {
			employeeList[index] = NULL;
			amountEmployee--;
		}
	}
}
void Management::printEmployee(int index) {
	if (index >= 0 || index < MAX_EMPLOYEE) {
		if (employeeList[index] != NULL) {
			employeeList[index]->print();
		}
	}
}
void Management::printAllEmplyee() {
	for (int i = 0; i < MAX_EMPLOYEE; i++) {
		if (employeeList[i] != NULL) {
			cout << i << ".";
			employeeList[i]->print();
		}
	}
}

int main()
{
	cout << "Urlaubsverwaltung von Lukas Wagenlehner" << endl << endl;

	Management *management;
	Date *currentDate;
	int selection;
	bool loop = false;

	currentDate = getCurrentDate();
	management = new Management();

	while (loop)
	{
		printMenu();
		if (isMenuSelectionValid(selection = getMenuRequest())) {
			printLine();
			switch (selection)
			{
			case 1:
				management->createNewEmployee(currentDate);
				break;
			case 2:
				break;
			case 3:
				management->printAllEmplyee();
				break;
			case 4:
				break;
			case 5:
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
	cout << "[1] Neuen Mitarbeiter anlegen" << endl;
	cout << "[2] Mitarbeiter l\x94schen" << endl;
	cout << "[3] Alle Mitarbeiter auflisten" << endl;
	cout << "[4] Mitarbeiter suchen und detallierte Ausgabe" << endl;
	cout << "[5] Mitarbeiter Urlaubstage anrechnen" << endl;
	cout << "[6] Programm beenden" << endl;
	printLine();
}
int getMenuRequest() {
	int request;
	if(!(cin >> request)){
		return -1;
	}
	return request;
}
bool isMenuSelectionValid(int request) {
	if (request > 0 && request < 7) {
		return true;
	}
	else {
		return false;
	}
}
Date *createNewDate() {
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
	cout << "Bitte aktuelles Datum eingeben:" << endl;
	return createNewDate();
}