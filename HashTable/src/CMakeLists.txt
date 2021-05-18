cmake_minimum_required(VERSION 3.17)
project(EngRusTrans C)

set(CMAKE_C_STANDARD 11)
set(GCC_COVERAGE_COMPILE_FLAGS "-O2")

find_package(Gdi32)
#target_link_libraries(Gdi32)

#To compile with AVX2
set(GCC_COVERAGE_COMPILE_FLAGS "-msse -msse2 -msse3 -lSDL2 -mavx -mfpmath=sse -mavx2")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mavx")

add_executable(EngRusTrans main.c "LinkedList.c" "LinkedList.h" HashFuncs.c HashFuncs.h FileMaster.c FileMaster.h HashTest.c HashTest.h HashTable.c HashTable.h Unit-Test.c Unit-Test.h)
