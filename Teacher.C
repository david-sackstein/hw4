#include "Teacher.H"

using std::string;
using std::cout;
using std::endl;

Teacher::Teacher(const string& name, unsigned int age, unsigned int seniority) :
    Person(name, age),
    seniority_(seniority)
{
}

void Teacher::print() const {
    Person::print();
    cout << "Seniority : " << seniority_ << "\n";
}

