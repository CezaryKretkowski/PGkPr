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
    // setUpGUI(this);
    setUpUi();
    while (!endFlag)
    {
        glClearColor(clearColorRGB[0], clearColorRGB[1], clearColorRGB[2], 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        double x;
        double y;
        float currenTime = glfwGetTime();
        deltaTime = float(currenTime - deltaTime);
        glfwGetCursorPos(window, &x, &y);
        mousePos.x = x;
        mousePos.y = y;
        if (!glfwWindowShouldClose(window) == 0)
            endFlag = true;

        for (std::list<Component *>::iterator i = components.begin(); i != components.end(); i++)
        {
            if (addObjectTriger)
            {
                GameObject *obj = new GameObject(objects[objectIndex].vert, objects[objectIndex].normal, objects[objectIndex].uvs);
                gameObjects.push_back(obj);
                addObjectTriger = false;
            }
            (*i)->run(this);
        }

        // runUpGUI(this);
        glFinish();
        glfwSwapBuffers(window);
        glfwPollEvents();
        deltaTime = glfwGetTime();
    }
    // cleanGUI(this);
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
    clearColorRGB = glm::vec3(color);
}
bool Frame::addObjectToScene(int index, bool add)
{
    return add;
}
void Frame::setUpUi()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
}
void Frame::renderUi()
{
}
