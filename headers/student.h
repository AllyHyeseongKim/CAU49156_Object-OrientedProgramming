#ifndef __STUDENT_H__
#define __STUDENT_H__

#include <string>
#include "person.h"
using namespace std;

class Student: public Person {
    string id;
    string department;
    string tel;
public:
    Student(string name, string age, string id, string department, string tel);
    Student(const Student& copy);
    Student(const string &line);

    string getId() const;
    string getDepartment() const;
    string getTel() const;

    void modifyInfo(string name, string department, string tel);

    friend ostream& operator<<(ostream& os, const Student& student);
    friend bool operator<( const Person& person1,  const Person& person2);
    friend bool operator==(const Student& student1,  const Person& student2);
};

#endif