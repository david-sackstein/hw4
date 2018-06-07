#ifndef _TEACH_H_
#define _TEACH_H_
#include "Person.H"
#include <string>
#include <iostream>

class Teacher : public Person{
public:

    Teacher(const string& name, unsigned int age, unsigned int seniority);

    unsigned int getSeniority() const { return seniority_; }
    void setSeniority(unsigned int seniority) { seniority_ = seniority; }
    void print() const;

private:

    unsigned int seniority_;
};

#endif
