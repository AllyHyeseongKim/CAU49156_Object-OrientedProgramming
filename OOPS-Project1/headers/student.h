#ifndef __STUDENT_H__
#define __STUDENT_H__

#include <string>
#include "person.h"
using namespace std;

/* 
* Class that inform that this is instance of Student.
* Student is extended by Person
* The instace of this has name, age, id, department, telephone
*/
class Student: public Person {
    string id;
    string department;
    string tel;
public:
    // constructor
    Student(string name, string age, string id, string department, string tel);

    // constructor for deep copy
    Student(const Student& copy);

    /* 
    * constructor for fileIO
    * string format : name|age|id|department|telephone
    */
    Student(const string &line);

    string getId() const;
    string getDepartment() const;
    string getTel() const;

    // modify student information
    void modifyInfo(string name, string department, string tel);

    /* 
    * operation overloading for print person information
    * string format : name|age|id|department|telephone
    */
    friend ostream& operator<<(ostream& os, const Student& student);

    /* 
    * operation overloading for compare.
    * compare name in dictionary order.
    */
    friend bool operator<(const Person& person1, const Person& person2);
    // oparation overloading for compare.
    friend bool operator==(const Student& student1, const Person& student2);
};

#endif