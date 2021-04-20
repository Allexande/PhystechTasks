cmake_minimum_required(VERSION 3.17)
project(EngRusTrans C)

set(CMAKE_C_STANDARD 11)

add_executable(EngRusTrans main.c "LinkedList .c" "LinkedList .h" HashFuncs.c HashFuncs.h FileMaster.c FileMaster.h HashTest.c HashTest.h)
