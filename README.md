# OOPS (Object-Oriented Programming with SOLID)
### Project1 (Problem2)

Projects for Object-Oriented Programming

#### 설계와 달라지점  

person name, age protected로 변경

int menu --> int 대신 enum으로 SearchMenu로 재정의  
deletion class 에서 delete --> deleteStudent로 바꿈 (delete는 예약어라 사용못함)  
student list manager에 file name 변수 추가  
student list manager에서 getStudentList return type 변경  
insert 성공여부를 bool 로 표현  
fileOpen --> file read로 바꿈  

#### 의문점
getStudentList로 List를 받아버리면 수정 가능할텐데?

#### complie
g++ -std=c++11 main.cpp src/person.cpp src/student.cpp src/student_list_manager.cpp src/utils.cpp -o main
