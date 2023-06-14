set(CMAKE_CXX_STANDARD 17)

cmake_minimum_required(VERSION 3.15)
project(client VERSION 1.0)





#include_directories(/usr/include/python3.8)

#include_directories(${PYTHON3_INCLUDE_DIRS} )
find_package(Python3 COMPONENTS Interpreter Development NumPy REQUIRED)

find_package(PythonLibs 3 REQUIRED)
include_directories(${PYTHON3_INCLUDE_DIRS} ${NumPy_INCLUDE_DIRS})

#add_library(python3.8 INTERFACE)

add_executable(client
        main.cpp
        Client.cpp)

target_compile_options(client PRIVATE -Wall -Wextra -pedantic)
# link python and numpy
target_link_libraries(client
    PRIVATE
        ${PYTHON_LIBRARIES}
        Python3::NumPy
)

install(TARGETS client)