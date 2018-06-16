#include "Office.H"
#include "defs.H"
#include <iostream>

using std::cout;
using std::endl;
using std::string;
using std::boolalpha;

//**********************************************************
//  Function name : Office::Office
//  Description   : Create new office with room number 1
//					and area of 20 sm. Set occupacion to
//					true and initialize busy to false.
//  Paramaters    : None.
//  Return value  : None.
//**********************************************************
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

//**********************************************************
//  Function name : Office::addChild
//  Description   : Add child to appropriate class, if
//					possible.
//  Paramaters    : child - const reference pointer to child
//  Return value  : Return SUCCESS if addition passed,
//					otherwise return FAILURE.
//**********************************************************
Result Office::addChild(const Child& child)
{
    if (isBusy_) {
        return FAILURE;
    }

    vector<Class>::iterator classit = findClassByAge(child.getAge());
    if (classit == classes_.end()) {
        return FAILURE;
    }

	return classit->addChild(child);
}

//**********************************************************
//  Function name : Office::addTeacher
//  Description   : Add teacher to appropriate class, if
//					possible.
//  Paramaters    : teacher - reference pointer to teacher
//  Return value  : Return SUCCESS if addition passed,
//					otherwise return FAILURE.
//**********************************************************
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

//**********************************************************
//  Function name : Office::removeChild
//  Description   : Remove child from his/her class.
//  Paramaters    : name - reference pointer to childs' name
//  Return value  : Return SUCCESS if deletion passed,
//					otherwise return FAILURE.
//**********************************************************
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

//**********************************************************
//  Function name : Office::removeTeacher
//  Description   : Remove teacher from his/her class.
//  Paramaters    : name - reference pointer to teachers'
//						   name.
//  Return value  : Return SUCCESS if deletion passed,
//					otherwise return FAILURE.
//**********************************************************
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

//**********************************************************
//  Function name : Office::removeClass
//  Description   : Remove class and all its people.
//  Paramaters    : age - class age
//  Return value  : Return SUCCESS if deletion passed,
//					otherwise return FAILURE.
//**********************************************************
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

//**********************************************************
//  Function name : isValidPhoneNumber
//  Description   : Check if phone number is valid.
//  Paramaters    : number - reference pointer to string of
//							 number.
//  Return value  : Return SUCCESS if number is valid,
//					otherwise return FAILURE.
//**********************************************************
bool isValidPhoneNumber(const string& number)
{
    return 
        (number.length() == 10) && 
        (number[0] == '0') && 
        (number[1] == '5');
}

//**********************************************************
//  Function name : Office::setSick
//  Description   : Set child to sick and office to busy.
//  Paramaters    : name - reference pointer to sick childs'
//						   name.
//  Return value  : Return SUCCESS if setting passed,
//					otherwise return FAILURE.
//**********************************************************
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

//**********************************************************
//  Function name : Room::print
//  Description   : Prints offices' features.
//  Paramaters    : None.
//  Return value  : None.
//**********************************************************
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

//**********************************************************
//  Function name : Office::findClassToAddTeacher
//  Description   : Find the suitable class for new teacher.
//  Paramaters    : teacher - reference pointer to teachers
//  Return value  : Return vector<Class>::iterator that
//					the teacher should be put into.
//**********************************************************
vector<Class>::iterator Office::findClassToAddTeacher(const Teacher& teacher)
{
    if (classes_.empty()) {
        return classes_.end();
    }

	vector<Class>::iterator begin = classes_.begin();

    double maxRatio = begin->getCurrentRatio();
    vector<Class>::iterator argMaxRatio = begin;

    size_t minTeachers = begin->getTeachersNum();
    vector<Class>::iterator argMinTeachers = begin;

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

//**********************************************************
//  Function name : Office::findClassByAge
//  Description   : Find class of age.
//  Paramaters    : age - class age
//  Return value  : Return vector<Class>::iterator of the
//					class of the given age. If not found,
//					return end iterator.
//**********************************************************
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
