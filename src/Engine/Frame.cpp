#include "Frame.h"

using namespace Engine;

bool Frame::glewInital()
{
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK)
    {
        fprintf(stderr, "Failed to initialize GLEW\n");
        getchar();
        glfwTerminate();
        return false;
    }
    return true;
}

bool Frame::glfwInital()
{
    if (!glfwInit())
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
        getchar();
        return false;
    }
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    return true;
}

void Frame::closeFrame()
{
    endFlag = true;
}

void Frame::reloadFrame()
{
    endFlag = false;
    mainLoop();
}

void Frame::mainLoop()
{
}

bool Frame::init(int width, int height, std::string title, bool mode)
{
    if (!glewInital())
        return false;
    if (mode)
        window = glfwCreateWindow(width, height, title.c_str(), glfwGetPrimaryMonitor(), NULL);
    else
        window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

    if (window == NULL)
        return false;

    glfwMakeContextCurrent(window);

    if (!glewInital())
        return false;

    return true;
}
Frame::~Frame()
{
    glfwTerminate();
}
