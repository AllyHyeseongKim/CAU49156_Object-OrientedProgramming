#ifndef __INSERTION_H__
#define __INSERTION_H__

#include "student.h"

class Insertion {
    virtual void insert(Student student);
    virtual bool chkRedunduncy(string id);
};

#endif