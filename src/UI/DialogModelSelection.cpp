
#include "DialogModelSelection.h"
#include "../../shader.hpp"
#include <cstring>
#include "../../dependeces/Common/dirent.h"

void DialogModelSelection::loadFileList()
{
    DIR *dir;
    struct dirent *ent;
    int i = 0;
    if ((dir = opendir("../../resources/Models")) != NULL)
    { /* print all the files and directories within directory */
        while ((ent = readdir(dir)) != NULL)
        {
            if (strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0)
            {
                std::string name(ent->d_name);

                names.push_back(name);
            }
        }
        i++;
        closedir(dir);
    }
    else
    {
        /* could not open directory */
        perror("");
    }
    size = names.size();
    if (size > 100)
        size = 100;
    int j = 0;
    for (j; j < size; j++)
    {
        const char *name = names[j].c_str();
        // printf("%s \n", name);
        items[j] = name;
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

    objects[index]->setProjectionMatrix(projection);
    objects[index]->setViewMatrix(view);

    glm::vec3 lightPos = glm::vec3(4, 4, 4);
    glUniform3f(lightID, lightPos.x, lightPos.y, lightPos.z);
    objects[index]->draw(matrixID, viewMatrixID, modelMatrixID);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, width, height);
}
void DialogModelSelection::renderContent(Engine::Frame *super)
{

    int counter = 0;

    static int selectable = 0;

    float f = 0.0f;

    ImGui::Text("Model Selection."); // Display some text (you can use a format strings too)
    renderOnFrameBuffer(super);
    if (ImGui::Button("<-", ImVec2(50, 20)))
        control(4);

    ImGui::SameLine();
    if (ImGui::Button("->", ImVec2(50, 20))) // Buttons return true when clicked (most widgets return true when edited/activated)
        control(3);

    ImGui::SameLine();
    if (ImGui::Button("+", ImVec2(50, 20))) // Buttons return true when clicked (most widgets return true when edited/activated)
        control(1);

    ImGui::SameLine();
    if (ImGui::Button("-", ImVec2(50, 20))) // Buttons return true when clicked (most widgets return true when edited/activated)
        control(2);

    ImGui::PushItemWidth(120);
    ImGui::ListBox("list Box", &selectable, items, size, 23);

    ImGui::SetCursorPos(ImVec2(140, 90));
    ImGui::GetWindowDrawList()->AddImage(
        (void *)fboTex,
        ImVec2(ImGui::GetCursorScreenPos()),
        ImVec2(ImGui::GetCursorScreenPos().x + width / 2,
               ImGui::GetCursorScreenPos().y + height / 2),
        ImVec2(0, 1), ImVec2(1, 0));

    ImGui::SetCursorPos(ImVec2(200, 70));
    index = selectable;
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS) %d", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate, index);
    ImGui::SetCursorPos(ImVec2(8, 480));
    if (ImGui::Button("Load", ImVec2(120, 20)))
    {
        super->addObjectTriger = true;
        super->objectIndex = index;
    }
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
    loadFileList();
    projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 300.0f);
    // Camera matrix
    view = glm::lookAt(
        glm::vec3(0.f, 3.f, 3.f),   // Camera is here
        glm::vec3(0.f, 0.f, 0.f),   // and looks here : at the same position, plus "direction"
        glm::vec3(0.0f, 1.0f, 0.0f) // Head is up (set to 0,-1,0 to look upside-down)
    );
    puts("dziala setup");

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

    std::string dirPath = "../../resources/Models/";
    for (std::vector<Engine::Mesh>::iterator i = super->objects.begin(); i != super->objects.end(); i++)
    {
        RenderableObject *object = new RenderableObject();

        // OBJLoad("../../resources/cube1.obj", vert, normals, uvs);
        std::vector<glm::vec3> vert, normal;
        std::vector<glm::vec2> uvs;
        vert = (*i).vert;
        normal = (*i).normal;
        uvs = (*i).uvs;
        object->initFromArrary(vert, normal, uvs);
        object->loadTexture(core, "../../resources/uvmap.png", "myTextureSampler");
        object->setProjectionMatrix(projection);
        object->setViewMatrix(view);
        objects.push_back(object);
    }

    createFrambuffer();
}
void DialogModelSelection::control(int mode)
{
    switch (mode)
    {
    case 1:
        objects[index]->translate(glm::vec3(0.0f, 0.1f, 0.1f));
        break;
    case 2:
        objects[index]->translate(glm::vec3(0.0f, -0.1f, -0.1f));
        break;
    case 3:
        objects[index]->rotate(glm::vec3(0.0f, 1.0f, 0.0f), 2.0f);
        break;
    case 4:
        objects[index]->rotate(glm::vec3(0.0f, -1.0f, 0.0f), 2.0f);
        break;

    default:
        break;
    }
}