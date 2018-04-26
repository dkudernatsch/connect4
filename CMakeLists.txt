cmake_minimum_required(VERSION 3.9)
project(connect4)
set(CMAKE_CXX_STANDARD 17)


add_executable(connect4
        src/connect4_function.h
        src/GameBoard.cpp src/main.cpp src/HumanPlayer.cpp src/ComputerPlayer.cpp)

###################################################################
add_subdirectory(googletest/googletest)
include_directories(${gtest_include_dir})


add_executable(tests
        src/test.cpp
        src/connect4_function.h
        src/GameBoard.cpp
        src/ComputerPlayer.cpp
        src/HumanPlayer.cpp)

set_target_properties(tests PROPERTIES COMPILE_FLAGS -DTESTS)

target_link_libraries(tests gtest)
add_test(tests tests)