#include "../headers/person.h"
#include "../headers/utils.h"

Person::Person(string name, string age): name(name), age(age){};
Person::Person(const Person& copy): name(copy.name), age(copy.age){};
Person::Person(const string &line) {
    vector<string> strSet = split_str(line, '|');

    name = strSet[0];
    age = strSet[1];
};

string Person::getAge() const {
    return this->age;
};

string Person::getName() const {
    return this->name;
}

ostream& operator<<(ostream& os, const Person& person)
{
    os << person.name << "|" << person.age << endl;
    return os;
}


bool operator<(const Person& person1, const Person& person2) {
    string lowPersonName1 = person1.getName();
    string lowPersonName2 = person2.getName();
    transform(lowPersonName1.begin(), lowPersonName1.end(), 
            lowPersonName1.begin(), ::tolower);
    transform(lowPersonName2.begin(), lowPersonName2.end(),
            lowPersonName2.begin(), ::tolower);
    return lowPersonName1 < lowPersonName2;
}