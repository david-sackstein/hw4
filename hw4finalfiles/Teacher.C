#include "Teacher.H"

using std::string;
using std::cout;
using std::endl;

//**********************************************************
//  Function name : Teacher::Teacher
//  Description   : Create new teacher with given name, age
//					and seniority.
//  Paramaters    : name - reference pointer of name
//					age - integer of age
//					seniority - integer of seniority
//  Return value  : None.
//**********************************************************
Teacher::Teacher(const string& name, unsigned int age, unsigned int seniority) :
    Person(name, age),
    seniority_(seniority)
{
}

//**********************************************************
//  Function name : Teacher::print
//  Description   : Prints teachers' features.
//  Paramaters    : None.
//  Return value  : None.
//**********************************************************
void Teacher::print() const {
    Person::print();
    cout << "Seniority : " << seniority_ << "\n";
}

