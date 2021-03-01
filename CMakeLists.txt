cmake_minimum_required(VERSION 3.16.3)

project(CRM_system)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wshadow -Werror -DLOCAL -DDEBUG")
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_PREFIX_PATH "C:\\Qt\\Qt5.14.0\\5.14.0\\mingw73_32\\")

include_directories(include)
#include_directories(testing)

find_package(Qt5Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)


add_executable(CRM_system src/main.cpp src/people.cpp src/storageFileSystem.cpp src/useCases.cpp)
target_link_libraries(CRM_system Qt5::Widgets)
#add_executable(CRM-file_structure_tests src/people.cpp testing/doctest_main.cpp testing/file_structure_test.cpp include/fwd.h)
