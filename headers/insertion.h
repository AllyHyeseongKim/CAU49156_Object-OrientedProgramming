#ifndef __INSERTION_H__
#define __INSERTION_H__

#include "student.h"

/* 
* Marker virtual class that it support insert function. 
* Implement detail on extended class.
*/
class Insertion {
    // insert student
    virtual bool insert(Student &student) = 0;
    // chek there is no student whose id is id.
    virtual bool chkRedundancy(string id) = 0;
};

#endif