#ifndef _CLASS_H_
#define _CLASS_H_

#include <string>
#include <iostream>
#include <vector>
#include "defs.H"
#include "Room.H"
#include "Child.H"
#include "Teacher.H"

using std::string;
using std::vector;
using std::size_t;

class Class : public Room {
public:
    Class(unsigned int roomNumber, 
        unsigned int area, 
        double maxRatio,
        unsigned int ageClass, 
        unsigned int maxChildren);

    size_t getTeachersNum() const { return teachers_.size(); }
	size_t getAgeClass() const { return ageClass_; }
    double getCurrentRatio() const { return (teachers_.size() == 0) ? -1 : children_.size() / (double)teachers_.size(); }
    string getChildPhoneNumber(const string& name) const;

    void addTeacher(const Teacher& teacher);
	Result addChild(const Child& child);
    Result removeTeacher(const string& name);
    Result removeChild(const string& name);

    Result setIsSick(const string& name);

	void print() const;

	Child* Class::getChild(const string& name);

private:

    double maxRatio_;
	std::size_t maxChildren_;
	std::size_t ageClass_;
    vector<Child> children_;
    vector<Teacher> teachers_;
};

#endif
