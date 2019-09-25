#ifndef __SEARCH_H__
#define __SEARCH_H__

#include <vector>
#include <string>
#include "student.h"

typedef enum {Name, Id, Department, Age} SearchMenu;

/* 
* Marker virtual class that it support deleting function. 
* Implement detail on extended class.
*/
class Search {
protected:
    virtual vector<Student> searching(string str, SearchMenu menu) = 0;
    virtual vector<Student> searchByName(string name) = 0;
    virtual vector<Student> searchById(string id) = 0;
    virtual vector<Student> searchByDepart(string depart) = 0;
    virtual vector<Student> searchByAge(string age) = 0;
};

#endif