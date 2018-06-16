#ifndef _CHILD_H_
#define _CHILD_H_

#include "Person.H"
#include "defs.H"
#include <string>
#include <iostream>

using std::string;

class Child : public Person {

public:

    Child(
        const string& name, 
        unsigned int age, 
        const string& phoneNumber);

    const string& getPhoneNumber() const { return phoneNumber_; }

    void setPhoneNumber(const string& phoneNumber) { phoneNumber_ = phoneNumber; }
    Result setIsSick();

    void print() const;

private:
    
    string phoneNumber_;
    bool isSick_;
};

#endif
