# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(Raycasting-in-Maze VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find SDL2 package
find_package(SDL2 REQUIRED)

# Include the directory for header files
include_directories(include)

# Add the executable by specifying source files
add_executable(Raycasting-in-Maze
    src/main.cpp
    src/Game.cpp
    src/Renderer.cpp
    src/Player.cpp
    src/Maze.cpp
)

# Link the SDL2 libraries
target_link_libraries(Raycasting-in-Maze PRIVATE SDL2::SDL2 SDL2::SDL2main)

# Include SDL2 directories
target_include_directories(Raycasting-in-Maze PRIVATE ${SDL2_INCLUDE_DIRS})

# Compiler flags for safety
# if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
#     target_compile_options(Raycasting-in-Maze PRIVATE
#         -Wall                # Enable all common warnings
#         -Wextra              # Enable extra warnings
#         -Werror              # Treat all warnings as errors
#         -Wpedantic           # Strict ISO C++ compliance
#         -Wnull-dereference   # Warn if a null dereference is detected
#         -fstack-protector-strong # Stack protection to prevent stack overflow exploits
#         -fsanitize=address   # Address sanitizer for detecting memory issues
#         -fsanitize=undefined # Undefined behavior sanitizer
#         -fno-omit-frame-pointer # Ensure frame pointers are kept for better debugging
#     )
    
#     target_link_options(Raycasting-in-Maze PRIVATE
#         -fsanitize=address
#         -fsanitize=undefined
#     )
# endif()
