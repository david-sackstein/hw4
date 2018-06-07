#include "Person.H"

using std::string;
using std::cout;
using std::endl;

Person::Person(const string& name, unsigned int age) :
    name_(name),
    age_(age)
{
}

void Person::print() const
{
    cout << "Name : " << name_ << "\nAge : "<< age_ << "\n";
}