#include "pch.h"
#include "Question.h"

using namespace std;

Question::Question() {

}

Question::Question(string question,list<string> answers):question(question),answers(answers)
{
}

Question::~Question()
{
}

ostream& operator<<(ostream& os, const Question& question) {
    os << question.question << endl << endl;
    int i = 1;
    for (list<string>::const_iterator iterator = question.answers.begin(), end = question.answers.end(); iterator != end; iterator++) {
        os << "["<<i<<"]"<<"\t" << *iterator<< endl;
        i++;
    }
    return os;
}
