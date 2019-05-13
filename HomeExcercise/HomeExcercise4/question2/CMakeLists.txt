cmake_minimum_required(VERSION 3.14)
project(Question2 C)

set(CMAKE_C_STANDARD 99)

add_executable(Question2 main.c tree.c checkString.c)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
        "checkString.h"
        "tree.h"
)

# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
include_directories("${PROJECT_BINARY_DIR}")