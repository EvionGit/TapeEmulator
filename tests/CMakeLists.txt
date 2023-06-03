cmake_minimum_required(VERSION 3.21)
project(TapeSorterTests)

set(CMAKE_CXX_STANDARD 20)

add_executable(TapeSorterTests
        sorter_unit_tests.cpp
        ../include/ITape.h
        ../include/Tape.h ../src/Tape.cpp
        ../include/TapeSorter.h ../src/TapeSorter.cpp
        ../include/TapeMapping.h ../src/TapeMapping.cpp
)


