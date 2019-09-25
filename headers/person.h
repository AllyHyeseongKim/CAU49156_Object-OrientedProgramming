#ifndef __PERSON_H__
#define __PERSON_H__

#include <iostream>
#include <string>
using namespace std;

class Person {
protected:
    string name;
    string age;
    
public:
    Person(string name, string age);
    Person(const Person& copy);
    Person(const string &line);

    string getName();
    string getAge();

    friend ostream& operator<<(ostream& os, const Person& person);
    friend bool operator<( const Person& person1,  const Person& person2);
};

#endif