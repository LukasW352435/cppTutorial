// 3_controlStructures.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <cstdlib>
using namespace std;
int main()
{
    std::cout << "Control Structures\n";
    int x;
    cout << "Geben Sie eine Zahl ein: ";
    cin >> x;
    if
        (x > 10)
    {
        cout << "Die eingegebene Zahl ist größer als 10." << endl;
    }

    cout << endl << "Programmstart FOR..." << endl << endl;
    int i;
    cout << "   1. FOR-Schleife " << endl;
    for (i = 0; i < 12; i++)
    {
        cout << "Aufstieg  " << i << endl;
    }
    cout << "   2. FOR-Schleife " << endl;
    for (int j = 10; j > 0; j--)
    {
        cout << "Abstieg  " << j << endl;
    }
    system("pause");
}

