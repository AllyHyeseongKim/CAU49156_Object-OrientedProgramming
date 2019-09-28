#include "../headers/student_list_manager.h"

StudentListManager::StudentListManager(string fileName) {
        this->fileName = fileName;
        StudentListManager::fileRead();
}

vector<Student> StudentListManager::getStudentList() {
    return this->studentList;
}

vector<Student> StudentListManager::searching(string str, SearchMenu menu) {
    switch (menu) {
    case Name:  
        return StudentListManager::searchByName(str);
    case Id:
        return StudentListManager::searchById(str);
    case Department:
        return StudentListManager::searchByDepart(str);
    case Age:
        return StudentListManager::searchByAge(str);
    default:
        throw out_of_range("Menu index를 초과하셨습니다.");
    }
}

bool StudentListManager::insert(Student &student) {
    if(!StudentListManager::chkCorrectInfoForm(student.getName(), student.getAge(), student.getId(), 
    student.getDepartment(), student.getTel())) return false;

    studentList.insert(upper_bound(studentList.begin(), studentList.end(), student), student);
    StudentListManager::fileWrite();

    return true;
}

void StudentListManager::deleting(string id) {
    vector<Student>::iterator student = find_if(studentList.begin(), studentList.end(), 
    [&id](Student& student) {return student.getId() == id;});

    studentList.erase(student);
    StudentListManager::fileWrite();
}

void StudentListManager::thanosFingerSnap() {
    int numDelete = studentList.size()/2;
    int index;
    
    srand((unsigned int)time(0));

    for(int i = 0; i < numDelete; i++) {
        index = rand() % studentList.size();
        studentList.erase(studentList.begin() + index);
    }

    StudentListManager::fileWrite();
}


bool StudentListManager::modifyStudentInfo(string id, string name, string department, string tel) {
    vector<Student>::iterator studentIter = find_if(studentList.begin(), studentList.end(), 
    [&id](Student& student) {return student.getId() == id;});

    if (!StudentListManager::chkCorrectInfoForm(name, "11", "0000000000", department, tel)) return false;

    if (studentIter == studentList.end())
        return false;
    studentIter->modifyInfo(name, department, tel);
    
    StudentListManager::fileWrite();
    return true;
}

vector<Student> StudentListManager::searchByName(string str) {
    vector<Student> result;
    vector<Student>::iterator studentIter = find_if(studentList.begin(), studentList.end(), 
        [&str](Student& student) {return str == student.getName();});;

    for (; studentIter != studentList.end(); studentIter++)
        result.push_back(*studentIter);
    
    return result;
}

vector<Student> StudentListManager::searchById(string str) {
    vector<Student> result;
    vector<Student>::iterator studentIter = find_if(studentList.begin(), studentList.end(), 
        [&str](Student& student) {return str == student.getId();});;

    for (; studentIter != studentList.end(); studentIter++)
        result.push_back(*studentIter);
    
    return result;
}

vector<Student> StudentListManager::searchByDepart(string str) {
    vector<Student> result;
    vector<Student>::iterator studentIter = find_if(studentList.begin(), studentList.end(), 
        [&str](Student& student) {return str == student.getDepartment();});;

    for (; studentIter != studentList.end(); studentIter++)
        result.push_back(*studentIter);
    
    return result;
}

vector<Student> StudentListManager::searchByAge(string str) {
    vector<Student> result;
    vector<Student>::iterator studentIter = find_if(studentList.begin(), studentList.end(), 
        [&str](Student& student) {return str == student.getAge();});;

    for (; studentIter != studentList.end(); studentIter++)
        result.push_back(*studentIter);
    
    return result;
}

bool StudentListManager::chkRedundancy(string id) {
    vector<Student>student = StudentListManager::searchById(id);

    return student.empty();
}


bool StudentListManager::chkCorrectInfoForm(string name, string age, string id, string department, string tel) {
    regex onlyNumber("^[0-9]+$");
    if (!StudentListManager::chkRedundancy(id)) { 
        cout << "Error : Already inserted" << endl;
        return false;
    };
    if (name.length() > 15) {
        cout << "Error: Wrong Name format" << endl;
        return false;
    }
    if (id.length() != 10 || !regex_match(id, onlyNumber)) {
        cout << "Error: Wrong ID format" << endl;
        return false;
    }
    if (age.length() > 3 || !regex_match(id, onlyNumber)) {
        cout << "Error: Wrong age format" << endl;
        return false;
    }
    if (department.length() > 20) {
        cout << "Error: Wrong department fomat" << endl;
        return false;
    }
    if (tel.length() > 12 || !regex_match(id, onlyNumber)) {
        cout << "Error: Wrong telephone number format" << endl;
        return false;
    }
    return true;
}

void StudentListManager::fileRead() {
    fd.open(fileName, ios::in);
    if(!fd.is_open()) {
        cout << "- <" << fileName << "> doesn't exist. Make a new file which name is <" << fileName << ">." << "\n\n";
    }
    StudentListManager::setStudentList();
    fd.close();
}

void StudentListManager::fileWrite() {
    ofstream fd;
    fd.open(fileName, ios::out);
    for (Student stu: studentList)
        fd << stu;
    fd.close();
}

void StudentListManager::setStudentList() {
    string line;
    Student *tempStudent;

    if (fd.is_open()) {
        while (getline(fd, line)) {
            tempStudent = new Student(line);
            studentList.push_back(*tempStudent);
            delete(tempStudent);
        }
    }
}

ostream& operator<<(ostream& os, const StudentListManager& student)
{
    cout << endl << "STUDENT LIST MANAGER" << endl;
    cout << "TOTAL MEMBER: " << student.studentList.size() << endl << endl;
    cout << "LIST" << endl; 
    cout << "    ID     |       NAME      |  AGE  |      DEPARTMENT      |       TEL      |" << endl;
    for (Student stu: student.studentList) {
        os << setw(10) << stu.getId() <<" | " << setw(15) << stu.getName() <<" |  " << setw(4) << stu.getAge()
         << " | " <<setw(20) << stu.getDepartment() << " | " << setw(14) << stu.getTel() << " | " << endl;
    }
    return os;
}