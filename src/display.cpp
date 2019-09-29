//
// Created by herojeff on 2019-09-27.
//

#include "../headers/display.h"

void Display::printStudentList(vector<Student> list){
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

void Display::viewPagerStudentList(vector<Student> list) {
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
                    "3. Back to Menu\n"
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

void Display::mainView(StudentListManager &stu) {
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
            stu.insert(*(new Student(name, age, id, dept, tel)));

        } else if (selection == "2") {
            string name, age, id, dept, tel;
            cout << "Enter ID : ";
            cin >> id;

            vector<Student> student = stu.searching(id, Id);
            if (!student.empty()) {                
                cout << "Enter new Name : " << student[0].getName() << " -> ";
                cin >> name;
                cout << "Enter new Department : " << student[0].getDepartment() << " -> ";
                cin >> dept;
                cout << "Enter new Telephone : " << student[0].getTel() << " -> ";
                cin >> tel;
                stu.modifyStudentInfo(id, name, dept, tel);
            }

        } else if (selection == "3") {
            vector<Student> list = stu.getStudentList();
            cout << endl << "TOTAL MEMBER: " << list.size() << endl;
            if (list.size() < 5) {
                printStudentList(list);
            }
            else{
                viewPagerStudentList(list);
            }

        } else if (selection == "4") {
            string mode, input;
            SearchMenu menu;
            vector<Student> result;
            cout << "Search for...?\n"
                    "1. ID\n"
                    "2. Name\n"
                    "3. Age\n"
                    "4. Department\n";
            cout << "Enter Mode : ";
            cin >> mode;
            while (true) {
                if (mode == "1") {
                    cout << "Enter ID : ";
                    menu = Id;
                } else if (mode == "2") {
                    cout << "Enter Name : ";
                    menu = Name;
                } else if (mode == "3") {
                    cout << "Enter Age : ";
                    menu = Age;
                } else if (mode == "4") {
                    cout << "Enter Department : ";
                    menu = Department;
                } else {
                    cout << "Wrong input. Try again.\n";
                    continue;
                }
                cin >> input;
                result = stu.searching(input, menu);

                if(result.size() > 5) {
                    viewPagerStudentList(stu.searching(input, menu));
                } else {
                    printStudentList(result);
                }
                break;
            }

        } else if (selection == "5") {
            string input;
            cout << "Enter Id : ";
            cin >> input;
            stu.deleting(input);
            cout << "Goodbye, student.";

        } else if (selection == "thanos") {
            stu.thanosFingerSnap();
            //todo : ascii art
            cout << "I'm inevitable." << endl;

        } else {
            cout << "Wrong input. Try again.\n";
        }

        cout << "\n";
//        system("CLS");
    }
}
