cmake_minimum_required(VERSION 3.9)
project(connect4)
set(CMAKE_CXX_STANDARD 17)


add_executable(connect4
        src/connect4_function.h
        src/GameBoard.cpp src/main.cpp src/HumanPlayer.cpp src/ComputerPlayer.cpp)

###################################################################
include(ExternalProject)
ExternalProject_Add(googletest
        GIT_REPOSITORY    https://github.com/google/googletest.git
        GIT_TAG           master
        SOURCE_DIR        "${CMAKE_BINARY_DIR}/googletest-src"
        BINARY_DIR        "${CMAKE_BINARY_DIR}/googletest-build"
        CONFIGURE_COMMAND ""
        BUILD_COMMAND     ""
        INSTALL_COMMAND   ""
        TEST_COMMAND      ""
        )


add_executable(tests
        src/test.cpp
        src/connect4_function.h
        src/GameBoard.cpp
        src/ComputerPlayer.cpp
        src/HumanPlayer.cpp)

set_target_properties(tests PROPERTIES COMPILE_FLAGS -DTESTS)

target_link_libraries(tests gtest gtest_main)
add_test(tests tests)