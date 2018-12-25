
#include "pch.h"
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

class Person {
private:
    float einkommen;
public: 

    string vorname;
    string nachname;
    int alter;
    
    void datenAusgeben() 
    {
        cout << vorname << endl;
        cout << nachname << endl;
        cout << alter << endl;
        cout << einkommen <<endl;
    }
    void einkommenEingeben() {
        cout << "Einkommen eingeben: ";
        cin >>  einkommen;
    }
};

int main()
{
    Person person = Person();
    person.vorname = "Max";
    person.nachname = "Mustermann";
    person.alter = 25;
    person.einkommenEingeben();
    person.datenAusgeben();
    system("pause");
    return EXIT_SUCCESS;
}

