cmake_minimum_required(VERSION 3.0)
project(server VERSION 1.0)

add_subdirectory(VL53L0X)

add_executable(server
        main.cpp
        Server.cpp Servo.cpp)
target_compile_options(server PRIVATE -Wall -Wextra -pedantic -Werror)
target_link_libraries(server VL53L0X)
install(TARGETS server)
