#ifndef __STUDENT_H__
#define __STUDENT_H__

#include <string>
#include "person.h"
using namespace std;

class Student: Person {
    string id;
    string department;
    string tel;
public:
    Student(string name, string age, string id, string department, string tel);

    string getId();
    string getDepartment();
    string getTel();

    friend ostream& operator<<(ostream& os, Student& student);
};

#endif