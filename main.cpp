
#include <iostream>
#include "headers/student_list_manager.h"
using namespace std;
int main(int argc, char * argv[]) {
    StudentListManager *stu = new StudentListManager("data.txt");

    stu->insert(*(new Student("AnJisu", "22", "1234517890", "Computer Engineer", "01037937352")));
    stu->insert(*(new Student("KimJisu", "22", "1234537890", "Computer Engineer", "01037937352")));
    stu->insert(*(new Student("JangWonbeom", "21", "1234567890", "Computer Engineer", "01037937352")));

    cout << *stu;

    return 0;
}

