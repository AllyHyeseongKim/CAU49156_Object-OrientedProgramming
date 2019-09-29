#include "../headers/student.h"
#include "../headers/utils.h"

#include <algorithm>

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

bool operator<(const Student& student1, const Student& student2) {
    string lowStudentName1 = student1.getName();
    string lowStudentName2 = student2.getName();
    transform(lowStudentName1.begin(), lowStudentName1.end(), 
            lowStudentName1.begin(), ::tolower);
    transform(lowStudentName2.begin(), lowStudentName2.end(),
            lowStudentName2.begin(), ::tolower);
    return lowStudentName1 < lowStudentName2;
}

bool operator==(const Student& student1, const Student& student2) {
    return student1.getId() == student2.getId();
}