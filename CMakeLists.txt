CMAKE_MINIMUM_REQUIRED(VERSION 3.9 FATAL_ERROR)

PROJECT("Arnon_Sidescroller" VERSION 0.0.0 DESCRIPTION "A 2D sidescroller")
MESSAGE("${PROJECT_NAME} v${PROJECT_VERSION}")
MESSAGE(" - ${PROJECT_DESCRIPTION}")
MESSAGE("-----------------------------------")

##############################################################################
# Varaibles
##############################################################################

SET(EXEC_NAME "Arnon")

SET(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
SET(CMAKE_CXX_STANDARD 17)
SET(SOURCE_FILES "src/main.cpp")

# MSVC C++ 17
if(MSVC)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
endif()

##############################################################################
# Build Targets
##############################################################################

ADD_EXECUTABLE(${EXEC_NAME} ${SOURCE_FILES})

##############################################################################
# Libraries
##############################################################################

# INCLUDES
TARGET_INCLUDE_DIRECTORIES(${EXEC_NAME} PUBLIC "src/eventManager" "ext/json")

# FMT
ADD_SUBDIRECTORY("ext/fmt")
TARGET_LINK_LIBRARIES(${EXEC_NAME} fmt)

# OPENGL (Required by IMGUI)
TARGET_LINK_LIBRARIES(${EXEC_NAME} OpenGL)

# IMGUI AND IMGUI_SFML
ADD_SUBDIRECTORY("ext/imgui")
TARGET_LINK_LIBRARIES(${EXEC_NAME} imgui)

# SFML
SET(SFML_STATIC_LIBRARIES TRUE)
FIND_PACKAGE(SFML 2 REQUIRED audio graphics window system)
if(SFML_FOUND)
  INCLUDE_DIRECTORIES(${SFML_INCLUDE_DIR})
  TARGET_LINK_LIBRARIES(${EXEC_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()
