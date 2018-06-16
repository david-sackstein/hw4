#include "Class.H"
#include "defs.H"

#include <iostream>

using std::cout;
using std::endl;

//**********************************************************
//  Function name : Room::Room
//  Description   : Create new class with room number, area,
//					max ratio, age and max children number. 
//  Paramaters    : roomNumber - integer of Room Number
//					area - area value
//					maxRatio - double of max ratio ch/te
//					ageClass - age value
//					maxChildren - max children number
//  Return value  : None.
//**********************************************************
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

//**********************************************************
//  Function name : Class::getChildPhoneNumber
//  Description   : Get phone number by childs' name.
//  Paramaters    : name - reference pointer to name str
//  Return value  : None.
//**********************************************************
string Class::getChildPhoneNumber(const string& name) const
{
    for (vector<Child>::const_iterator curr = children_.cbegin(); 
        curr != children_.end(); 
        curr++) {
        if (curr->getName() == name) {
            return curr->getPhoneNumber();
        }
    }

    return "No Child";
}

//**********************************************************
//  Function name : Class::addTeacher
//  Description   : Add teacher to classes' teachers vector.
//  Paramaters    : teacher - reference pointer to teacher
//  Return value  : None.
//**********************************************************
void Class::addTeacher(const Teacher& teacher)
{
    teachers_.push_back(teacher);
}

//**********************************************************
//  Function name : Class::addChild
//  Description   : Add child to classes' children vector.
//  Paramaters    : child - const reference pointer to child
//  Return value  : Return SUCCESS if addition passed,
//					otherwise return FAILURE.
//**********************************************************
Result Class::addChild(const Child& child)
{
    if (teachers_.size() == 0) {
        return FAILURE;
    }
	
	size_t newClassSize = children_.size() + 1;
	double newRatio = newClassSize / (double)teachers_.size();

    if ((newRatio > maxRatio_) || (newClassSize > maxChildren_)) {
        return FAILURE;
    }

	children_.push_back(child);
	return SUCCESS;
}

//**********************************************************
//  Function name : Class::removeTeacher
//  Description   : Remove teacher from the class, if
//					max ratio allows it.
//  Paramaters    : name - reference pointer to teachers'
//						   name.
//  Return value  : Return SUCCESS if deletion passed,
//					otherwise return FAILURE.
//**********************************************************
Result Class::removeTeacher(const string& name)
{
	size_t teacherCount = teachers_.size();

	if (teacherCount <= 1) {
		return FAILURE;
	}

	double newRatio =  children_.size() / (double)(teacherCount - 1);

	if (newRatio > maxRatio_) {
		return FAILURE;
	}

	for (vector<Teacher>::const_iterator curr = teachers_.cbegin();
		curr != teachers_.end();
		++curr) {

		if (curr->getName() == name) {
			teachers_.erase(curr);
			return SUCCESS;
		}
	}
	return FAILURE;
}

//**********************************************************
//  Function name : Class::removeChild
//  Description   : Remove child from the class.
//  Paramaters    : name - reference pointer to childs' name
//  Return value  : Return SUCCESS if deletion passed,
//					otherwise return FAILURE.
//**********************************************************
Result Class::removeChild(const string& name)
{
	for (vector<Child>::const_iterator curr = children_.cbegin();
		curr != children_.end();
		++curr) {
		
		if (curr->getName() == name) {
			children_.erase(curr);
			return SUCCESS;
		}
	}
	return FAILURE;
}

//**********************************************************
//  Function name : Class::setIsSick
//  Description   : Set child in class to sick.
//  Paramaters    : name - reference pointer to sick childs'
//						   name.
//  Return value  : Return SUCCESS if setting passed,
//					otherwise return FAILURE.
//**********************************************************
Result Class::setIsSick(const string& name)
{
	for (vector<Child>::iterator curr = children_.begin();
		curr != children_.end();
		curr++) {
		if (curr->getName() == name) {
			return curr->setIsSick();
		}
	}

	return FAILURE;
}

//**********************************************************
//  Function name : Class::print
//  Description   : Prints classes' features.
//  Paramaters    : None.
//  Return value  : None.
//**********************************************************
void Class::print() const
{
	size_t childrenCount = children_.size();
	size_t teachersCount = teachers_.size();

	cout << "Printing class status : \n";
	cout << "========================\n";
	Room::print();

	cout << "Max number of children : " << maxChildren_ << "\n";
	cout << "Number of children : " << childrenCount << "\n";
	cout << "Number of teachers : " << teachersCount << "\n";
	cout << "Max value for ratio : " << maxRatio_ << "\n";
	cout << "Current ratio : " << getCurrentRatio() << "\n";
	cout << "Children age range : " << ageClass_ << " - " << (ageClass_ + 1) << "\n";
	cout << "\n";

	if (childrenCount != 0)
	{
		cout << "Printing childrens status : \n";
		cout << "========================\n";
		for (vector<Child>::const_iterator curr = children_.begin();
			curr != children_.end();
			curr++) {
			const Child& child = *curr;
			child.print();
		}
		cout << "\n";
	}

	if (teachersCount != 0)
	{
		cout << "Printing teachers status : \n";
		cout << "========================\n";
		for (vector<Teacher>::const_iterator curr = teachers_.begin();
			curr != teachers_.end();
			curr++) {
			const Teacher& teacher = *curr;
			teacher.print();
		}
		cout << "\n";
	}
}