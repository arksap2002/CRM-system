cmake_minimum_required(VERSION 3.16.3)

project(CRM_system)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wshadow -Werror -DLOCAL -DDEBUG")

include_directories(include)
#include_directories(testing)

add_executable(CRM_system src/main.cpp src/people.cpp src/peopleMVP.cpp)
#add_executable(CRM-file_structure_tests src/people.cpp testing/doctest_main.cpp testing/file_structure_test.cpp include/fwd.h)
