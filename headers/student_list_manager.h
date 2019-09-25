#ifndef __STUDENT_LIST_MANAGER_H__
#define __STUDENT_LIST_MANAGER_H__

#include <fstream>
#include <iomanip>

#include "student.h"
#include "search.h"
#include "deletion.h"
#include "insertion.h"
#include "thanos.h"

class StudentListManager: public Search, public Insertion, public Deletion, public Thanos {
    vector<Student> studentList;
    ifstream fd;
    string fileName;

public:
    StudentListManager(string fileName);

    vector<Student> getStudentList();
    vector<Student> searching(string str, SearchMenu menu);

    bool insert(Student &student);

    void deleting(string id);

    void thanosFingerSnap();

    bool modifyStudentInfo(string id, string name, string department, string tel);

    friend ostream& operator<<(ostream& os, const StudentListManager& student);

private:
    vector<Student> searchByName(string str);
    vector<Student> searchById(string id_t);
    vector<Student> searchByDepart(string depart);
    vector<Student> searchByAge(string Age);

    bool chkRedundancy(string id);
    bool chkWorngInfoForm(string name, string age, string id, string department, string tel);

    void fileRead();
    void fileWrite();

    void setStudentList();
};

#endif