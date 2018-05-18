cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
project(ArnonSidescroller VERSION 0.0.0 LANGUAGES CXX)

# Enable C++ 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# To make Visual Studio shut up about printf
if(WIN32)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

# Add Main Project
add_subdirectory(arnon)
