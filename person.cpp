#include "person.h"

Person::Person(string name, string age) {
    this->name = name;
    this-> age = age;
}

string Person::getAge() {
    return this->age;
};

string Person::getName() {
    return this->name;
}

ostream& operator<<(ostream& os, Person& person)
{
    os << "name: " << person.getName() << " age: " << person.getAge() << endl;
    return os;
}