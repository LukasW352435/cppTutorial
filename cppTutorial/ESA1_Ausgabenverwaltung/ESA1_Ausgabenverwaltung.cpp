#include "pch.h"
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <string>
#include <sstream>
using namespace std;

// limit für die Warnung, ob man in einem Monat zu viel Geld ausgegeben hat
#define LIMIT_OF_MONTHLY_EXPENSES 500

// globale variable für das erstellen von immer neuen Rechnungsnummer => In einem Programm durchlauf können maximal INT_MAX Rechnungen erstellt werden
int invoiceNumber = 0;

// Enums für Monat und Kategorie der Rechnung, zweck: schönerer Quellcode
enum Month { January = 0, February = 1, March = 2, April = 3, May = 4, June = 5, July = 6, August = 7, September = 8, October = 9, November = 10, December = 11 };
enum Category { Fuel = 0, Eat = 1, Clothing = 2, Vacation = 3, Hausehold = 4, FreeTime = 5, Pets = 6, Other = 7 };

void printMenu();
int getMenuRequest();
bool isMenuSelectionValid(int request);
int getNumberToRemove();
void printWhichInvoiceToRemove();
string getMonthAsString(Month month);
string getCategoryAsString(Category category);
void printLine();
void printMenu();
string convertDoubleToString(double value);

// Klasse Rechnung
class Invoice {
    friend class ListOfInvoices;
private:
    // Attribute
    int number;
    Month month;
    double amount;
    Category category;
    // Pointer auf die Nächste Rechnung
    Invoice *nextInvoice;
public:
    Invoice(int number, Month month, double amount, Category category);
    void print();
};
// Konstruktor
Invoice::Invoice(int number, Month month, double amount, Category category) :number(number), month(month), amount(amount), category(category) {
    // Jede neue Rechnung hat zu Anfang keine Nachfolgende Rechnung
    nextInvoice = NULL;
}
// Ausgabe einer Rechnung auf der Konsole
void Invoice::print() {
    // Enum month wird in einen schönen string umgewandelt
    string monthAsString = getMonthAsString(month);
    // Enum category wird in einen schönen string umgewandelt
    string categoryAsString = getCategoryAsString(category);
    // Ausgabe der Rechnung auf der Konsole
    cout << "Rechnungsnummer: " << number << ", Betrag: " << amount << " Euro, Monat: " << monthAsString << ", Kategorie: " << categoryAsString << endl;
}

// kann erst hier sein, da Rechnung erst jetzt bekannt ist (normalerweise sind alle Klassen in einer eigenen Datei, dann wäre das hier auch nicht nötig)
// Diese Funktion ist nicht in ListOfInvoices, da mann ja eventuell auch Rechnungen für andere zwecke erstellen möchte
Invoice *createNewInvoice();

