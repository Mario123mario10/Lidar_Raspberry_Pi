cmake_minimum_required(VERSION 3.0)
project(client VERSION 1.0)

add_executable(client
        main.cpp
        Client.cpp)
target_compile_options(client PRIVATE -Wall -Wextra -pedantic -Werror)
install(TARGETS client)
