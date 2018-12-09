#include "pch.h"
#include <iostream>
#include <ctime>
#include <string>

using namespace std;

int main()
{
    // Felder
    int lotto[6];
    int i, j;
    bool newNumber;

    srand(time(NULL));
    for (i = 0; i < 6; i++) {
        do {
            lotto[i] = rand() % 49 + 1;
            newNumber = true;
            for (j = 0; j < i; j++) {
                if (lotto[j] == lotto[i]) {
                    newNumber = false;
                }
            }
        } while (!newNumber);
    }
    for (i = 0; i < 6; i++) {
        cout << lotto[i] << " ";
    }
    cout << endl;
    system("pause");

    // mehrdimensionale Felder

    float numbers[2][12] = { {20.5, 22, 25.2, 30, 55, 66, 74, 20.55, 22, 25.2, 30, 55},
                           {20.55, 22, 25.2, 55, 8, 99, 44, 22.5, 66.3, 10, 11, 12.5} };
    float umsatz[2][1] = { {0},{0} };

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 12; j++) {
            umsatz[i][0] += numbers[i][j];
        }
    }
    cout << "Umsatz 1.Jahr: " << umsatz[0][0] << endl;
    cout << "Umsatz 2.Jahr: " << umsatz[1][0] << endl;

    system("pause");

    // string

    string str1 = "Mein Haus";
    string str2 = str1.substr(5, 4);
    string str3 = str1.erase(1, 5);

    cout << str2 << endl;
    cout << str3 << endl;

    string strA = "Klein";
    string strB = "Schw";
    string strC = strA.replace(0, 2, strB);
    cout << strC << endl << endl;

    string str4 = "abcd";
    cout << str4.length() << endl;
    cout << str4.find("d") << endl;

    system("pause");

    // bubblesort

    int numbersToSort[6] = { 43,22,100,500,3,99 };
    for (i = 0; i < 6; i++) {
        cout << numbersToSort[i]<<" ";
    }
    cout << endl;

    int tmp;
    i = 0; j = 0;
    for (i = 0; i < 6 - 1; ++i) {
        for (j = 0; j < 6 - i - 1;++j) {
            if (numbersToSort[j] > numbersToSort[j + 1]) {
                tmp = numbersToSort[j];
                numbersToSort[j] = numbersToSort[j + 1];
                numbersToSort[j + 1] = tmp;
            }
        }
    }
    for (i = 0; i < 6; i++) {
        cout << numbersToSort[i] << " ";
    }
    cout << endl;
    system("pause");

    return EXIT_SUCCESS;
}