// Liste aus Rechnungen
class ListOfInvoices {
private:
    // Start Pointer der Liste
    Invoice *anchor;
public:
    ListOfInvoices();
    void insert(Invoice *invoice);
    void removeByNumber(int number);
    void print();
    void printSortedMonthlyOverview();
    void printSumOfCategories();
};
// Konstruktor
ListOfInvoices::ListOfInvoices() {
    // zu beginn ist die Liste leer
    anchor = NULL;
}
// neue Rechnung vorne in der Liste einfügen
void ListOfInvoices::insert(Invoice *invoice) {
    // Die neue Rechnung auf die aktuelle Startrechnung zeigen lassen
    invoice->nextInvoice = anchor;
    // Die neue Rechnung zur Startrechnung machen
    anchor = invoice;
}
// eine Rechnung anhand ihrer eindeutigen Rechnungsnummer löschen
void ListOfInvoices::removeByNumber(int number) {
    // ein helfer um sich die letzte besichtigte Rechnung zu merken, da auf dieser Rechnung später der Pointer auf die nächste Rechnung geändert werden muss
    Invoice *invoiceSave = anchor;
    // zum durch Iterieren der Liste
    Invoice *invoice;
    // wird verwendet, falls die Rechnung nicht existiert
    bool wasDeleted = false;
    // Durchlauf aller Rechnungen
    for (invoice = anchor; invoice != NULL; invoice = invoice->nextInvoice) {
        // Schauen ob es sich um die gesuchte Rechnung handelt
        if (invoice->number == number) {
            if (invoice == anchor) {
                // spezielles löschen, falls die erste Rechnung in der Liste gelöscht werden soll
                anchor = invoice->nextInvoice;
            }
            else {
                // löschen einer Rechnung, die nicht die erste Rechnung ist
                invoiceSave->nextInvoice = invoice->nextInvoice;
            }
            // Kurze bestätigung, das die Rechnung gelöscht worden ist
            cout << "Gel\x94schte Rechnung:" << endl;
            invoice->print();
            // Merken das eine Rechnung gelöscht worden ist
            wasDeleted = true;
            break;
        }
        // Setzen der zu letzt durchlaufenen Rechnung
        invoiceSave = invoice;
    }
    if (!wasDeleted) {
        // Falls keine Rechnung gelöscht worden ist
        cout << "Die Rechnung mit der Nummer " << number << " ist nicht vorhanden." << endl;
    }
}
// Ausgabe der Liste
void ListOfInvoices::print() {
    cout << "Liste aller Rechnungen" << endl;
    printLine();
    Invoice *invoice;
    if (anchor == NULL) {
        cout << "Die Liste ist leer, bitte Rechnungen eingeben." << endl;
    }
    // Durchgehen der Liste und jede Rechnung auf der Konsole ausgeben
    for (invoice = anchor; invoice != NULL; invoice = invoice->nextInvoice) {
        invoice->print();
    }
}
// Ausgabe der Liste Sortiert nach Monat, jede Kategorie pro Monat aufsummiert und eventuell warnung, falls in einem Monat zu viel ausgegeben worden ist
void ListOfInvoices::printSortedMonthlyOverview() {
    int month;
    int category;
    double categorySum;
    double monthTotal;
    // string für einen Monat, um es möglich zu machen die warnung, falls zu viel Geld in einem Monat ausgegeben worden ist direckt unter den Monat zu schreiben
    string monthCalculated;
    Invoice *invoice;
    cout << "Alle Ausgaben, sortiert nach Monat:" << endl;

    // Ich habe mich für die volgende Lösung entschieden, da sie meiner Meinung für ein "kleines" Programm ausreichend ist
    // Bei extrem vielen Listenelementen würde ich eine Lösung vorziehen, in der die Liste wenn möglich nur einmal durchlaufen werden müsste.

    // für jeden Monat einmal die Liste durchgehen
    for (month = (int)January; month < (int)December + 1; month++) {
        monthTotal = 0;
        monthCalculated = "";
        // für jede Kategorie einmal die Liste durchgehen
        for (category = (int)Fuel; category < (int)Other + 1; category++) {
            categorySum = 0;
            // die Liste einmal durchgehen
            for (invoice = anchor; invoice != NULL; invoice = invoice->nextInvoice) {
                if (invoice->category == category && invoice->month == month) {
                    // wenn der Monat und die Kategorie der Rechnung stimmen, auf die momentane Summe der entsprechenden Kategorie aufaddieren
                    categorySum += invoice->amount;
                }
            }
            // für die Gesamt ausgaben eines Monats
            monthTotal += categorySum;
            // auf den momentanen Monats string die aktuelle Kategorie "aufaddieren"
            monthCalculated += getCategoryAsString((Category)category) + ":  \t" + convertDoubleToString(categorySum) + " Euro\n";
        }
        printLine();
        cout << getMonthAsString((Month)month) << endl;
        printLine();
        // falls das Limit überschritten worden ist
        if (monthTotal >= LIMIT_OF_MONTHLY_EXPENSES) {
            cout << "Mehr ausgegeben als geplant!!!" << endl;
            printLine();
        }
        cout << monthCalculated;
        cout << "Gesamt: \t" << monthTotal << " Euro" << endl;
    }
}
// Summe aller Kategorien ausgeben
void ListOfInvoices::printSumOfCategories() {
    int category;
    double categorySum;
    double total = 0;
    Invoice *invoice;
    cout << "Summe aller Kategorien" << endl;
    printLine();
    // alle Kategorien durchlaufen
    for (category = (int)Fuel; category < (int)Other + 1; category++) {
        categorySum = 0;
        // Liste durchlaufen
        for (invoice = anchor; invoice != NULL; invoice = invoice->nextInvoice) {
            if (invoice->category == category) {
                // wenn die Kategorie stimmt, auf die momentane Kategorie addieren
                categorySum += invoice->amount;
            }
        }
        total += categorySum;
        cout << getCategoryAsString((Category)category) << ": " << categorySum << " Euro" << endl;
    }
    cout << "Gesamt: " << total << " Euro" << endl;
}

int main()
{
    // damit double mit 2 Nachkommastellen ausgegeben werden
    cout << fixed << setprecision(2);

    cout << "Ausgabenverwaltung von Lukas Wagenlehner" << endl << endl;

    // für das Menu
    int selection;
    Invoice *invoice;
    // neue Liste erstellen
    ListOfInvoices *listOfInvoices = new ListOfInvoices();
    bool loop = true;

    while (loop) {
        printMenu();
        // Nutzer nach einer aktivität fragen
        if (isMenuSelectionValid(selection = getMenuRequest())) {
            printLine();
            switch (selection)
            {
            case 1:
                // Nutzer möchte eine neue Rechnung eingeben
                invoice = createNewInvoice();
                // Neue Rechnung in die Liste einfügen
                listOfInvoices->insert(invoice);
                break;
            case 2:
                // Nutzer möchte sich eine Übersicht ausgeben lassen
                listOfInvoices->printSortedMonthlyOverview();
                break;
            case 3:
                // Nutzer möchte wissen was er für die jeweiligen Kategorien in diesem Jahr ausgegeben hat
                listOfInvoices->printSumOfCategories();
                break;
            case 4:
                // Nutzer möchte alle Rechnungen anschauen
                // Nützlich wenn er eine Löschen möchte
                listOfInvoices->print();
                break;
            case 5:
                // Nutzer möchte eine Rechnung löschen
                int numberToRemove;
                // Nutzer fragen welche Rechnung er löschen möchte
                printWhichInvoiceToRemove();
                // eingabe des Nutzers hollen
                numberToRemove = getNumberToRemove();
                printLine();
                // versuchen die Rechnung zu Löschen
                listOfInvoices->removeByNumber(numberToRemove);
                break;
            default:
                // case 6 oder andere eingabe
                // while verlassen
                loop = false;
                break;
            }
        }
        else {
            // der Nutzer hat eine falsche eingabe gemacht, Programm beenden
            break;
        }
    }
    system("pause");
    return EXIT_SUCCESS;
}

