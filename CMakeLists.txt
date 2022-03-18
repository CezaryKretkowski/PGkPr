cmake_minimum_required(VERSION 3.0.0)
project(PGKPr VERSION 0.1.0)

set(GLFW_INCLUDE_DIR ./dependeces/glfw/include/)
set(GLFW_LIB_DIR ./dependeces/glfw/lib-vc2022)

set(GLEW_INCLUDE_DIR ./dependeces/glew/include)
set(GLEW_LIB_DIR ./dependeces/glew/lib/Release/x64)
add_subdirectory(dependeces/glm/)

include_directories(${GLFW_INCLUDE_DIR} ${GLEW_INCLUDE_DIR})
link_directories(${GLFW_LIB_DIR} ${GLEW_LIB_DIR})
find_package(OpenGL REQUIRED)
add_executable(PGKPr main.cpp shader.cpp
    dependeces/Common/stb_image.c
    dependeces/Common/stb_image.h
    dependeces/Common/objloader.cpp
    dependeces/Common/objloader.hpp
    src/Engine/Frame.cpp
    src/Engine/Component.h
    src/Camera/Camera.h
    src/Camera/Camera.cpp
    src/RenderableObject/RenderableObject.h
    src/RenderableObject/RenderableObject.cpp
    App.h
)

target_link_libraries(${PROJECT_NAME} glew32s glew32 OpenGL32 glfw3 glm)