#include "headers/student.h"

Student::Student(string name, string age, string id, string department, string tel)
    : Person(name, age), id(id), department(department), tel(tel) {};

Student::Student(const Student& copy)
    : Person(copy.name, copy.age), id(copy.id), department(copy.department), tel(copy.tel) {};

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
    os <<"id: " << student.id << " name: " << student.name << " age: " << student.age 
    << " department: " << student.department << " telephone number: " << student.tel << endl;
    return os;
}