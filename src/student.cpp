#include "../headers/student.h"
#include "../headers/utils.h"

Student::Student(string name, string age, string id, string department, string tel)
    : Person(name, age), id(id), department(department), tel(tel) {};

Student::Student(const Student& copy)
    : Person(copy.name, copy.age), id(copy.id), department(copy.department), tel(copy.tel) {};

Student::Student(const string &line):Person(line) {
    vector<string> strSet = split_str(line, '|');
    id = strSet[2];
    department = strSet[3];
    tel = strSet[4];
}

string Student::getId() const {
    return this->id;
}

string Student::getDepartment() const {
    return this->department;
}

string Student::getTel() const {
    return this->tel;
}


void Student::modifyInfo(string name, string department, string tel) {
    this->name = name;
    this->department = department;
    this->tel = tel;
}

ostream& operator<<(ostream& os, const Student& student)
{
    os << student.name << "|" << student.age << "|" <<  student.id << "|" << student.department << "|" << student.tel << endl;
    return os;
}

bool operator<(const Student& student1,  const Person& student2) {
    return student1.getName() < student1.getName();
}

bool operator==(const Student& student1,  const Student& student2) {
    return student1.getId() == student2.getId();
}