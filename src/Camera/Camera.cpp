#include "Camera.h"

Camera::Camera(glm::vec3 pos, float intialFov, float horizontalAngle, float verticalAngle)
{
    this->intialFov = intialFov;
    this->horizontalAngle = horizontalAngle;
    this->verticalAngle = verticalAngle;
    this->posytion = pos;
    this->up = glm::vec3(0, 1, 0);
    lastTime = 0.0f;

    projectionMatrix = glm::perspective(glm::radians(intialFov), 4.0f / 3.0f, 0.1f, 100.0f);
    viewMatrix = glm::lookAt(posytion, glm::vec3(0, 0, 0), up);
}
void Camera::upDateView()
{
    direction = glm::vec3(
        cos(verticalAngle) * sin(horizontalAngle),
        -0.70f,
        cos(verticalAngle) * cos(horizontalAngle));

    right = glm::vec3(
        sin(horizontalAngle - 3.14f / 2.0f),
        0,
        cos(horizontalAngle - 3.14f / 2.0f));

    glm::vec3 up = glm::cross(right, direction);

    float FoV = intialFov; // - 5 * glfwGetMouseWheel(); // Now GLFW 3 requires setting up a callback for this. It's a bit too complicated for this beginner's tutorial, so it's disabled instead.

    // Projection matrix : 45� Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
    projectionMatrix = glm::perspective(glm::radians(FoV), 4.0f / 3.0f, 0.1f, 100.0f);
    // Camera matrix
    viewMatrix = glm::lookAt(
        posytion,                   // Camera is here
        posytion + direction,       // and looks here : at the same position, plus "direction"
        glm::vec3(0.0f, 1.0f, 0.0f) // Head is up (set to 0,-1,0 to look upside-down)
    );
    glm::vec3 var = posytion + direction;
}
void Camera::control(GLFWwindow *w, int width, int hight)
{
    double currentTime = glfwGetTime();
    float deltaTime = float(currentTime - lastTime);
    double xpos, ypos;
    float speed = 3.0f; // 3 units / second
    float mouseSpeed = 0.5f;

    glfwGetCursorPos(w, &xpos, &ypos);

    // glfwSetCursorPos(w, 1024 / 2, 768 / 2);

    // setHorizontalAngle(getHorizontalAngle() + (mouseSpeed * float(width / 2 - xpos)));
    //  setVerticalAngle(getVerticalAngle() + (mouseSpeed * float(hight / 2 - ypos)));

    if (glfwGetKey(w, GLFW_KEY_W) == GLFW_PRESS)
    {
        direction = glm::vec3(direction[0], 0.0f, direction[2]);
        setPosytion(getPosytion() + getDirection() * deltaTime * speed);
    }
    if (glfwGetKey(w, GLFW_KEY_S) == GLFW_PRESS)
    {
        direction = glm::vec3(direction[0], 0.0f, direction[2]);
        setPosytion(getPosytion() - getDirection() * deltaTime * speed);
    }
    if (glfwGetKey(w, GLFW_KEY_A) == GLFW_PRESS)
    {
        setPosytion(getPosytion() - getRight() * deltaTime * speed);
    }
    if (glfwGetKey(w, GLFW_KEY_D) == GLFW_PRESS)
    {
        setPosytion(getPosytion() + getRight() * deltaTime * speed);
    }
    if (glfwGetKey(w, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        setHorizontalAngle(getHorizontalAngle() + deltaTime * mouseSpeed);
    }
    if (glfwGetKey(w, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        setHorizontalAngle(getHorizontalAngle() - deltaTime * mouseSpeed);
    }

    upDateView();
    lastTime = currentTime;
}
void Camera::dailogControl(GLFWwindow *w, int width, int hight, double xpos, double ypos, int mode)
{
    double currentTime = glfwGetTime();
    float deltaTime = float(currentTime - lastTime);

    float speed = 3.0f; // 3 units / second
    float mouseSpeed = 0.5f;

    // glfwSetCursorPos(w, 1024 / 2, 768 / 2);

    // setHorizontalAngle(getHorizontalAngle() + (mouseSpeed * float(width / 2 - xpos)));
    // setVerticalAngle(getVerticalAngle() + (mouseSpeed * float(hight / 2 - ypos)));

    if (mode == 0)
    {
        direction = glm::vec3(direction[0], 0.0f, direction[2]);
        setPosytion(getPosytion() + getDirection() * deltaTime * speed);
    }
    if (mode == 1)
    {
        direction = glm::vec3(direction[0], 0.0f, direction[2]);
        setPosytion(getPosytion() - getDirection() * deltaTime * speed);
    }
    if (glfwGetKey(w, GLFW_KEY_A) == GLFW_PRESS)
    {
        setPosytion(getPosytion() - getRight() * deltaTime * speed);
    }
    if (glfwGetKey(w, GLFW_KEY_D) == GLFW_PRESS)
    {
        setPosytion(getPosytion() + getRight() * deltaTime * speed);
    }
    if (glfwGetKey(w, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        setHorizontalAngle(getHorizontalAngle() + deltaTime * mouseSpeed);
    }
    if (glfwGetKey(w, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        setHorizontalAngle(getHorizontalAngle() - deltaTime * mouseSpeed);
    }
    // switch (mode)
    // {
    // case 0:
    //     direction = glm::vec3(direction[0], 0.0f, direction[2]);
    //     setPosytion(getPosytion() + getDirection() * deltaTime * speed);
    //     break;
    // case 1:
    //     direction = glm::vec3(direction[0], 0.0f, direction[2]);
    //     setPosytion(getPosytion() - getDirection() * deltaTime * speed);
    //     break;
    // case 2:
    //     setPosytion(getPosytion() - getRight() * deltaTime * speed);
    //     break;
    // case 3:
    //     setPosytion(getPosytion() + getRight() * deltaTime * speed);
    //     break;
    // case 4:
    //     setHorizontalAngle(getHorizontalAngle() + deltaTime * mouseSpeed);
    //     break;
    // case 5:
    //     setHorizontalAngle(getHorizontalAngle() - deltaTime * mouseSpeed);
    //     break;
    // }

    upDateView();
    lastTime = currentTime;
}
