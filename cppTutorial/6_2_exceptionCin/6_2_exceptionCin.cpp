// 6_2_exceptionCin.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <cstdlib>

using namespace std;
int main()
{
    int room_choice;
    try {
        while (true)
        {
            cout << "\nEnter room to move to: ";

            if (cin >> room_choice) {

            }

            else if (cin.fail())
            {
                cin.clear();
                //cin.ignore();
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear out the input buffer
                cout << "Incorrect entry. Try again. "<<endl;
            }
            char again;
            cout << "Again?" << endl;
            cin >> again;
            if (again == 'y') {
                continue;
            }
            else
            {
                break;
            }
        }
    }
    catch (...) {
        cout << "Error" << endl;
    }
    system("pause");
    return EXIT_SUCCESS;
}

