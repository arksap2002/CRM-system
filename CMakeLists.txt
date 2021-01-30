cmake_minimum_required(VERSION 3.17)
project(CRM_system)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wshadow -Werror -DLOCAL -DDEBUG")

add_executable(CRM_system main.cpp)
