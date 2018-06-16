#include "Child.H"

using std::cout;
using std::endl;
using std::boolalpha;

//**********************************************************
//  Function name : Child::Child
//  Description   : Create new child with given name, age
//					and phone number.
//  Paramaters    : name - reference pointer of name
//					age - integer of age
//					phoneNumber - reference pointer of num
//  Return value  : None.
//**********************************************************
Child::Child(const string& name, unsigned int age, const string& phoneNumber) :
    Person(name, age),
    phoneNumber_(phoneNumber),
    isSick_(false)
{
}

//**********************************************************
//  Function name : Child::setIsSick
//  Description   : Set child to sick.
//  Paramaters    : None.
//  Return value  : Return SUCCESS if setting passed,
//					otherwise return FAILURE.
//**********************************************************
Result Child::setIsSick() {
    if (!isSick_)
    {
        isSick_ = true;
        return SUCCESS;
    }
    return FAILURE;
};

//**********************************************************
//  Function name : Child::print
//  Description   : Prints childs' features.
//  Paramaters    : None.
//  Return value  : None.
//**********************************************************
void Child::print() const {
    Person::print();
    cout << "Parent's Phone : " << phoneNumber_ << 
        "\nIs sick : " << boolalpha << isSick_ << "\n";
}


