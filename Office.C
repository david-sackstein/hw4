#include "Office.H"
#include "defs.H"
#include <iostream>

using std::cout;
using std::endl;
using std::string;
using std::boolalpha;

Office::Office() :
	Room(1, 20),
	isBusy_(false),
	sickName_("")
{
	setOccupied();
}

Class* Office::getClass(size_t age)
{
	for (vector<Class>::iterator curr = classes_.begin();
		curr != classes_.end();
		++curr) {
		Class& myClass = *curr;
		if (myClass.getAgeClass() == age)
			return &myClass;
	}
	return NULL;
}

Child* Office::getChild(const string& name)
{
	for (vector<Class>::iterator curr = classes_.begin();
		curr != classes_.end();
		++curr) {

		Class& myClass = *curr;
		Child* child = myClass.getChild(name);
		if (child != NULL)
			return child;
	}
	return NULL;
}

Result Office::addClass(unsigned int area, double maxRatio,
	unsigned int ageClass,
	unsigned int maxChildren)
{
	if (isBusy_)
		return FAILURE;

	if (getClass(ageClass) != NULL)
		return FAILURE;

	Class newClass = Class(classes_.size() + 2, area, maxRatio, ageClass, maxChildren);
	classes_.push_back(newClass);

	return SUCCESS;
}

Result Office::addChild(const Child& child)
{
	if (isBusy_)
		return FAILURE;

	Class* myClass = getClass(child.getAge());
	if (myClass == NULL)
		return FAILURE;

	(*myClass).addChild(child);
	return SUCCESS;
}

Result Office::addTeacher(const Teacher& teacher)
{
	if (isBusy_)
		return FAILURE;

	// find most crowded ratio and min number of teachers
	// if an empty class is found -- add teacher

	double maxRatio = (*classes_.begin()).getCurrentRatio();
	size_t minTeachers = (*classes_.begin()).getTeachersNum();
	for (vector<Class>::iterator curr = classes_.begin(); // i had to remove const due to addTeacher
		curr != classes_.end(); ++curr)
	{
		Class& myClass = *curr;
	
		if (!myClass.getIsOccupied())
		{
			myClass.addTeacher(teacher);
			myClass.setOccupied();
			return SUCCESS;
		}
		
		double currRatio = myClass.getCurrentRatio();
		size_t currTeachersCount = myClass.getTeachersNum();
		if (currRatio > maxRatio)
		{
			maxRatio = currRatio;
		}
		if (minTeachers > currTeachersCount)
		{
			minTeachers = currTeachersCount;
		}
	}

	// add teacher to first minTeachers class
	for (vector<Class>::iterator curr = classes_.begin();
		curr != classes_.end(); ++curr)
	{
		Class& myClass = *curr;

		if (myClass.getTeachersNum() == minTeachers)
		{
			myClass.addTeacher(teacher);
			return SUCCESS;
		}
	}

	return FAILURE;
}

Result Office::removeChild(const string& name)
{
	bool isChildSick = name == sickName_;
	if (isBusy_ && !isChildSick) // when busy - remove the sick child only
		return FAILURE;

	// try removing the child from every class untill there is SUCCESS (= the child was found and deleted)
	
	for (vector<Class>::iterator curr = classes_.begin();
		curr != classes_.end();
		++curr)
	{
		Class& myClass = *curr;

		if (myClass.removeChild(name) == SUCCESS)
		{
			if (isChildSick)
			{
				isBusy_ = false;
				sickName_ = "";
			}
			return SUCCESS;
		}
	}

	return FAILURE;
}

Result Office::removeTeacher(const string& name)
{
	if (isBusy_)
		return FAILURE;

	// try removing the teacher from every class untill there is SUCCESS (= the teacher was found and deleted)

	for (vector<Class>::iterator curr = classes_.begin();
		curr != classes_.end();
		++curr)
	{
		Class& myClass = *curr;

		if (myClass.removeTeacher(name) == SUCCESS)
		{
			return SUCCESS;
		}
	}

	return FAILURE;
}

Result Office::removeClass(size_t age)
{
	if (isBusy_)
		return FAILURE;

	for (vector<Class>::const_iterator curr = classes_.cbegin();
		curr != classes_.end();
		++curr) {

		const Class& myClass = *curr;
		if (myClass.getAgeClass() == age) {
			classes_.erase(curr);
			return SUCCESS;
		}
	}


	return FAILURE;
}

bool isValidPhoneNumber(const string& number)
{
	return (number.length() == 10) && (number[0] == '0') && (number[1] == '5')
		? true
		: false;
}

Result Office::setSick(const string& name)
{
	if (isBusy_)
		return FAILURE;

	Child* child = getChild(name);
	if (child == NULL)
		return FAILURE;

	string phoneNumber = (*child).getPhoneNumber();
	if (!isValidPhoneNumber(phoneNumber))
		return FAILURE;

	if ((*child).setIsSick() != SUCCESS)
		return FAILURE;
	
	sickName_ = (*child).getName();
	isBusy_ = true;

	cout << "Reporting sick child : \n";
	cout << "Name : " << (*child).getName() << "\n";
	cout << "Parent's phone number : " << phoneNumber << "\n";

	return SUCCESS;
}

void Office::print()
{
	cout << "Printing office status : \n";
	cout << "========================\n";
	Room::print();

	cout << "Office is busy : " << boolalpha << isBusy_ << "\n";
	if(sickName_ != "")
		cout << "Sick child : " << sickName_ << "\n";
	cout << "\n";

	if (classes_.size() != 0)
	{
		for (vector<Class>::const_iterator curr = classes_.begin();
			curr != classes_.end();
			++curr) {
			const Class& myClass= *curr;
			myClass.print();
		}
	}
}

