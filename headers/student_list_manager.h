#ifndef __STUDENT_LIST_MANAGER_H__
#define __STUDENT_LIST_MANAGER_H__

#include <fstream>

#include "student.h"
#include "search.h"
#include "deletion.h"
#include "insertion.h"

int studentCompareByName(const void *, const void *);

class StudentListManager: public Search, public Insertion, public Deletion {
    vector<Student> studentList;
    ifstream fd;
    string fileName;

public:
    StudentListManager(string fileName);

    vector<Student> getStudentList();
    vector<Student> searching(string str, SearchMenu menu);

    void insert(Student &student);

    void deleting(string id);

    friend ostream& operator<<(ostream& os, const StudentListManager& student);

private:
    vector<Student> searchByName(string str);
    vector<Student> searchById(string id_t);
    vector<Student> searchByDepart(string depart);
    vector<Student> searchByAge(string Age);

    bool chkRedundancy(string id);

    void fileOpen();
    void fileWrite();

    void setStudentList();
};

#endif