# Arnon Sidescroller

add_executable(${PROJECT_NAME} "")

# Set source files
target_sources(${PROJECT_NAME}
               PRIVATE
               # Project Specific Files
               ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp

               # GLFW Wrapping
               ${CMAKE_CURRENT_SOURCE_DIR}/src/window.h
               ${CMAKE_CURRENT_SOURCE_DIR}/src/window.cpp

               # OpenGL Wrapping
               ${CMAKE_CURRENT_SOURCE_DIR}/src/GL/glCore45.h
               ${CMAKE_CURRENT_SOURCE_DIR}/src/GL/glCore45.cpp
               ${CMAKE_CURRENT_SOURCE_DIR}/src/GL/vertexBuffer.h
               ${CMAKE_CURRENT_SOURCE_DIR}/src/GL/vertexBuffer.cpp
               ${CMAKE_CURRENT_SOURCE_DIR}/src/GL/indexBuffer.h
               ${CMAKE_CURRENT_SOURCE_DIR}/src/GL/indexBuffer.cpp
               )

# Set include directories
target_include_directories(${PROJECT_NAME}
                           PRIVATE
                           ${CMAKE_CURRENT_SOURCE_DIR}/src
                           )

# Find Packages
find_package(glfw3 3.2 REQUIRED)
find_package(glm REQUIRED)
find_package(OpenGL REQUIRED)

# Link Libraries
target_link_libraries(${PROJECT_NAME}
                      glfw
                      glm
                      OpenGL::GL
                      )

# TODO: Define Install Targets Here
