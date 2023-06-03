cmake_minimum_required(VERSION 3.21)
project(TapeSorter)

set(CMAKE_CXX_STANDARD 20)

add_executable(TapeSorter
        src/TapeSorter_main.cpp
        include/ITape.h
        include/Tape.h src/Tape.cpp
        include/TapeSorter.h src/TapeSorter.cpp
)

add_executable(TapeMapper
        src/TapeMapper_main.cpp
        include/ITape.h
        include/Tape.h src/Tape.cpp
        include/TapeMapping.h src/TapeMapping.cpp
)

add_subdirectory(tests)
