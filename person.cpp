#include "person.h"

Person::Person(string name, string age): name(name), age(age){};
Person::Person(const Person& copy): name(copy.name), age(copy.age){};

string Person::getAge() {
    return this->age;
};

string Person::getName() {
    return this->name;
}

ostream& operator<<(ostream& os, const Person& person)
{
    os << "name: " << person.name << " age: " << person.age << endl;
    return os;
}