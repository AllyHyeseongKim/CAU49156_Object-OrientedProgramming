#include "student_list_manager.h"

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

void StudentListManager::insert(Student &student) {
    if (!StudentListManager::chkRedundancy(student.getId))
        return;

    studentList.push_back(student);
    qsort(&studentList[0], studentList.size(), sizeof(Student), studentCompareByName);
}

void StudentListManager::deleting(string id) {
    vector<Student>::iterator student = find_if(studentList.begin(), studentList.begin() + studentList.size(), 
    [&id](Student& student) {return student.getId() == id;});

    studentList.erase(student);
}

vector<Student> StudentListManager::searchByName(string str) {
    vector<Student> result;
    vector<Student>::iterator studentIter = find_if(studentList.begin(), studentList.begin() + studentList.size(), 
        [&str](Student& student) {return str == student.getName();});;

    for (; studentIter != studentList.end(); studentIter++)
        result.push_back(*studentIter);
    
    return result;
}

vector<Student> StudentListManager::searchById(string str) {
    vector<Student> result;
    vector<Student>::iterator studentIter = find_if(studentList.begin(), studentList.begin() + studentList.size(), 
        [&str](Student& student) {return str == student.getId();});;

    for (; studentIter != studentList.end(); studentIter++)
        result.push_back(*studentIter);
    
    return result;
}

vector<Student> StudentListManager::searchByDepart(string str) {
    vector<Student> result;
    vector<Student>::iterator studentIter = find_if(studentList.begin(), studentList.begin() + studentList.size(), 
        [&str](Student& student) {return str == student.getDepartment();});;

    for (; studentIter != studentList.end(); studentIter++)
        result.push_back(*studentIter);
    
    return result;
}

vector<Student> StudentListManager::searchByAge(string str) {
    vector<Student> result;
    vector<Student>::iterator studentIter = find_if(studentList.begin(), studentList.begin() + studentList.size(), 
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
    fd.open(fileName, ios::binary|ios::in);
}


void StudentListManager::fileWrite() {
    ofstream fd;
    fd.open(fileName, ios::binary|ios::app|ios::out);

    for (Student stu: studentList) {
        fd.write((char*)&stu, sizeof(Student));
    }
}

void StudentListManager::setStudentList() {
    streampos fileSize;
    int numOfObject;
    Student *tempStudent;

    StudentListManager::fileOpen();

    if (fd.is_open()) {
        fileSize = fd.tellg();
        numOfObject = fileSize/sizeof(Student);
        
        for (int i = 0; i < numOfObject; i++) {
            fd.read((char*)tempStudent, sizeof(Student));
            studentList.push_back(*tempStudent);
        }
    }
    fd.close();
}