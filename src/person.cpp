#include "../headers/person.h"
#include "../headers/utils.h"

Person::Person(string name, string age): name(name), age(age){};
Person::Person(const Person& copy): name(copy.name), age(copy.age){};
Person::Person(const string &line) {
    vector<string> strSet = split_str(line, ' ');

    name = strSet[0];
    age = strSet[1];
};

string Person::getAge() {
    return this->age;
};

string Person::getName() {
    return this->name;
}

ostream& operator<<(ostream& os, const Person& person)
{
    os << person.name << " " << person.age << endl;
    return os;
}