#include <iostream>
#include  "headers/display.h"

using namespace std;

int main(int argc, char *argv[]) {
    string dataFileName;
    if (argc == 1) {
        cout << "Create a new file <data.txt> if one does not already exist.\n";
        dataFileName = "data.txt";
    } else if (argc == 2) {
        cout << "Create a new file <" << argv[1] << ">";
        dataFileName = argv[1];
    } else { // argc > 2
        cout << "Wrong option - please choose only one .txt file";
    }

    StudentListManager *stu = new StudentListManager(dataFileName);
    Display display;
    display.mainView(*stu);
    delete(stu);
    return 0;
}