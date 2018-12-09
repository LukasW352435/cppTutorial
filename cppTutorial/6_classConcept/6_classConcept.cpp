#include "pch.h"
#include <iostream>
#include <cstdlib>
using namespace std;

class Konto
{
private:
    int Kontostand;
public:
    Konto();
    ~Konto();
    int setKontostand(int kontostand);
    int getKontostand();
};
Konto::Konto() {
    cout << "Neues Konto erzeugt." << endl;
}
Konto::~Konto() {
    cout << "Konto gel\x94scht." << endl;
}

int Konto::setKontostand(int kontostand) {
    if (kontostand >= 0 && kontostand <= 1000) {
        Kontostand = kontostand;
        return 1;
    }
    else {
        return 0;
    }
}
int Konto::getKontostand() {
    return Kontostand;
}

int main()
{
    Konto TestKonto;
    int alternative = 0;
    int wert = 0;
    TestKonto.setKontostand(0);
    cout << "Kontoverwaltung" << endl;
    do {
        cout << "1 = Kontostand \x84ndern" << endl;
        cout << "2 = Kontostand lesen" << endl;
        cout << "0 = Ende der Aktion" << endl << endl;
        cout << "Ihre Wahl:";
        cin >> alternative;
        switch (alternative) {
        case 1:
            cout << "Neuer Wert:";
            cin >> wert;
            if (TestKonto.setKontostand(wert)) {
                cout << "Wert ge\x84ndert." << endl << endl;
            }
            else {
                cout << "Wert nicht ge\x84ndert." << endl << endl;
            }
            break;
        case 2:
            cout << "Aktueller Wert:";
            cout << TestKonto.getKontostand() << endl << endl;
            break;
        }
    } while (alternative);
    TestKonto.~Konto();
    system("pause");
    return EXIT_SUCCESS;
}

