#ifndef UI_H
#define UI_H
#include "../dependeces/imgui/imgui.h"
#include "../../dependeces/imgui/backends/imgui_impl_glfw.h"
#include "../../dependeces/imgui/backends/imgui_impl_opengl3.h"
#include "../Engine/Frame.h"
void setUpGUI(Engine::Frame *f);
void runUpGUI(Engine::Frame *f);
void cleanGUI(Engine::Frame *f);
#endif;