#ifndef __MODIFICATION_H__
#define __MODIFICATION_H__

#include "student.h"

/* 
* Marker virtual class that it support modify function. 
* Implement detail on extended class.
*/
class Modification {
    // modify student information
    virtual bool modifyStudentInfo(string id, string name, string department, string tel) = 0;
};

#endif