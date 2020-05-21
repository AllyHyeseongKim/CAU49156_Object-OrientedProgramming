#ifndef __PERSON_H__
#define __PERSON_H__

#include <iostream>
#include <string>
using namespace std;

/* 
* Class that inform that this is instance of Person. 
* The instace of this has name, age.
*/
class Person {
protected:
    string name;
    string age;
    
public:
    // constructor
    Person(string name, string age);

    // constructor for deep copy
    Person(const Person& copy);

    /* 
    * constructor for fileIO
    * string format : name|age
    */
    Person(const string &line);

    string getName() const;
    string getAge() const;

    /* 
    * operation overloading for print person information
    * string format : name|age
    */
    friend ostream& operator<<(ostream& os, const Person& person);

    /* 
    * operation overloading for compare.
    * compare name in dictionary order.
    */
    friend bool operator<(const Person& person1, const Person& person2);
};

#endif