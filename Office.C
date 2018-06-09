#include "Office.H"
#include "defs.H"
#include <iostream>

using std::cout;
using std::endl;
using std::string;
using std::boolalpha;

Office::Office() :
	Room(1, 20),
	isBusy_(false)
{
	setOccupied();
}

Result Office::addClass(unsigned int area, double maxRatio,
	unsigned int ageClass,
	unsigned int maxChildren)
{
    if (isBusy_) {
        return FAILURE;
    }

    if (findClassByAge(ageClass) != classes_.end()) {
        return FAILURE;
    }

	classes_.push_back(
        Class(
            (unsigned int)(classes_.size() + 2), 
            area, maxRatio, 
            ageClass, 
            maxChildren));

	return SUCCESS;
}

Result Office::addChild(const Child& child)
{
    if (isBusy_) {
        return FAILURE;
    }

    vector<Class>::iterator classit = findClassByAge(child.getAge());
    if (classit == classes_.end()) {
        return FAILURE;
    }

    classit->addChild(child);
	return SUCCESS;
}

Result Office::addTeacher(const Teacher& teacher)
{
    if (isBusy_) {
        return FAILURE;
    }

    vector<Class>::iterator it = findClassToAddTeacher(teacher);
    if (it == classes_.end()) {
        return FAILURE;
    }

    it->addTeacher(teacher);
    it->setOccupied();

    return SUCCESS;
}

Result Office::removeChild(const string& name)
{
	bool isChildSick = name == sickName_; // check classes_.empty()
    if (isBusy_ && !isChildSick) {// when busy - remove the sick child only
        return FAILURE;
    }

	// try removing the child from every class untill there is SUCCESS (= the child was found and deleted)
	
	for (vector<Class>::iterator curr = classes_.begin();
		curr != classes_.end();
		++curr)
	{
		if (curr->removeChild(name) == SUCCESS)
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
    if (isBusy_) {
        return FAILURE;
    }

	// try removing the teacher from every class untill there is SUCCESS (= the teacher was found and deleted)

	for (vector<Class>::iterator curr = classes_.begin();
		curr != classes_.end();
		++curr)
	{
		if (curr->removeTeacher(name) == SUCCESS)
		{
			return SUCCESS;
		}
	}

	return FAILURE;
}

Result Office::removeClass(size_t age)
{
    if (isBusy_) {
        return FAILURE;
    }

	for (vector<Class>::const_iterator curr = classes_.cbegin();
		curr != classes_.end();
		++curr) {

		if (curr->getAgeClass() == age) {
			classes_.erase(curr);
			return SUCCESS;
		}
	}

	return FAILURE;
}

bool isValidPhoneNumber(const string& number)
{
    return 
        (number.length() == 10) && 
        (number[0] == '0') && 
        (number[1] == '5');
}

Result Office::setSick(const string& name)
{
    if (isBusy_) {
        return FAILURE;
    }

    for (vector<Class>::iterator curr = classes_.begin();
        curr != classes_.end();
        ++curr) {

        Class& currClass = *curr;
    
        string phoneNumber = currClass.getChildPhoneNumber(name);

        if (phoneNumber == "No Child") {
            continue;
        }

        if (!isValidPhoneNumber(phoneNumber)) {
            return FAILURE;
        }

        if (currClass.setIsSick(name) != SUCCESS) {
            return FAILURE;
        }

        sickName_ = name;
        isBusy_ = true;

        cout << "Reporting sick child : \n";
        cout << "Name : " << name << "\n";
        cout << "Parent's phone number : " << phoneNumber << "\n";
   
        return SUCCESS;
    }
    return FAILURE;
}

void Office::print()
{
	cout << "Printing office status : " << std::endl;
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

vector<Class>::iterator Office::findClassToAddTeacher(const Teacher& teacher)
{
    if (classes_.empty()) {
        return classes_.end();
    }

    Class& first = *classes_.begin();

    double maxRatio = first.getCurrentRatio();
    vector<Class>::iterator argMaxRatio = classes_.end();

    size_t minTeachers = first.getTeachersNum();
    vector<Class>::iterator argMinTeachers = classes_.end();

    for (vector<Class>::iterator curr = classes_.begin();
        curr != classes_.end();
        ++curr)
    {
        if (!curr->getIsOccupied())
        {
            return curr;
        }

        double currRatio = curr->getCurrentRatio();
        size_t currTeachersCount = curr->getTeachersNum();

        if (currRatio > maxRatio)
        {
            maxRatio = currRatio;
            argMaxRatio = curr;
        }

        if (currTeachersCount < minTeachers) // not <= so we catch the first
        {
            minTeachers = currTeachersCount;
            argMinTeachers = curr;
        }
    }

    return (maxRatio == 0.0) ? argMinTeachers : argMaxRatio;
}

vector<Class>::iterator Office::findClassByAge(size_t age)
{
    for (vector<Class>::iterator curr = classes_.begin();
        curr != classes_.end();
        ++curr) {
        if (curr->getAgeClass() == age) {
            return curr;
        }
    }
    return classes_.end();
}
