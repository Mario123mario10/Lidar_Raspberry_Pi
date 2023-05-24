cmake_minimum_required(VERSION 3.0)
project(server VERSION 1.0)

add_executable(server
        main.cpp
        Server.cpp)
target_compile_options(server PRIVATE -Wall -Wextra -pedantic -Werror)
install(TARGETS server)
