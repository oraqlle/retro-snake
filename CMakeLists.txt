cmake_minimum_required(VERSION 3.25)

project(
    snake
    VERSION 0.1.0
    DESCRIPTION "snake in raylib"
    LANGUAGES CXX
)

# ---- Global Defines ----
set(CMAKE_EXPORT_COMPILE_COMMANDS   ON  CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS               ON  CACHE BOOL "" FORCE)
set(CMAKE_CXX_STANDARD_REQUIRED     ON  CACHE BOOL "" FORCE)
set(CMAKE_CXX_EXTENSIONS            OFF CACHE BOOL "" FORCE)

#---- raylib Defines ----
set(BUILD_EXAMPLES  OFF CACHE BOOL "" FORCE) # don't build the supplied examples
set(BUILD_GAMES     OFF CACHE BOOL "" FORCE) # don't build the supplied example games
set(WITH_PIC        ON  CACHE BOOL "" FORCE) # Process Independent Code

# ---- Dependencies ----
include(FetchContent)
FetchContent_Declare(
    raylib
    GIT_REPOSITORY  https://github.com/raysan5/raylib.git
    GIT_TAG         6.0
    GIT_PROGRESS    true
)

FetchContent_MakeAvailable(raylib)

add_executable(snake src/main.cpp)
target_compile_features(snake PRIVATE cxx_std_20)
target_link_libraries(snake PRIVATE raylib)

if (MSVC)
    # warning level 4
    target_compile_options(snake PRIVATE /W4)
else()
    # additional warnings
    target_compile_options(snake PRIVATE -Wall -Wextra -Werror -Wpedantic)
endif()

# Checks if OSX and links appropriate frameworks (only required on MacOS)
if (APPLE)
    target_link_libraries(snake PRIVATE "-framework IOKit")
    target_link_libraries(snake PRIVATE "-framework Cocoa")
    target_link_libraries(snake PRIVATE "-framework OpenGL")
endif()
