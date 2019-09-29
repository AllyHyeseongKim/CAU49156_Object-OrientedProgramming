#include <iostream>
#include  "headers/display.h"

using namespace std;

int main(int argc, char *argv[]) {
    StudentListManager *stu = new StudentListManager("data.txt");
    Display display;
    display.mainView(*stu);
    delete(stu);
    return 0;
}