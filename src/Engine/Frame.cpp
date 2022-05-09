#include "Frame.h"
#include "../UI/UI.h"
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
    double posX, posY;
    for (std::list<Component *>::iterator i = components.begin(); i != components.end(); i++)
        (*i)->setUp(this);
    setUpGUI(this);

    while (!endFlag)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        if (!glfwWindowShouldClose(window) == 0)
            endFlag = true;

        for (std::list<Component *>::iterator i = components.begin(); i != components.end(); i++)
            (*i)->run(this);
        runUpGUI(this);
        glFinish();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    cleanGUI(this);
    for (std::list<Component *>::iterator i = components.begin(); i != components.end(); i++)
        (*i)->clean(this);
}

bool Frame::init(bool mode, int width, int height, std::string title)
{
    if (!glfwInital())
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
    glfwSwapInterval(1);
    mainLoop();

    return true;
}
void Frame::add(Component *c)
{
    components.push_back(c);
}
Frame::~Frame()
{
    glfwTerminate();
}
void Frame::clearColor(glm::vec4 color)
{
    glClearColor(color[0], color[1], color[2], color[3]);
}
