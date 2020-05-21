#ifndef __DELETION_H__
#define __DELETION_H__

#include <string>
using namespace std;

/* 
* Marker virtual class that it support deleting function. 
* Implement detail on extended class.
*/
class Deletion {
    // delete studnet by id
    virtual bool deleting(string id) = 0;
};

#endif