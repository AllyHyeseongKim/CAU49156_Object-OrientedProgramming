cmake_minimum_required(VERSION 3.14)
project(TestCMake)

set(CMAKE_CXX_STANDARD 11)

add_executable(TestCMake main.cpp src/utils.cpp src/student_list_manager.cpp src/student.cpp src/person.cpp src/display.cpp)