#include "pch.h"
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <string>
#include <sstream>
using namespace std;

// limit f�r die Warnung, ob man in einem Monat zu viel Geld ausgegeben hat
#define LIMIT_OF_MONTHLY_EXPENSES 500

// globale variable f�r das erstellen von immer neuen Rechnungsnummer => In einem Programm durchlauf k�nnen maximal INT_MAX Rechnungen erstellt werden
int invoiceNumber = 0;

// Enums f�r Monat und Kategorie der Rechnung, zweck: sch�nerer Quellcode
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
    // Pointer auf die N�chste Rechnung
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
    // Enum month wird in einen sch�nen string umgewandelt
    string monthAsString = getMonthAsString(month);
    // Enum category wird in einen sch�nen string umgewandelt
    string categoryAsString = getCategoryAsString(category);
    // Ausgabe der Rechnung auf der Konsole
    cout << "Rechnungsnummer: " << number << ", Betrag: " << amount << " Euro, Monat: " << monthAsString << ", Kategorie: " << categoryAsString << endl;
}

// kann erst hier sein, da Rechnung erst jetzt bekannt ist (normalerweise sind alle Klassen in einer eigenen Datei, dann w�re das hier auch nicht n�tig)
// Diese Funktion ist nicht in ListOfInvoices, da mann ja eventuell auch Rechnungen f�r andere zwecke erstellen m�chte
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
// neue Rechnung vorne in der Liste einf�gen
void ListOfInvoices::insert(Invoice *invoice) {
    // Die neue Rechnung auf die aktuelle Startrechnung zeigen lassen
    invoice->nextInvoice = anchor;
    // Die neue Rechnung zur Startrechnung machen
    anchor = invoice;
}
// eine Rechnung anhand ihrer eindeutigen Rechnungsnummer l�schen
void ListOfInvoices::removeByNumber(int number) {
    // ein helfer um sich die letzte besichtigte Rechnung zu merken, da auf dieser Rechnung sp�ter der Pointer auf die n�chste Rechnung ge�ndert werden muss
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
                // spezielles l�schen, falls die erste Rechnung in der Liste gel�scht werden soll
                anchor = invoice->nextInvoice;
            }
            else {
                // l�schen einer Rechnung, die nicht die erste Rechnung ist
                invoiceSave->nextInvoice = invoice->nextInvoice;
            }
            // Kurze best�tigung, das die Rechnung gel�scht worden ist
            cout << "Gel\x94schte Rechnung:" << endl;
            invoice->print();
            // Merken das eine Rechnung gel�scht worden ist
            wasDeleted = true;
            break;
        }
        // Setzen der zu letzt durchlaufenen Rechnung
        invoiceSave = invoice;
    }
    if (!wasDeleted) {
        // Falls keine Rechnung gel�scht worden ist
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
    // string f�r einen Monat, um es m�glich zu machen die warnung, falls zu viel Geld in einem Monat ausgegeben worden ist direckt unter den Monat zu schreiben
    string monthCalculated;
    Invoice *invoice;
    cout << "Alle Ausgaben, sortiert nach Monat:" << endl;

    // Ich habe mich f�r die volgende L�sung entschieden, da sie meiner Meinung f�r ein "kleines" Programm ausreichend ist
    // Bei extrem vielen Listenelementen w�rde ich eine L�sung vorziehen, in der die Liste wenn m�glich nur einmal durchlaufen werden m�sste.

    // f�r jeden Monat einmal die Liste durchgehen
    for (month = (int)January; month < (int)December + 1; month++) {
        monthTotal = 0;
        monthCalculated = "";
        // f�r jede Kategorie einmal die Liste durchgehen
        for (category = (int)Fuel; category < (int)Other + 1; category++) {
            categorySum = 0;
            // die Liste einmal durchgehen
            for (invoice = anchor; invoice != NULL; invoice = invoice->nextInvoice) {
                if (invoice->category == category && invoice->month == month) {
                    // wenn der Monat und die Kategorie der Rechnung stimmen, auf die momentane Summe der entsprechenden Kategorie aufaddieren
                    categorySum += invoice->amount;
                }
            }
            // f�r die Gesamt ausgaben eines Monats
            monthTotal += categorySum;
            // auf den momentanen Monats string die aktuelle Kategorie "aufaddieren"
            monthCalculated += getCategoryAsString((Category)category) + ":  \t" + convertDoubleToString(categorySum) + " Euro\n";
        }
        printLine();
        cout << getMonthAsString((Month)month) << endl;
        printLine();
        // falls das Limit �berschritten worden ist
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

    // f�r das Menu
    int selection;
    Invoice *invoice;
    // neue Liste erstellen
    ListOfInvoices *listOfInvoices = new ListOfInvoices();
    bool loop = true;

    while (loop) {
        printMenu();
        // Nutzer nach einer aktivit�t fragen
        if (isMenuSelectionValid(selection = getMenuRequest())) {
            printLine();
            switch (selection)
            {
            case 1:
                // Nutzer m�chte eine neue Rechnung eingeben
                invoice = createNewInvoice();
                // Neue Rechnung in die Liste einf�gen
                listOfInvoices->insert(invoice);
                break;
            case 2:
                // Nutzer m�chte sich eine �bersicht ausgeben lassen
                listOfInvoices->printSortedMonthlyOverview();
                break;
            case 3:
                // Nutzer m�chte wissen was er f�r die jeweiligen Kategorien in diesem Jahr ausgegeben hat
                listOfInvoices->printSumOfCategories();
                break;
            case 4:
                // Nutzer m�chte alle Rechnungen anschauen
                // N�tzlich wenn er eine L�schen m�chte
                listOfInvoices->print();
                break;
            case 5:
                // Nutzer m�chte eine Rechnung l�schen
                int numberToRemove;
                // Nutzer fragen welche Rechnung er l�schen m�chte
                printWhichInvoiceToRemove();
                // eingabe des Nutzers hollen
                numberToRemove = getNumberToRemove();
                printLine();
                // versuchen die Rechnung zu L�schen
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
// Nutzer nach aktivit�t fragen
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
// Rechnungsnummer zum l�schen abfragen
int getNumberToRemove() {
    int numberToRemove;
    if (!(cin >> numberToRemove)) {
        return -1;
    }
    return numberToRemove;
}
// Nutzer fragen welche Rechnung gel�scht werden soll
void printWhichInvoiceToRemove() {
    cout << "Rechnung l\x94schen" << endl;
    printLine();
    cout << "Bitte Rechnungsnummer eingeben:" << endl;
}
// sch�ne Ausgabe der Enums Month und Category
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
// f�r Gestalltung f�r das Menu
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

    // Monat abfragen ACHTUNG keine �berpr�fung Nutzer eingabe 35, entspricht halt keinem Monat
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
    // Globale Rechnungsnummer hochz�hlen
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
