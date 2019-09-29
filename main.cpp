#include <iostream>
#include  "headers/display.h"

using namespace std;

int main(int argc, char *argv[]) {
    string dataFileName;
    if (argc != 1){
        dataFileName = argv[1];
    }
    else {
        cout << "Create a new file <data.txt>\n";
        dataFileName = "data.txt";
    }

    StudentListManager *stu = new StudentListManager(dataFileName);
    Display display;
    display.mainView(*stu);
    delete(stu);
    return 0;
}