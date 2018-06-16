#include "Person.H"

using std::string;
using std::cout;
using std::endl;

//**********************************************************
//  Function name : Person::Person
//  Description   : Create new person with given name and
//					age.
//  Paramaters    : name - reference pointer of name
//					age - integer of age
//  Return value  : None.
//**********************************************************
Person::Person(const string& name, unsigned int age) :
    name_(name),
    age_(age)
{
}

//**********************************************************
//  Function name : Person::print
//  Description   : Prints persons' features.
//  Paramaters    : None.
//  Return value  : None.
//**********************************************************
void Person::print() const
{
    cout << "Name : " << name_ << "\nAge : "<< age_ << "\n";
}