cmake_minimum_required(VERSION 3.15...3.31)

set(CMAKE_CXX_STANDARD 20) 

project(RollForHonor VERSION 1.0 LANGUAGES CXX)

# Add custom CMake modules directory to the search path.
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/")


# Include the custom module that defines `add_git_submodule()`
include(AddGitSubmodule)


# Add Git submodules for dependencies:
# 1. Catch2 - A unit testing framework for C++.
add_git_submodule(${PROJECT_SOURCE_DIR}/external/Catch2)

# 2. fmt - A modern formatting library (used by spdlog).
add_git_submodule(${PROJECT_SOURCE_DIR}/external/fmt)

# 3. nlohmann/json - A C++ JSON library.
add_git_submodule(${PROJECT_SOURCE_DIR}/external/nlohmann/json)

# 4. spdlog - A fast C++ logging library.
add_git_submodule(${PROJECT_SOURCE_DIR}/external/spdlog)

# 5. raylib - Simple and easy-to-use library to enjoy videogames programming.
add_git_submodule(${PROJECT_SOURCE_DIR}/external/raylib)


# Add main source and test directories as subprojects.
# - `src/` contains the main application code.
# - `test/` contains unit tests (likely Catch2).
add_subdirectory("src")
add_subdirectory("test")
