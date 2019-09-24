
#include <iostream>
#include "headers/student_list_manager.h"
using namespace std;
int main(int argc, char * argv[]) {
    StudentListManager *stu = new StudentListManager("data.txt");

    cout << stu->searching("ad", Age).size();

    return 0;
}

