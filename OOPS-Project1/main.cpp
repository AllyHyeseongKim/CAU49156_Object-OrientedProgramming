#include <iostream>
#include  "headers/display.h"

using namespace std;

int main(int argc, char *argv[]) {
    string dataFileName;
    if (argc <= 2) {

        if (argc == 1) {
            cout << "Create a new file <data.txt> if one does not already exist.\n";
            dataFileName = "data.txt";
        } else { // argc == 2
            cout << "Create a new file <" << argv[1] << ">";
            dataFileName = argv[1];
        }

        StudentListManager *stu = new StudentListManager(dataFileName);
        Display display;
        display.mainView(*stu);
        delete(stu);

    } else { // argc > 2
        cout << "Wrong option - please choose only one .txt file";
    }

    return 0;
}