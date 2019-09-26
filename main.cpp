
#include <iostream>
#include "headers/student_list_manager.h"
#include "headers/search.h"

using namespace std;

void printStudentList(vector<Student> list){
    cout << "LIST" << endl;
    cout << "    ID     |       NAME      |  AGE  |      DEPARTMENT      |       TEL      |" << endl;
    for (Student student: list) {
        cout << setw(10) << student.getId() << " | " << setw(15) << student.getName() << " |  " << setw(4)
             << student.getAge()
             << " | " << setw(20) << student.getDepartment() << " | " << setw(14) << student.getTel() << " | "
             << endl;
    }
}
int main(int argc, char *argv[]) {
    StudentListManager *stu = new StudentListManager("data.txt");

    while (true) {
        string selection;
        cout
                << "1. Add Student\n2. Edit Student\n3. Show All\n4. Search Student\n5. Kick Student\n0. Exit\n\nEnter number : ";
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

            Student student = stu->searching(id, Id).at(0);
            cout << "Enter new Name : " << student.getName() << " -> ";
            cin >> name;
            cout << "Enter new Department : " << student.getDepartment() << " -> ";
            cin >> dept;
            cout << "Enter new Telephone : " << student.getTel() << " -> ";
            cin >> tel;
            stu->modifyStudentInfo(id, name, dept, tel);
        } else if (selection == "3") {
            auto list = stu->getStudentList();
            cout << endl << "TOTAL MEMBER: " << list.size() << endl;
            if (list.size() < 5) {
                printStudentList(list);
            }
            else{
                int pageCount = list.size()/5, lastPageIndexes = list.size()%5;
                for(int i=0;i<pageCount;i++){
                    int input;
                    printStudentList(vector<Student>(list.begin() + i*5, list.begin() + i*5+5));
                    while(true){
                        cout << "1. Next Page\n2. Break\n\nEnter number : ";
                        cin >> input;
                        if(input == 1){
                            break;
                        } else if(input == 2){
                            break;
                        } else {
                            cout << "Wrong input. Try again.\n";
                        }
                    }
                }
                printStudentList(vector<Student>(list.begin() + pageCount*5, list.begin() + list.size()));
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