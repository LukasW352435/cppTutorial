#include "pch.h"
#include <iostream> 
#include <string>
using namespace std;
class Klausur
{
private:
    int i;
    string s;

    Klausur()
    {}
    Klausur(int ii)
    {
        i = ii; 
        s = "";
    }
    Klausur(int ii, string ss) : i(ii), s(ss)
    {
    }
    void zeigDich()
    {
        cout << i << " " << s << endl;
    }
    friend Klausur operator+(const Klausur &links, const Klausur &rechts);
    friend void operator==(const Klausur &links, const Klausur &rechts);

};

Klausur operator+(const Klausur &links, const Klausur &rechts)
{
    Klausur tmp;
    tmp.i = links.i + rechts.i;
    tmp.s = links.s + rechts.s;
    return(tmp);
}
void operator==(const Klausur &links, const Klausur &rechts) {
    if (links.i == rechts.i && links.s == rechts.s ) {
        cout << "gleich" << endl;

    }
    else
    {
        cout << "nicht gleich" << endl;
    }
}
int main()
{
    for (int x = 10; x <= 20; x += 2) { cout << x; }
    system("PAUSE");
}
//#include "Question.h"
//#include <iostream>
//
//using namespace std;
//
//int main()
//{
//    string question = "Welche Farbe hat der Himmel?";
//    list<string> answers = { "Blau","Rot","Gelb","Schwarz" };
//    Question q = Question(question, answers);
//    cout << q;
//    system("pause");
//    return EXIT_SUCCESS;
//}
