#ifndef _PERSON_H_
#define _PERSON_H_

#include <string>
#include <iostream>

using std::string;

class Person {

public:
    Person(const string& name, unsigned int age);

    unsigned int getAge() const { return age_; }
    const string& getName() const { return name_; }

    void print() const;

private:

    string name_;
    unsigned int age_;
};

#endif
