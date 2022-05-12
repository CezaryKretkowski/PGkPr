#include "UI.h"
#include "../Engine/Frame.h"

UI::UI(std::string title, ImVec4 clearColor)
{
    this->title = title;
    this->visible = false;
    clear_color = clearColor;
}
void UI::setUp(Engine::Frame *super)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(super->getWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 330");
    setUpContent(super);
}
void UI::run(Engine::Frame *super)
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
    if (visible)
    // ImGui::ShowDemoWindow(&show_demo_window);

    // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
    {

        ImGui::Begin(title.c_str());
        // Create a window called "Hello, world!" and append into it.
        renderContent(super);
        ImGui::End();
    }
    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(super->getWindow(), &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void UI::clean(Engine::Frame *super)
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
