cmake_minimum_required(VERSION 3.15)
project(Simple2DEngine LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# SDL2

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)

# Prefer pkg-config for freetype to capture transitive deps (libpng, zlib, brotli, harfbuzz, etc.)
find_package(PkgConfig)
if(PkgConfig_FOUND)
    pkg_check_modules(FREETYPE_PKG REQUIRED freetype2)
    include_directories(${FREETYPE_PKG_INCLUDE_DIRS})
    link_directories(${FREETYPE_PKG_LIBRARY_DIRS})
    set(EXTRA_ENGINE_LIBS ${FREETYPE_PKG_LIBRARIES})
else()
    find_package(Freetype REQUIRED)
    if(FREETYPE_FOUND)
        include_directories(${FREETYPE_INCLUDE_DIRS})
        set(EXTRA_ENGINE_LIBS ${FREETYPE_LIBRARIES})
    else()
        message(FATAL_ERROR "Freetype not found! Install freetype and its dependencies or enable pkg-config.")
    endif()
endif()


# Debug flag
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DENGINE_DEV_MODE)
endif()

# Optional advanced logging features (timestamps, file filter, file output)
option(ENGINE_ADVANCED_LOGGING "Enable advanced logging features" OFF)
if(ENGINE_ADVANCED_LOGGING)
    message(STATUS "ENGINE_ADVANCED_LOGGING enabled")
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
    src/Core/MemoryTracker.cpp
    src/Core/TextRenderer.cpp
    src/Core/GLUtils.cpp
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
target_link_libraries(engine PRIVATE SDL2::SDL2 SDL2_ttf::SDL2_ttf ${EXTRA_ENGINE_LIBS})

if(ENGINE_ADVANCED_LOGGING)
    target_compile_definitions(engine PRIVATE ENGINE_ADVANCED_LOGGING)
endif()

# Copy assets for runtime

# Copy assets for runtime
file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})



