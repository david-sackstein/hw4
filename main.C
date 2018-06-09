#include "Office.H"
#include "Class.H"
#include "Child.H"
#include "Teacher.H"

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::string;
using std::istringstream;

int stringToInt(const string s) {
    istringstream istr(s);
    int i = 0;
    istr >> i;
    return i;
}

double stringToDouble(const string s1, const string s2) {

    istringstream istr1(s1);
    istringstream istr2(s2);
    int i; //integer part
    int j; //fraction part
    double a = 0;
    istr1 >> i;
    istr2 >> j;
    a = double(i) + double(j) / 1000; //assuming fraction part is alwways 3 digits
    return a;
}

vector<string> tokenize(string line, const char* delim) {
    size_t i, j;
    vector<string> tokens;
    while (!line.empty()) {
        i = line.find_first_not_of(delim);
		if (i == std::string::npos) {
			return tokens;
		}
        j = line.find_first_of(delim, i + 1);
        tokens.push_back(line.substr(i, j - i));
        if (j > line.size() - 1)
            line = "";
        else
            line = line.substr(j + 1, line.size() - j - 1);
    }
    return tokens;
}

void ShowError(const vector<string>& tokens)
{
    cerr << "Failed -";

    for (size_t i = 0; i < tokens.size(); ++i)
    {
        cerr << " " << tokens[i];
    }

    cerr << "\n";
}

void addClass(Office& office, const vector<string>& tokens)
{
    if (tokens.size() == 5) {
        int size = stringToInt(tokens[1]);
        vector<string> decimalParts = tokenize(tokens[2], ".");
        double ratio = stringToDouble(decimalParts[0], decimalParts[1]);
        unsigned int max_num_children = stringToInt(tokens[3]);
        int children_age = stringToInt(tokens[4]);

        Result result = office.addClass(size, ratio, children_age, max_num_children);
        if (result == SUCCESS) {
            return;
        }
    }
    ShowError(tokens);
}

void removeClass(Office& office, vector<string> tokens)
{
    if (tokens.size() == 2) {
        int ageClass = stringToInt(tokens[1]);

        Result result = office.removeClass(ageClass);
        if (result == SUCCESS) {
            return;
        }
    }
    ShowError(tokens);
}

void addChild(Office& office, const vector<string>& tokens)
{
    if (tokens.size() == 4) {
        int age = stringToInt(tokens[1]);
        const string& name = tokens[2];
        const string& phoneNumber = tokens[3];

        Result result = office.addChild(Child(name, age, phoneNumber));
        if (result == SUCCESS) {
            return;
        }
    }
    ShowError(tokens);
}

void addTeacher(Office& office, const vector<string>& tokens)
{
    if (tokens.size() == 4) {
        int age = stringToInt(tokens[1]);
        const string& name = tokens[2];
        int seniority = stringToInt(tokens[3]);

        Result result = office.addTeacher(Teacher(name, age, seniority));
        if (result == SUCCESS) {
            return;
        }
    }
    ShowError(tokens);
}

void removeChild(Office& office, const vector<string>& tokens)
{
    if (tokens.size() == 2) {
        const string& name = tokens[1];

        Result result = office.removeChild(name);
        if (result == SUCCESS) {
            return;
        }
    }
    ShowError(tokens);
}

void removeTeacher(Office& office, const vector<string>& tokens)
{
    if (tokens.size() == 2) {
        const string& name = tokens[1];

        Result result = office.removeTeacher(name);
        if (result == SUCCESS) {
            return;
        }
    }
    ShowError(tokens);
}

void printKindergarten(Office& office, const vector<string>& tokens)
{
    if (tokens.size() == 1) {
        office.print();
        return;
    }
    ShowError(tokens);
}

void sickChild(Office& office, const vector<string>& tokens)
{
    if (tokens.size() == 2) {
        const string& name = tokens[1];

        Result result = office.setSick(name);
        if (result == SUCCESS) {
            return;
        }
    }
    ShowError(tokens);
}

#include <fstream>

