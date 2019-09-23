#ifndef __SEARCHING_H__
#define __SERACHING_H__

#include <vector>
#include <string>
#include "student.h"

typedef enum {Name, Id, Department, Age} SearchMenu;

class Search {
protected:
    virtual vector<Student> searching(string str, SearchMenu menu) = 0;
    virtual vector<Student> searchByName(string name) = 0;
    virtual vector<Student> searchById(string id) = 0;
    virtual vector<Student> searchByDepart(string depart) = 0;
    virtual vector<Student> searchByAge(string age) = 0;
};

#endif