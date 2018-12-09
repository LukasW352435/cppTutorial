#include "pch.h"
#include <iostream>
using namespace std;

#define MAX_MITARBEITER 500

class Datum {
public:
    int Tag;
    int Monat;
    int Jahr;
    Datum();
    Datum(int Tag,int Monat,int Jahr);
};
Datum::Datum() {

}
Datum::Datum(int Tag,int Monat,int Jahr):Tag(Tag),Monat(Monat),Jahr(Jahr) {

}


class Mitarbeiter {
private:
    bool gueltig;
    string Name;
    string Vorname;
    Datum Geburtsdatum;
    int VerbrauchteUrlaubsTage;
    int UrlaubsTage;
public:
    Mitarbeiter();
    Mitarbeiter(string Name,string Vorname,Datum Geburtsdatum);
    ~Mitarbeiter();
    void BerechneUrlaubsTage(Datum aktuellesDatum);

};
Mitarbeiter::Mitarbeiter() {
    gueltig = false;
}

Mitarbeiter::Mitarbeiter(string Name, string Vorname, Datum Geburtsdatum):Name(Name),Vorname(Vorname),Geburtsdatum(Geburtsdatum) {
    VerbrauchteUrlaubsTage = 0;
    UrlaubsTage = 0;
    gueltig = true;
}
Mitarbeiter::~Mitarbeiter() {

}

void Mitarbeiter::BerechneUrlaubsTage(Datum aktuellesDatum) {
    int alter = aktuellesDatum.Jahr - Geburtsdatum.Jahr;
    if (alter >= 50) {
        UrlaubsTage = 32;
    }
    else{
        UrlaubsTage = 30;
    }
}

class Verwaltung {
private:
    Mitarbeiter MitarbeiterListe[MAX_MITARBEITER];
public:
    Verwaltung();
    bool MitarbeiterAnlegen(Mitarbeiter neuerMitarbeiter);
    bool MitarbeiterLoeschen(int index);
    void AuflistungAllerMitarbeiter();
};
Verwaltung::Verwaltung() {

}
bool Verwaltung::MitarbeiterAnlegen(Mitarbeiter neuerMitarbeiter) {
    for (int i = 0; i < MAX_MITARBEITER; i++) {
        if (MitarbeiterListe[i] == ) {

        }
    }
}

int main()
{
    Verwaltung verwaltung;
    system("pause");
    return EXIT_SUCCESS;
}