// Menu anzeigen
void printMenu() {
    printLine();
    cout << "[1] Neue Rechnung eingeben" << endl;
    cout << "[2] Jahres\x81\berblick ausgeben" << endl;
    cout << "[3] Summe aller Kategorien ausgeben" << endl;
    cout << "[4] Alle Rechnungen ausgeben" << endl;
    cout << "[5] Rechnung l\x94schen" << endl;
    cout << "[6] Programm beenden" << endl;
    printLine();
}
// Nutzer nach aktivität fragen
int getMenuRequest() {
    int request;
    if (!(cin >> request)) {
        return -1;
    }
    return request;
}
// Schauen ob es den Menupunkt gibt
bool isMenuSelectionValid(int request) {
    if (request > 0 && request < 7) {
        return true;
    }
    else {
        return false;
    }
}
// Rechnungsnummer zum löschen abfragen
int getNumberToRemove() {
    int numberToRemove;
    if (!(cin >> numberToRemove)) {
        return -1;
    }
    return numberToRemove;
}
// Nutzer fragen welche Rechnung gelöscht werden soll
void printWhichInvoiceToRemove() {
    cout << "Rechnung l\x94schen" << endl;
    printLine();
    cout << "Bitte Rechnungsnummer eingeben:" << endl;
}
// schöne Ausgabe der Enums Month und Category
string getMonthAsString(Month month) {
    switch (month)
    {
    case January:
        return "Januar";
        break;
    case February:
        return "Februar";
        break;
    case March:
        return  "M\x84rz";
        break;
    case April:
        return "April";
        break;
    case May:
        return "Mai";
        break;
    case June:
        return "Juni";
        break;
    case July:
        return "Juli";
        break;
    case August:
        return "August";
        break;
    case September:
        return "September";
        break;
    case October:
        return "Oktober";
        break;
    case November:
        return "November";
        break;
    case December:
        return "Dezember";
        break;
    default:
        return "";
        break;
    }
}
string getCategoryAsString(Category category) {
    switch (category)
    {
    case Fuel:
        return "Tanken";
        break;
    case Eat:
        return "Essen";
        break;
    case Clothing:
        return "Kleidung";
        break;
    case Vacation:
        return "Urlaub";
        break;
    case Hausehold:
        return "Haushalt";
        break;
    case FreeTime:
        return "Freizeit";
        break;
    case Pets:
        return "Haustiere";
        break;
    case Other:
        return "Sonstiges";
        break;
    default:
        return "";
        break;
    }
}
// für Gestalltung für das Menu
void printLine() {
    cout << "-----------------------------------------------------------------------------------" << endl;
}
// neue Rechnung erstellen
Invoice *createNewInvoice() {
    double amount;
    Month month;
    Category category;

    cout << "Neue Rechnung" << endl;
    printLine();

    // Betrag abfragen
    cout << "Bitte Betrag eingeben:" << endl;
    cin >> amount;

    // Monat abfragen ACHTUNG keine überprüfung Nutzer eingabe 35, entspricht halt keinem Monat
    cout << "Bitte Monat eingeben:" << endl;
    int monthHelper;
    // auswahl anzeigen
    for (monthHelper = (int)January; monthHelper < (int)December + 1; monthHelper++) {
        cout << "[" << monthHelper << "] " << getMonthAsString((Month)monthHelper) << endl;
    }
    cin >> monthHelper;
    month = (Month)monthHelper;

    // Kategorie abfragen, ich gehe auch hier von einem freundlichen benutzer aus, der keine falscheingabe macht
    cout << "Bitte Kategorie eingeben:" << endl;
    int categoryHelper;
    // auswahl anzeigen
    for (categoryHelper = (int)Fuel; categoryHelper < (int)Other + 1; categoryHelper++) {
        cout << "[" << categoryHelper << "]" << getCategoryAsString((Category)categoryHelper) << endl;
    }
    cin >> categoryHelper;
    category = (Category)categoryHelper;

    // Neue Rechnung erstellen
    Invoice *invoice = new Invoice(invoiceNumber, month, amount, category);
    // Globale Rechnungsnummer hochzählen
    invoiceNumber++;

    //Nutzer mitteilen das eine neue Rechnung erstellt worden ist
    printLine();
    cout << "Neue Rechnung Erstellt:" << endl;
    invoice->print();
    return invoice;
}
// double to String mit 2 nachkomma stellen
string convertDoubleToString(double variable) {
    stringstream stream;
    stream << std::fixed << setprecision(2) << variable;
    return stream.str();
}
