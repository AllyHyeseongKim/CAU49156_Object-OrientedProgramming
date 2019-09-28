
#include <iostream>
#include "headers/student_list_manager.h"

using namespace std;

void printStudentList(vector<Student> list){
    cout << "LIST" << endl;
    cout << "    ID     |       NAME      |  AGE  |      DEPARTMENT      |       TEL      |" << endl;
    for (Student student: list) {
        cout << setw(10) << student.getId() << " | "        // "ID" has up to 10
            << setw(15) << student.getName() << " |  "      // "Name" has up to 15
            << setw(4) << student.getAge() << " | "         // "Age" has up to 3
            << setw(20) << student.getDepartment() << " | " // "Department" has up to 20
            << setw(14) << student.getTel() << " | "        // "Tel" has up to 12
            << endl;
    }
}
int main(int argc, char *argv[]) {
    StudentListManager *stu = new StudentListManager("data.txt");

    while (true) {
        string selection;

        cout << "1. Add Student\n"
                "2. Edit Student\n"
                "3. Show All\n"
                "4. Search Student\n"
                "5. Kick Student\n"
                "0. Exit\n"
                "\nEnter Menu number : ";

        cin >> selection;

        if (selection == "0") {
            cout << "Saved.";
            break;

        } else if (selection == "1") {
            string name, age, id, dept, tel;
            cout << "Enter Name : ";
            cin >> name;
            cout << "Enter Age : ";
            cin >> age;
            cout << "Enter ID : ";
            cin >> id;
            cout << "Enter Department : ";
            cin >> dept;
            cout << "Enter Telephone : ";
            cin >> tel;

            stu->insert(*(new Student(name, age, id, dept, tel)));
        } else if (selection == "2") {
            string name, age, id, dept, tel;
            cout << "Enter ID : ";
            cin >> id;

            vector<Student> student = stu->searching(id, Id);
            if (!student.empty()) {                
                cout << "Enter new Name : " << student[0].getName() << " -> ";
                cin >> name;
                cout << "Enter new Department : " << student[0].getDepartment() << " -> ";
                cin >> dept;
                cout << "Enter new Telephone : " << student[0].getTel() << " -> ";
                cin >> tel;
                stu->modifyStudentInfo(id, name, dept, tel);
            }
        } else if (selection == "3") {
            vector<Student> list = stu->getStudentList();
            cout << endl << "TOTAL MEMBER: " << list.size() << endl;
            if (list.size() < 5) {
                printStudentList(list);
            }
            else{
                // start from 0 page
                int input = 1, i = -1;
                while(true){
                    if(input == 1) {
                        if((i+1)*5 >= list.size()) {
                            cout << "- End of Page - " << "\n\n";
                        }
                        else {
                            i++;
                            printStudentList(vector<Student>(list.begin() + i*5, list.begin() + i*5+5));
                        }
                    } else if(input == 2) {
                        if(i == 0) {
                            cout << "- Front of Page - " << "\n\n";
                        } else {
                            i--;
                            printStudentList(vector<Student>(list.begin() + i*5, list.begin() + i*5+5));
                        }
                    } else { // input == 3
                        break;
                    }
                    while(true){
                        cout << "1. Next Page\n"
                                "2. Previous Page\n"
                                "3. Stop\n"
                                "\nEnter number : ";
                        cin >> input;
                        if(input == 1 || input == 2 || input == 3){
                            break;
                        } else {
                            cout << "Wrong input. Try again.\n";
                        }
                    }
                }
            }
        } else if (selection == "4") {
            string mode, input;
            vector<Student> k;
            cout << "Search for...?\n1. ID\n2. Name\n3. Age\n4. Department\n";
            cin >> input;
            while (true) {
                //todo : ViewPager
                if (input == "1") {
                    k = stu->searching(input, Id);
                } else if (input == "2") {
                    k = stu->searching(input, Name);
                } else if (input == "3") {
                    k = stu->searching(input, Age);
                } else if (input == "4") {
                    k = stu->searching(input, Department);
                } else {
                    cout << "Wrong input. Try again.\n";
                    continue;
                }
                break;
            }

        } else if (selection == "5") {
            string input;
            cout << "Enter Id : ";
            cin >> input;
            stu->deleting(input);
            cout << "Goodbye, student.";
        } else if (selection == "thanos") {
            stu->thanosFingerSnap();
            //todo : ascii art
            cout << "I'm inevitable." << endl;
        } else {
            cout << "Wrong input. Try again.\n";
        }
        cout << "\n";
//        system("CLS");
    }

    return 0;
}