#ifndef UI_H
#define UI_H

#include "../dependeces/imgui/imgui.h"
#include "../../dependeces/imgui/backends/imgui_impl_glfw.h"
#include "../../dependeces/imgui/backends/imgui_impl_opengl3.h"
#include "../Engine/Frame.h"

#include "../Engine/Component.h"
void setUpGUI(Engine::Frame *f);
void runUpGUI(Engine::Frame *f);
void cleanGUI(Engine::Frame *f);
class UI : public Engine::Component
{
protected:
    bool visible;
    std::string title;
    ImVec4 clear_color;

    void run(Engine::Frame *super) override;
    void setUp(Engine::Frame *super) override;
    void clean(Engine::Frame *super) override;

public:
    UI(std::string title = "simple Window", ImVec4 clearColor = ImVec4(0.45f, 0.55f, 0.60f, 1.00f));
    ~UI() {}
    bool isVisible() { return visible; }
    void setVisiblity(bool vs) { visible = vs; }
    void addGameObject(Engine::Mesh *o) override {}
    virtual void setUpContent(Engine::Frame *super) {}
    virtual void renderContent(Engine::Frame *super) {}
};
#endif;