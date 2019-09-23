#include "student.h"

Student::Student(string name, string age, string id, string department, string tel):Person(name, age) {
    this->id = id;
    this->department = department;
    this->tel = tel;
}

string Student::getId() {
    return this->id;
}

string Student::getDepartment() {
    return this->getDepartment;
}

string Student::getTel() {
    return this->tel;
}

ostream& operator<<(ostream& os, Student& student)
{
    os <<"id: " << student.getId() << " name: " << student.getName() << " age: " << student.getAge() 
    << " department: " << student.getDepartment << "telephone number: " << student.getTel() << endl;
    return os;
}