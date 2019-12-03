#include <string>
#include <iostream>
#include <iomanip>
#include <list>

class Question
{
private:
    std::string question;
    std::list<std::string> answers;
public:
    Question();
    Question(std::string question,std::list<std::string> answers);
    ~Question();
    friend std::ostream& operator<< (std::ostream& os, const Question& question);
};

