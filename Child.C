#include "Child.H"

using std::cout;
using std::endl;
using std::boolalpha;

Child::Child(const string& name, unsigned int age, const string& phoneNumber) :
    Person(name, age),
    phoneNumber_(phoneNumber),
    isSick_(false)
{
}

Result Child::setIsSick() {
    if (!isSick_)
    {
        isSick_ = true;
        return SUCCESS;
    }
    return FAILURE;
};

void Child::print() const {
    Person::print();
    cout << "Parent's Phone : " << phoneNumber_ << 
        "\nIs sick : " << boolalpha << isSick_ << "\n";
}


