 
#include <iostream>
#include "headers/student_list_manager.h"
using namespace std;
int main(int argc, char * argv[]) {
    StudentListManager *stu = new StudentListManager("data.txt");

    cout << stu->insert(*(new Student("Jang Wonbeom", "21", "1234567890", "Computer Science", "01037937352")));
    cout << *stu;

    stu->modifyStudentInfo("1234567890", "sdf", "sdf", "01037937352");

    cout << *stu;

    return 0;
}

