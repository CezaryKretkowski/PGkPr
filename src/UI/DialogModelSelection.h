#ifndef DIALOGMODELSELECTION_H
#define DIALOGMODELSELECTION_H
#include "../dependeces/imgui/imgui.h"
#include "../../dependeces/imgui/backends/imgui_impl_glfw.h"
#include "../../dependeces/imgui/backends/imgui_impl_opengl3.h"
#include "../Engine/Component.h"
class DialogModelSelection : public Engine::Component
{
private:
    /* data */
public:
    DialogModelSelection(/* args */);
    ~DialogModelSelection();
};

DialogModelSelection::DialogModelSelection(/* args */)
{
}

DialogModelSelection::~DialogModelSelection()
{
}

#endif;
