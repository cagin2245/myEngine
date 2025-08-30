cmake_minimum_required(VERSION 3.15)

add_executable(sandbox main.cpp)
target_link_libraries(sandbox PRIVATE engine SDL2::SDL2)
