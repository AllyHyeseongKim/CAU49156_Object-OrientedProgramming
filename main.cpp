 
#include <iostream>
#include "headers/student_list_manager.h"
using namespace std;
int main(int argc, char * argv[]) {
    StudentListManager *stu = new StudentListManager("data.txt");

    stu->insert(*(new Student("Z111111111", "11", "1s11111111", "adsf", "adsf")));

    stu->thanosFingerSnap();

    cout << *stu;

    return 0;
}

