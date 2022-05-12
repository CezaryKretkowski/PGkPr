#include "DialogModelSelection.h"
#include "../../shader.hpp"
namespace fs = std::experimental::filesystem;
void DialogModelSelection::loadFileList()
{
    std::string path = "../../resources";
    for (const auto &entry : fs::directory_iterator(path))
    {
        std::string name = entry.path().string();
        std::cout << name.c_str() << std::endl;
        names.push_back(name.c_str());
    }
}
void DialogModelSelection::renderOnFrameBuffer(Engine::Frame *super)
{
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glViewport(0, 0, width, height);

    camera.upDateView();
    glClearColor(0.0f, 0.0f, 0.4f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(core);

    obj.setProjectionMatrix(camera.getProjectionMatrix());
    obj.setViewMatrix(camera.getViewMatrix());

    glm::vec3 lightPos = glm::vec3(4, 4, 4);
    glUniform3f(lightID, lightPos.x, lightPos.y, lightPos.z);
    obj.draw(matrixID, viewMatrixID, modelMatrixID);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, width, height);
}
void DialogModelSelection::renderContent(Engine::Frame *super)
{

    int counter = 0;

    char *item[] = {"items1", "items1", "items1"};
    static int selectable = 0;
    float f = 0.0f;

    ImGui::Text("Model Selection."); // Display some text (you can use a format strings too)
    renderOnFrameBuffer(super);
    if (ImGui::Button("<-", ImVec2(50, 20)))
        camera.dailogControl(super->getWindow(), super->getWidth(), super->getHeight(), 10, 10, 4);

    ImGui::SameLine();
    if (ImGui::Button("->", ImVec2(50, 20))) // Buttons return true when clicked (most widgets return true when edited/activated)
        camera.dailogControl(super->getWindow(), super->getWidth(), super->getHeight(), 10, 10, 5);

    ImGui::SameLine();
    if (ImGui::Button("^", ImVec2(50, 20))) // Buttons return true when clicked (most widgets return true when edited/activated)
        camera.dailogControl(super->getWindow(), super->getWidth(), super->getHeight(), 10, 10, 0);

    ImGui::SameLine();
    if (ImGui::Button("V", ImVec2(50, 20))) // Buttons return true when clicked (most widgets return true when edited/activated)
        camera.dailogControl(super->getWindow(), super->getWidth(), super->getHeight(), 10, 10, 1);

    ImGui::PushItemWidth(120);
    ImGui::ListBox("list Box", &selectable, &names[0], 23, 23);

    ImGui::SetCursorPos(ImVec2(140, 90));
    ImGui::GetWindowDrawList()->AddImage(
        (void *)fboTex,
        ImVec2(ImGui::GetCursorScreenPos()),
        ImVec2(ImGui::GetCursorScreenPos().x + width / 2,
               ImGui::GetCursorScreenPos().y + height / 2),
        ImVec2(0, 1), ImVec2(1, 0));

    ImGui::SetCursorPos(ImVec2(200, 70));
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
}
bool DialogModelSelection::createFrambuffer()
{
    glGenTextures(1, &fboTex);
    glBindTexture(GL_TEXTURE_2D, fboTex);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fboTex, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rbo);

    int res = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    return res == GL_FRAMEBUFFER_COMPLETE;
}
void DialogModelSelection::setUpContent(Engine::Frame *super)
{
    width = super->getWidth();
    height = super->getHeight();
    puts("dziala setup");
    loadFileList();

    glfwSetInputMode(super->getWindow(), GLFW_STICKY_KEYS, GL_TRUE);

    glfwPollEvents();

    glEnable(GL_DEPTH_TEST);

    glDepthFunc(GL_LESS);

    glEnable(GL_BLEND);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    core = LoadShaders("../../shaders/StandardShading.vertexshader", "../../shaders/StandardShading.fragmentshader");

    matrixID = glGetUniformLocation(core, "MVP");
    viewMatrixID = glGetUniformLocation(core, "V");
    modelMatrixID = glGetUniformLocation(core, "M");
    lightID = glGetUniformLocation(core, "LightPosition_worldspace");

    obj.intFromFile("../../resources/cube1.obj");
    obj.loadTexture(core, "../../resources/uvmap.png", "myTextureSampler");
    obj.setProjectionMatrix(camera.getProjectionMatrix());
    obj.setViewMatrix(camera.getViewMatrix());
    createFrambuffer();
}