// 2_BasikSyntax.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <cstdlib>
using namespace std;

int multiply(int, int);
void showResult(int);

inline int maximum(int a, int b) {
    return a > b ? a : b;
}

int main()
{
    cout << "Basic Syntax!\n"; 
    //int x = 10;
    //cout << "x = " << x++ << endl; // 10
    //cout << "x = " << x << endl;   // 11
    //cout << "x = " << ++x << endl; // 12
    //cout << "x = " << x << endl;   // 12

    int x, y, ergebnis;
    cout << "Bitte geben Sie den ersten Wert ein:";
    cin >> x;
    cout << "Bitte geben Sie den zweiten Wert ein:";
    cin >> y;

    ergebnis = multiply(x, y);
    showResult(ergebnis);

    cout <<"Maximum aus 4,7 ist: " <<maximum(4, 7) << endl;

    float var;
    if (!(cin >> var)) {
        cerr << "Fehler: Keine Zahl eingelesen!\n";
    }
    else
    {
        cout << var << endl;
    }
    if (!(cin >> var)) {
        cerr << "Fehler: Keine Zahl eingelesen!\n";
    }
    else
    {
        cout << var << endl;
    }
    system("pause");
    return EXIT_SUCCESS;
}

int multiply(int a, int b) {
    return a * b;
}
void showResult(int result) {
    cout << "Ergebnis der Multiplikation: " << result<<endl;
}