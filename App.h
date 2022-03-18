#ifndef APP_H
#define APP_H
#include "src/Engine/Component.h"
#include "src/Camera/Camera.h"
class App : public Engine::Component
{
private:
    glm::mat4 mat = glm::mat4(1.0);
    Camera camera;
    double lastTime;
    float speed = 3.0f; // 3 units / second
    float mouseSpeed = 0.0005f;

    /* data */
public:
    App(/* args */);
    ~App();
    void run(Engine::Frame *super)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
    void setUp(Engine::Frame *super)
    {
        glfwSetInputMode(super->getWindow(), GLFW_STICKY_KEYS, GL_TRUE);
        // Hide the mouse and enable unlimited mouvement
        glfwSetInputMode(super->getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        // glfwSetCursorPos(window, 1024 / 2, 768 / 2);
        glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
        glEnable(GL_DEPTH_TEST);
        // Accept fragment if it closer to the camera than the former one
        glDepthFunc(GL_LESS);

        glEnable(GL_BLEND);

        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        lastTime = glfwGetTime();
    }
    void clean(Engine::Frame *super) { puts("działa clean"); }
    void control(GLFWwindow *w);
};

void App::control(GLFWwindow *w)
{
    double currentTime = glfwGetTime();
    float deltaTime = float(currentTime - lastTime);
    double xpos, ypos;
    glfwGetCursorPos(w, &xpos, &ypos);

    camera.setHorizontalAngle(camera.getHorizontalAngle() + (mouseSpeed * float(1024 / 2 - xpos)));
    camera.setVerticalAngle(camera.getVerticalAngle() + (mouseSpeed * float(1024 / 2 - xpos)));

    if (glfwGetKey(w, GLFW_KEY_W) == GLFW_PRESS)
    {
        camera.setPosytion(camera.getPosytion() + camera.getDirection() * deltaTime * speed);
    }
    if (glfwGetKey(w, GLFW_KEY_S) == GLFW_PRESS)
    {
        camera.setPosytion(camera.getPosytion() - camera.getDirection() * deltaTime * speed);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        camera.setPosytion(camera.getPosytion() - camera.getRight() * deltaTime * speed);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        camera.setPosytion(camera.getPosytion() + camera.getRight() * deltaTime * speed);
    }
    camera.upDateView();
}
App::App(/* args */)
{
}

App::~App()
{
}

#endif;