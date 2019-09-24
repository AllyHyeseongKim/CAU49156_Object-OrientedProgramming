#ifndef __INSERTION_H__
#define __INSERTION_H__

#include "student.h"

class Insertion {
    virtual void insert(Student &student) = 0;
    virtual bool chkRedundancy(string id) = 0;
};

#endif