#include "headers/student_list_manager.h"

int studentCompareByName(const void *first, const void *second) {
    string firstStudentName =  ((Student*)first)->getName();
    string secondStudentName =  ((Student*)second)->getName();

    return firstStudentName.compare(secondStudentName);
}

StudentListManager::StudentListManager(string fileName) {
        this->fileName = fileName;
        StudentListManager::fileOpen();
        StudentListManager::setStudentList();
}

vector<Student> StudentListManager::getStudentList() {
    return this->studentList;
}

vector<Student> StudentListManager::searching(string str, SearchMenu menu) {
    switch (menu) {
    case Name:  
        return StudentListManager::searchByName(str);
    case Id:
        return StudentListManager::searchById(str);
    case Department:
        return StudentListManager::searchByDepart(str);
    case Age:
        return StudentListManager::searchByAge(str);
    default:
        throw out_of_range("Menu index를 초과하셨습니다.");
    }
}

bool StudentListManager::insert(Student &student) {
    if (!StudentListManager::chkRedundancy(student.getId())) { 
        cout << "Error : Already inserted" << endl;
        return false;
    };
    if (student.getName().length() > 15) return false;
    if (student.getId().length() != 10) return false;
    if (student.getAge().length() > 3) return false;
    if (student.getDepartment().length() > 20) return false;
    if (student.getTel().length() > 12) return false;

    studentList.push_back(student);
    qsort(&studentList[0], studentList.size(), sizeof(Student), studentCompareByName);
    StudentListManager::fileWrite();

    return true;
}

void StudentListManager::deleting(string id) {
    vector<Student>::iterator student = find_if(studentList.begin(), studentList.end(), 
    [&id](Student& student) {return student.getId() == id;});

    studentList.erase(student);
    StudentListManager::fileWrite();
}

vector<Student> StudentListManager::searchByName(string str) {
    vector<Student> result;
    vector<Student>::iterator studentIter = find_if(studentList.begin(), studentList.end(), 
        [&str](Student& student) {return str == student.getName();});;

    for (; studentIter != studentList.end(); studentIter++)
        result.push_back(*studentIter);
    
    return result;
}

vector<Student> StudentListManager::searchById(string str) {
    vector<Student> result;
    vector<Student>::iterator studentIter = find_if(studentList.begin(), studentList.end(), 
        [&str](Student& student) {return str == student.getId();});;

    for (; studentIter != studentList.end(); studentIter++)
        result.push_back(*studentIter);
    
    return result;
}

vector<Student> StudentListManager::searchByDepart(string str) {
    vector<Student> result;
    vector<Student>::iterator studentIter = find_if(studentList.begin(), studentList.end(), 
        [&str](Student& student) {return str == student.getDepartment();});;

    for (; studentIter != studentList.end(); studentIter++)
        result.push_back(*studentIter);
    
    return result;
}

vector<Student> StudentListManager::searchByAge(string str) {
    vector<Student> result;
    vector<Student>::iterator studentIter = find_if(studentList.begin(), studentList.end(), 
        [&str](Student& student) {return str == student.getAge();});;

    for (; studentIter != studentList.end(); studentIter++)
        result.push_back(*studentIter);
    
    return result;
}

bool StudentListManager::chkRedundancy(string id) {
    vector<Student>student = StudentListManager::searchById(id);

    return student.empty();
}

void StudentListManager::fileOpen() {
    fd.open(fileName, ios::in);
}


void StudentListManager::fileWrite() {
    ofstream fd;
    fd.open(fileName, ios::out);

    for (Student stu: studentList)
        fd << stu;
    fd.close();
}

void StudentListManager::setStudentList() {
    string line;
    Student *tempStudent;

    if (fd.is_open()) {
        while (getline(fd, line)) {
            tempStudent = new Student(line);
            studentList.push_back(*tempStudent);
            delete(tempStudent);
        }
    }
    fd.close();
}

ostream& operator<<(ostream& os, const StudentListManager& student)
{
    for (Student stu: student.studentList) {
        os << stu;
    }
    return os;
}