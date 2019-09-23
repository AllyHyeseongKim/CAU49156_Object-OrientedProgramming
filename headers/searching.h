#ifndef __SEARCHING_H__
#define __SERACHING_H__

#include <vector>
#include <string>
#include "student.h"

typedef enum {name, id, department, age} SearchMenu;

class Search {
protected:
    virtual vector<Student> searching();
    virtual vector<Student> searchByName(string name, SearchMenu menu);
    virtual vector<Student> searchById(string name);
    virtual vector<Student> searchByDepart(string name);
    virtual vector<Student> searchByAge(string name);
};

#endif