#ifndef __STUDENT_LIST_MANAGER_H__
#define __STUDENT_LIST_MANAGER_H__

#include <fstream>
#include <iomanip>
#include <algorithm>
#include <regex>

#include "student.h"
#include "search.h"
#include "deletion.h"
#include "insertion.h"
#include "modification.h"
#include "thanos.h"


/* 
* Class that inform that this is instance of StudentListManager. 
* StudentListManager support Search, Insertion, Deletion, Modification, Thanos.
*/
class StudentListManager: public Search, public Insertion, public Deletion, public Modification, public Thanos {
    /*
    * stored student information
    * The information is sorted alphabetically.
    * Search by many criteria.
    * Time consuming on search: quick sort + binary search > linear search --> use find_if
    * information is sorted alphabetically. Searched information is also sorted alphabetically using linear search.
    * To sort information alphabetically, we use lower_bound when we insert student information.
    * Time consuming on sorting: quick sort (O(n long n)) > lower_bound (O(log n))
    * 
    * For the safty, Searching function return duplicated vector of object.
    */

    ifstream fd;
    string fileName;
    vector<Student> studentList;

public:
    // Constructor
    StudentListManager(string fileName);

    vector<Student> getStudentList();
    
    /*
    * searching student by menu
    * SeachMenu(int) : Name, Id, Department,  Age
    */
    vector<Student> searching(string str, SearchMenu menu);

    // insert student
    bool insert(Student &student);

    // delete studnet by id
    bool deleting(string id);

    /* 
    * The function motivated by Avengers
    * This function remove a half of student information.
    */
    void thanosFingerSnap();

    // modify student information
    bool modifyStudentInfo(string id, string name, string department, string tel);

    // operation overloading for test output
    friend ostream& operator<<(ostream& os, const StudentListManager& student);

private:
    vector<Student> searchByName(string str);
    vector<Student> searchById(string id_t);
    vector<Student> searchByDepart(string depart);
    vector<Student> searchByAge(string Age);

    // chek there is no student whose id is id.
    bool chkRedundancy(string id);
    // check information form
    bool chkCorrectInfoForm(string name, string age, string id, string department, string tel);
    // load student informations from data file
    void fileRead();
    // write student informations from data file
    void fileWrite();
    // read student infromation and make vector<strudent>
    void setStudentList();
};

#endif