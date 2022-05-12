#ifndef DIALOGMODELSELECTION_H
#define DIALOGMODELSELECTION_H
#include "UI.h"
#include "../RenderableObject/RenderableObject.h"
#include "../Camera/Camera.h"
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
    RenderableObject obj;
    bool createFrambuffer();

public:
    void renderOnFrameBuffer(Engine::Frame *super);
    void setUpContent(Engine::Frame *super);
    void renderContent(Engine::Frame *super);
};

#endif;
