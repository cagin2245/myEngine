cmake_minimum_required(VERSION 3.15)
project(Simple2DEngine LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# SDL2
find_package(SDL2 REQUIRED)


# Debug flag
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DENGINE_DEV_MODE)
endif()

# Engine sources
set(ENGINE_SOURCES
    external/glad/glad.c
    src/Renderer.cpp
    src/Shader.cpp
    src/Window.cpp
    src/Texture.cpp
    src/Sprite.cpp
    src/Game.cpp
    src/Collision.cpp
    src/ResourceManager.cpp
    src/Core/Profiler.cpp
    src/Core/Logger.cpp
    src/Core/ProfilerOverlay.cpp
)




# Engine executable
add_executable(engine ${ENGINE_SOURCES} src/main.cpp)
target_include_directories(engine PRIVATE
    ${SDL2_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/external
    ${CMAKE_SOURCE_DIR}/external/glad
    ${CMAKE_SOURCE_DIR}/include/Engine
    ${CMAKE_SOURCE_DIR}/include/Engine/Core
)
target_link_libraries(engine PRIVATE SDL2::SDL2)

# Copy assets for runtime
file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})



