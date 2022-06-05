cmake_minimum_required(VERSION 3.0.0)
project(PGKPr VERSION 0.1.0)

set(GLFW_INCLUDE_DIR dependeces/glfw/include/)
set(GLFW_LIB_DIR dependeces/glfw/lib-vc2022)

set(GLEW_INCLUDE_DIR dependeces/glew/include)
set(GLEW_LIB_DIR dependeces/glew/lib/Release/x64)
add_subdirectory(dependeces/glm/)

include_directories(${GLFW_INCLUDE_DIR} ${GLEW_INCLUDE_DIR})
link_directories(${GLFW_LIB_DIR} ${GLEW_LIB_DIR})
find_package(OpenGL REQUIRED)
add_executable(PGKPr main.cpp shader.cpp
    dependeces/Common/stb_image.c
    dependeces/Common/stb_image.h
    dependeces/Common/OBJ_Loader.h
    dependeces/imgui/backends/imgui_impl_glfw.h
    dependeces/imgui/backends/imgui_impl_glfw.cpp
    dependeces/imgui/backends/imgui_impl_opengl3.h
    dependeces/imgui/backends/imgui_impl_opengl3.cpp
    dependeces/imgui/imgui.h
    dependeces/imgui/imgui.cpp
    dependeces/imgui/imgui_demo.cpp
    dependeces/imgui/imgui_draw.cpp
    dependeces/imgui/imgui_internal.h
    dependeces/imgui/imgui_tables.cpp
    dependeces/imgui/imgui_widgets.cpp
    dependeces/imgui/imstb_rectpack.h
    dependeces/imgui/imstb_textedit.h
    dependeces/imgui/imstb_truetype.h
    dependeces/Common/objloader.cpp
    dependeces/Common/objloader.hpp
    src/UI/DialogModelSelection.h
    src/UI/DialogModelSelection.cpp
    src/Engine/Frame.h
    src/Engine/Frame.cpp
    src/Engine/Component.h
    src/RenderableObject/RenderableObject.h
    src/RenderableObject/RenderableObject.cpp
    src/Camera/Camera.cpp
    src/Camera/Camera.h
    src/RenderableObject/Skybox.h
    src/RenderableObject/Skybox.cpp
    src/GameObject/GameObject.cpp
    src/GameObject/GameObject.h
    src/UI/DialogObjectProp.h
    src/UI/DialogObjectProp.cpp
    src/UI/UI.cpp
    src/UI/UI.h
    src/UI/DialogLightSettings.h
    src/UI/DialogLightSettings.cpp
    src/ParticleSystem/Particle.h
    src/ParticleSystem/ParticleSystem.h

    App.h

    src/Scene/Scene.h
)

target_link_libraries(${PROJECT_NAME} glew32s glew32 OpenGL32 glfw3 glm)
