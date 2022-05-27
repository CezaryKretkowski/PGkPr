#include "DialogObjectProp.h"
void DialogObjectProp::setUpContent(Engine::Frame *super) {}
void DialogObjectProp::renderContent(Engine::Frame *super) {}
void DialogObjectProp::setUp(Engine::Frame *super)
{

    setUpContent(super);
}
void DialogObjectProp::run(Engine::Frame *super)
{

    // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
    if (visible)

    {

        ImGui::Begin(title.c_str());
        // Create a window called "Hello, world!" and append into it.
        renderContent(super);
        ImGui::End();
    }
}

void DialogObjectProp::clean(Engine::Frame *super)
{
}
