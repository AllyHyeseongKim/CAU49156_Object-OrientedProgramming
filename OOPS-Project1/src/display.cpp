//
// Created by herojeff on 2019-09-27.
//

#include "../headers/display.h"
#include <iostream>
using namespace std;

void Display::printStudentList(vector<Student> list){
    cout << "\nLIST" << endl;
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
    string input = "1";
    int i = -1;
    while(true){
        if(input == "1") {
            if((i+1)*5 >= list.size()) {
                cout << "- End of Page - " << "\n\n";
            }
            else {
                i++;
                if(list.size() < i*5+5){
                    printStudentList(vector<Student>(list.begin() + i*5, list.end()));
                }
                else{
                    printStudentList(vector<Student>(list.begin() + i*5, list.begin() + i*5+5));
                }
            }
        } else if(input == "2") {
            if(i == 0) {
                cout << "- Front of Page - " << "\n\n";
            } else {
                i--;
                printStudentList(vector<Student>(list.begin() + i*5, list.begin() + i*5+5));
            }
        } else if(input == "3") {
            break;
        } else {
            cout << "Wrong input. Try again.\n\n";
        }
        cout << "1. Next Page\n"
                    "2. Previous Page\n"
                    "3. Back to Menu\n"
                    "\nEnter number : ";
        cin >> input;
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
                // "6. Thanos is coming..\n"
                "0. Exit\n"
                "\nEnter Menu number : ";

        cin >> selection;
        cin.ignore();

        if (selection == "0") {
            cout << "Saved.";
            break;

        } else if (selection == "1") {
            string name, age, id, dept, tel;
            cout << "Enter Name : ";
            getline(cin, name);
            cout << "Enter Age : ";
            getline(cin, age);
            cout << "Enter ID : ";
            getline(cin, id);
            cout << "Enter Department : ";
            getline(cin, dept);
            cout << "Enter Telephone : ";
            getline(cin, tel);
            stu.insert(*(new Student(name, age, id, dept, tel)));

        } else if (selection == "2") {
            string name, age, id, dept, tel;
            cout << "Enter ID : ";
            getline(cin, id);

            vector<Student> student = stu.searching(id, Id);
            if (!student.empty()) {                
                cout << "Enter new Name : " << student[0].getName() << " -> ";
                getline(cin, name);
                cout << "Enter new Department : " << student[0].getDepartment() << " -> ";
                getline(cin, dept);
                cout << "Enter new Telephone : " << student[0].getTel() << " -> ";
                getline(cin, tel);
                stu.modifyStudentInfo(id, name, dept, tel);
            }

        } else if (selection == "3") {
            vector<Student> list = stu.getStudentList();
            cout << endl << "TOTAL MEMBER: " << list.size();
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
                    "4. Department\n"
                    "5. Quit\n";
            while (true) {
                cout << "Enter Mode : ";
                cin >> mode;
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
                } else if (mode == "5") {
                    break;
                } else {
                    cout << "Wrong input. Try again.\n";
                    continue;
                }
                cin.ignore();
                getline(cin, input, '\n');
                result = stu.searching(input, menu);

                cout << input;

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
            if(stu.deleting(input)) {
                cout << "Goodbye, student." << "\n";
            } else {
                cout << "Wrong input. Try again.\n";
            }

        } else if (selection == "thanos") {
            stu.thanosFingerSnap();                    
            cout << setw(50) << "I am inevitable." << endl;

            cout << R"(                                                                                                     
                                            .''.                                                    
                                  .',,'    .,,;:.     ..''.                                         
                                  ',,;:.  .,,,;:'    .',,;'                                         
                                 .,,,;c, .,,,;;:'   .',,,;.                                         
                                 ';,;:c,..;,;;::.   .,;;,,.                                         
                            .,;,.',,;:c' .,,,;:;.  .',;;,'.                                         
                           .,;:c;'.,:::..',,;;:,.  .'';;,.                                          
                           ,;;:c;'.,:::'.,',;;;,. ..,,;,'.                                          
                          .,,;cc,'.';:c'.;,';;:;..''',;,'.                                          
                          .,,;c:,'.';:c,';,',,:;..,'.,;,'.                                          
                          .'';cc;;'.,:c:;,''',:;..,'',;;'.                                          
                          ...,cc;,'..:lc;'',;;::'';,';:;,.          .',,'.                          
                           .'.;c:'.',:::,';cc:;:;;;::::;,;.       .,;;,,,'.                         
                          .,:;,.';oxo:,''cOX0l:;;oxOKOl,';.      ':;;;,',.                          
                         .,dXNk,'xWMKl,',xWMNx:;;xKNMNd,,:'    .,::;;,','                           
                          ,xNW0;.l0Xk:'..:k0kl:::loxOxc;;:,   '::;::;,'.                            
                          .:oo:...,;'....';::::::::::::,,;;'';::;;,;;,.                             
                          .;;;'.........',;::;;::::::c:;,;:::::;''',,.                              
                          .,;;,.........',;;;::::::::c:::::c:::;,'',,.                              
                           .;;,.........'',;;:::::::::::cccc::::cl:,.                               
                           .,;,'.......'',;;;::::::::;:ccccc:::dXW0;                                
                            .;;;'.....'',,;;;:::::::::c:::c:::;l0Xk,                                
                            .';;,'''''',,;;;::::::::;:::::::;::;;'.                                 
                             .,;;,,,,;,'',;;;;:::::;;;::::;:::;.                                    
                              ';;,,'''''',:;;:::::::::;:::::;,.                                     
                              ';,....';;,;;;;:::::::c:;;;;'..                                       
                              ',,'',;::',;;;::::::ccc;',,'.                                         
                             ..',,,,''''',,:cc::::::::,',,..                                        
                            .'',;,.....'',,;:::cc:::;;;,','.                                        
                            .,;,,'...'''',;::::::::;;;;;,,,..                                       
                            .;:;,........',;,;:::;;;;:;;,,,'.                                       
                            .;;;,'... ...',,',::::::;;;;,,,'..                                      
                            .;;;,,.......';;,,;::::::;;;,,,'...                                     
                           .,:;;,'....'',;:;;;;:::::c::;'',,'..                                     
                           .;:;,,'...''',;:;;;;:::cc:::;,'',,''.                                    
                           ';:;,,'.''''',;;;;:;::::::::;,'',,,'.                                    
                          .,::;;,'''''',,;;;;::;:::::::;;,,,,,''.                                   
                          .;::;;,',,,,,,,;;:;;:;;;;::::;;,,,;;,'.                                   
                          .;:::;,,,,,,,,;;;;;;::;;;;:::;;,,,;;,,'.                                  
                          ';::;;,,;,,;;,;;;;:;::;;;;;::;;,,,;;,,'.                                  
                         .,:::;,,,,,,;;;;;:;;;;;;;;;;;::;,,,,,,''.                                  
                         .,:::;,,;,,,;;;;;;;;;;;;;;;;;::;;,,,,,'...                                 
                         .;::;;,;;,,,;;;;;;;;;;;:::::;;;;;,,'',,'..                                 
                         ';:;;,',,;,,,;;;;;;;;;;::;;;::::;,'''''..                                  
                         .';;;;;;;;;;;;;;;;;;;;;::;;:::::;,,''.                                     
                           .',,;;;;;;;;;;;;;;;;;;;;;;;;;;;'..                                       
                             ...',,,,,,,,,;,,;;,,,,,,,'...                                          
                                  ..................        
                    )" << "\n";                                        

        } else {
            cout << "Wrong input. Try again.\n";
        }

        cout << "\n";
//        system("CLS");
    }
}