cmake_minimum_required(VERSION 3.15)
project(Simple2DEngine LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)



# SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} external include)




# Derlenecek kaynaklar
set(SOURCES
    src/main.cpp
    src/glad.c
    src/Renderer.cpp
    src/Shader.cpp
    src/Window.cpp
    src/Texture.cpp
    src/Sprite.cpp
    src/Game.cpp
    src/Collision.cpp
)

add_executable(engine ${SOURCES})

target_link_libraries(engine PRIVATE SDL2::SDL2)
file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})