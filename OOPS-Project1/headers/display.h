#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include "student_list_manager.h"

class Display {

    public:
        void mainView(StudentListManager &stu);
    
    private:
        void printStudentList(vector<Student> list);
        void viewPagerStudentList(vector<Student> list);
};

#endif