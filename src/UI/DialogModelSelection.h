#ifndef DIALOGMODELSELECTION_H
#define DIALOGMODELSELECTION_H
#include "UI.h"
#include "../RenderableObject/RenderableObject.h"
#include "../Camera/Camera.h"
#include <string>
#include <iostream>
#include <filesystem>

class DialogModelSelection : public UI
{
private:
    /* data */ bool show_demo_window;
    bool show_another_window;
    int width, height;
    Camera camera;
    GLuint fbo, rbo, fboTex;
    GLuint core;
    GLuint matrixID;
    GLuint viewMatrixID;
    GLuint modelMatrixID;
    GLuint lightID;
    int index = 0;
    RenderableObject obj;
    std::vector<RenderableObject> objects;
    std::vector<glm::vec3> ver, normals;
    std::vector<glm::vec2> uv;
    std::vector<std::string> names;
    int size;
    const char *items[100];
    bool createFrambuffer();
    void loadFileList();

public:
    void renderOnFrameBuffer(Engine::Frame *super);
    void setUpContent(Engine::Frame *super);
    void renderContent(Engine::Frame *super);
};

#endif;