int main()
{
    Office KG_Office; //KinderGarten Office
    const char* delims = " \t\n\r";
    vector<string> tokens;
    string line;
    unsigned int lineNumber = 1;

    std::ifstream input("input1.txt");

    while (!input.eof()) {

		getline(input, line);
        tokens = tokenize(line, delims);
		if (tokens.size() == 0) { //empty line
            continue;
        }

        if (tokens[0] == "addClass") {
            addClass(KG_Office, tokens);
        }
        else if (tokens[0] == "removeClass") {
            removeClass(KG_Office, tokens);
        }
        else if (tokens[0] == "addChild") {
            addChild(KG_Office, tokens);
        }
        else if (tokens[0] == "addTeacher") {
            addTeacher(KG_Office, tokens);
        }
        else if (tokens[0] == "removeChild") {
            removeChild(KG_Office, tokens);
        }
        else if (tokens[0] == "removeTeacher") {
            removeTeacher(KG_Office, tokens);
        }
		else if (tokens[0] == "PrintKindergarten") {
			printKindergarten(KG_Office, tokens);
        }
        else if (tokens[0] == "sickChild") {
            sickChild(KG_Office, tokens);
        }
        else {
            ShowError(tokens);
        }
        lineNumber++;
    }
    return 0;
};

int main2()
{
    Child child1("c1", 1, "0541111111");
    Child child2("c2", 1, "0542222222");
    Child child3("c3", 1, "0543333333");
    Child child4("c4", 4, "0504444444");
    Child child5("c5", 4, "0525555555");
    Child child6("c6", 10, "0546666666");
    Child child7("c7", 10, "0547777777");

    Teacher teacher1("t1", 67, 40);
    Teacher teacher2("t2", 20, 5);
    Teacher teacher3("t3", 55, 10);
    Teacher teacher4("t4", 50, 10);
    Teacher teacher5("t5", 40, 10);
    Teacher teacher6("t6", 50, 10);

    Office office;
    office.addClass(50, 1, 2, 5);
    office.addClass(50, 3, 1, 5);
    office.addClass(50, 2, 4, 5);
    office.addClass(50, 1, 10, 5);

    office.addTeacher(teacher1);
    office.addTeacher(teacher2);
    office.addTeacher(teacher3);
    office.addTeacher(teacher4);
    office.addTeacher(teacher5);
    office.addTeacher(teacher6);
    office.print();

    office.addChild(child1);
    office.addChild(child2);
    office.addChild(child4);
    office.addChild(child5);
    office.addChild(child6);
    office.print();

    office.setSick("c5");
    cout << "~~~~~~~~~~~\\\\\\\\~~~~~~~~~~~~~~~~~~~~~~\\\\\\\\~~~~~~~~~~~~~~~~~~~~~~\\\\\\\\~~~~~~~~~~~\n\n";

    Result res = office.addTeacher(teacher5); // not supposed to work
    office.print();

    cout << "~~~~~~~~~~~\\\\\\\\~~~~~~~~~~~~~~~~~~~~~~\\\\\\\\~~~~~~~~~~~~~~~~~~~~~~\\\\\\\\~~~~~~~~~~~\n\n";

    office.removeChild("c5");
    office.print();

    cout << "~~~~~~~~~~~\\\\\\\\~~~~~~~~~~~~~~~~~~~~~~\\\\\\\\~~~~~~~~~~~~~~~~~~~~~~\\\\\\\\~~~~~~~~~~~\n\n";

    res = office.addTeacher(teacher5);
    office.addChild(child3); // can i add the same child ????
    office.addTeacher(teacher6);
    office.print();

    cout << "~~~~~~~~~~~\\\\\\\\~~~~~~~~~~~~~~~~~~~~~~\\\\\\\\~~~~~~~~~~~~~~~~~~~~~~\\\\\\\\~~~~~~~~~~~\n\n";

    office.removeTeacher("t5");
    office.print();

    cout << "~~~~~~~~~~~\\\\\\\\~~~~~~~~~~~~~~~~~~~~~~\\\\\\\\~~~~~~~~~~~~~~~~~~~~~~\\\\\\\\~~~~~~~~~~~\n\n";

    office.removeClass(4);
    office.print();

	if (res == FAILURE)
		return 1;
    return 0;
}
