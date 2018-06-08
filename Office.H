#ifndef _OFFICE_H_
#define _OFFICE_H_

#include <string>
#include <vector>

#include "Room.H"
#include "defs.H"
#include "Class.H"

using std::string;
using std::vector;

class Office : public Room {
public:
	Office();

	Result addClass(unsigned int area, double maxRatio,
		unsigned int ageClass,
		unsigned int maxChildren);

	Result addChild(const Child& child);
	Result addTeacher(const Teacher& teacher);

	Result removeChild(const string& name);
	Result removeTeacher(const string& name);
	Result removeClass(size_t age);

	Result setSick(const string& name);

	void print();


private:

	bool isBusy_;
	string sickName_;
	vector<Class> classes_;

	Class* getClass(size_t age);
	Child* Office::getChild(const string& name);
};

#endif
