#include "pch.h"
#include <iostream>
#include <cstdlib>
#include <iomanip>
using namespace std;

// globale constante variablen für die Kosten des jeweiligen Eises
const double capri = 1.10;
const double nogger = 1.60;
const double cornetto = 2.30;

// define für credit, bzw. Guthaben
#define CREDIT 5

void printGreeting();
void printAssortment();
void printCredit(double credit);
void printRequest();
int getRequest();
bool isRequestValid(int request);
bool isCreditHighEnough(int request, double credit);
double processRequest(int request, double credit);
void printToLowCredit();
bool isCreditToLowToContinue(double credit);
void printCreditToLowToContinue();
void printTotalAmount(double credit);
void printChange(double credit);
void printGoodbye();

int main()
{
    // ausgabe aller double Werte mit 2 Nachkommastellen
    cout<<fixed<<setprecision(2);

    cout << "Eisverkauf von Lukas Wagenlehner" << endl << endl;

    // lokale variable int in main. Für das Speichern der Benutzereingabe
    int request;

    // lokale variable credit in main. Entspricht dem Guthaben
    double credit = CREDIT;

    // Benutzer begrüßung
    printGreeting();
    // Benutzer das Sortiment zeigen
    printAssortment();
    // Startguthaben anzeigen
    printCredit(credit);
    while (true) {
        // Benutzer zur eingabe auffordern
        printRequest();
        // Benutzer Eingabe überprüfen
        if (isRequestValid(request = getRequest())) {
            // wenn Benutzer Eingabe ok ist
            // Ausrechnen ob der Benutzer noch genügend Guthaben für seine Auswahl hat
            if (isCreditHighEnough(request, credit)) {
                // Benutzer hat genügend Guthaben
                // Neues Guthaben ausrechnen
                credit = processRequest(request, credit);
                // Benutzer über sein verbliebenes Guthaben informieren
                printCredit(credit);
            }
            else
            {
                // Benutzer hat nicht genügend Guthaben um das Eis seiner wahl zu kaufen
                // Benutzer mitteilen das er zu wenig Guthaben hat
                printToLowCredit();
                // Benutzer über sein verbliebenes Guthaben informieren
                printCredit(credit);
            }
            // überprüfen ob der Benutzer mit dem restlichen Guthaben noch mindestens das günstigste Eis kaufen kann
            if (isCreditToLowToContinue(credit)) {
                // Benutzer hat zu wenig Guthaben um das günstigste Eis zu kaufen
                // Benutzer mitteilen das er kein weiteres Eis kaufen kann
                printCreditToLowToContinue();
                // Schleife verlassen
                break;
            }
        }
        else
        {
            // wenn Benutzer Eingabe falsch ist bzw. der Nutzer wünscht abzubrechen
            // Schleife verlassen
            break;
        }
        
    }
    // Benutzer den Gesamtbetrag seines Kaufes mitteilen
    printTotalAmount(credit);
    // Benutzer das Wechselgeld ausrechnen und mitteilen
    printChange(credit);
    // Benutzer verabschieden
    printGoodbye();

    system("pause");
    return EXIT_SUCCESS;
}

void printGreeting() {
    // Benutzer begrüßen
    cout << "Willkommen beim Eisverkauf!" << endl;
}
void printAssortment() {
    // Sortiment auf der Konsole ausgeben
    cout << endl;
    cout << "1. Capri:\t" << capri << " Euro" << endl;
    cout << "2. Nogger:\t" << nogger << " Euro" << endl;
    cout << "3. Cornetto:\t" << cornetto << " Euro" << endl;
    cout << endl;
}
void printCredit(double credit) {
    // Guthaben ausgeben
    cout << "Dein Guthaben betraegt: " << credit <<" Euro" <<endl<<endl;
}
void printRequest() {
    // Benutzer um eine Eingabe bitten
    cout << "Bitte mit 1,2 oder 3 ein Eis ausw\x84hlen. Belibige andere Taste dr\x81\cken um zu bezahlen oder abzubrechen." << endl;
}
int getRequest() {
    // mit cin eine int Eingabe von der Konsole holen, falls der Benutzer eine ungültige eingabe macht -1 zurückgeben
    int selection;
    if (!(cin >> selection)) {
        return -1;
    }
    return selection;
}
bool isRequestValid(int request) {
    // überprüfen ob der Benutzer eine 1,2 oder 3 eingegeben hat
    if (request > 0 && request < 4) {
        return true;
    }
    else {
        return false;
    }
}
bool isCreditHighEnough(int request,double credit) {
    // ausrechnen ob der Benutzer genügend Guthaben hat um das gewählte Eis bezahlen zu können
    double cost=0;
    switch (request)
    {
    case 1:
        cost = capri;
        break;
    case 2:
        cost = nogger;
        break;
    case 3:
        cost = cornetto;
        break;
    default:
        break;
    }
    credit -= cost;
    if (credit < 0) {
        return false;
    }
    else
    {
        return true;
    }
}
double processRequest(int request,double credit) {
    // neues Guthaben ausrechnen, indem die Kosten für das ausgewählte Eis abgezogen werden 
    double cost;
    if (request == 1) {
        cost = capri;
    }
    else if(request == 2)
    {
        cost = nogger;
    }
    else
    {
        cost = cornetto;
    }
    credit -= cost;
    return credit;
}
void printToLowCredit() {
    // Dem Benutzer mitteilen, dass er zuwenig Guthaben hat
    cout << "Dein Guthaben ist zu klein." << endl;
}
bool isCreditToLowToContinue(double credit) {
    // ausrechnen ob der Benutzer überhaupt noch genügend Guthaben hat um ein weiteres Eis zu kaufen
    credit -= capri;
    if (credit >= 0) {
        return false;
    }
    else {
        return true;
    }
}
void printCreditToLowToContinue() {
    // Benutzer informieren, dass sein Guthaben zu klein ist um ein weiteres Eis zu kaufen
    cout << "Dein Guthaben ist leider zu klein um ein weiteres Eis zu kaufen." << endl;
}
void printTotalAmount(double credit) {
    // Gesamtbetrag ausrechnen, indem vom Startguthaben das übrige Guthaben abgezogen wird
    double cost = CREDIT- credit;
    cout << "Der Gesamtbetrag f\x81r deine Bestellung ist: " << cost << " Euro"<< endl;
}
void printChange(double credit) {
    // ausrechnen des Wechselgeldes und in Euro und Cent ausgeben
    int euro=0;
    int cent=0;
    while (credit > 0.99) {
        credit--;
        euro++;
    }
    while (credit > 0.09) {
        credit -= 0.10;
        cent+=10;
    }
    cout << "Dein Wechselgeld betr\x84gt " << euro << " Euro und " << cent << " Cent." << endl;
}
void printGoodbye() {
    // Benutzer verabschieden
    cout << "Vielen dank f\x81r den Besuch!" << endl;
}


