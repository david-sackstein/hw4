#include "Class.H"
#include "defs.H"

#include <iostream>

using std::cout;
using std::endl;

// Add your code here ...
Class::Class(
    unsigned int roomNumber, unsigned int area,
    double maxRatio, unsigned int ageClass,
    unsigned int maxChildren)
    :
    Room(roomNumber, area),
    maxRatio_(maxRatio),
    ageClass_(ageClass),
    maxChildren_(maxChildren)
{
}

string Class::getChildPhoneNumber(const string& name) const
{
    for (vector<Child>::const_iterator curr = children_.begin(); 
        curr != children_.end(); 
        curr++) {
        const Child& child = *curr;
        if (child.getName() == name) {
            return child.getPhoneNumber();
        }
    }

    return "No Child";
}

void Class::addTeacher(const Teacher& teacher)
{
    teachers_.push_back(teacher);
}

void Class::addChild(const Child& child)
{
    //unsigned int  = newNum
}

void Class::removeTeacher(const string& name)
{

}

void Class::removeChild(const string& name)
{

}

Result Class::setIsSick(const string& name)
{
	return FAILURE;
}
