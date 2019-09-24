#include "../headers/student.h"
#include "../headers/utils.h"

Student::Student(string name, string age, string id, string department, string tel)
    : Person(name, age), id(id), department(department), tel(tel) {};

Student::Student(const Student& copy)
    : Person(copy.name, copy.age), id(copy.id), department(copy.department), tel(copy.tel) {};

Student::Student(const string &line):Person(line) {
    vector<string> strSet = split_str(line, ' ');
    id = strSet[2];
    department = strSet[3];
    tel = strSet[4];
}

string Student::getId() {
    return this->id;
}

string Student::getDepartment() {
    return this->department;
}

string Student::getTel() {
    return this->tel;
}

ostream& operator<<(ostream& os, const Student& student)
{
    os << student.name << " " << student.age << " " <<  student.id << " " << student.department << " " << student.tel << endl;
    return os;
}