#ifndef __PERSON_H__
#define __PERSON_H__

#include <iostream>
#include <string>
using namespace std;

class Person {
    string name;
    string age;
    
public:
    Person(string name, string age);

    string getName();
    string getAge();

    friend ostream& operator<<(ostream& os, Person& person);
};

#endif