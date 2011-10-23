project(ProcessRecovery)
cmake_minimum_required(VERSION 2.6)
add_executable(recover main.cpp SharedMemory.cpp BaseDataSection.cpp AHTest.cpp AHTestDataSection.h) 
