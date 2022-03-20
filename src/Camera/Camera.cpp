#include "Camera.h"

Camera::Camera(float intialFov, float horizontalAngle, float verticalAngle)
{
    this->intialFov = intialFov;
    this->horizontalAngle = horizontalAngle;
    this->verticalAngle = verticalAngle;
    this->posytion = glm::vec3(4, 4, 3);
    this->up = glm::vec3(0, 1, 0);

    projectionMatrix = glm::perspective(glm::radians(intialFov), 4.0f / 3.0f, 0.1f, 100.0f);
    viewMatrix = glm::lookAt(posytion, glm::vec3(0, 0, 0), up);
}
void Camera::upDateView()
{
    direction = glm::vec3(
        cos(verticalAngle) * sin(horizontalAngle),
        sin(verticalAngle),
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
        posytion,             // Camera is here
        posytion + direction, // and looks here : at the same position, plus "direction"
        up                    // Head is up (set to 0,-1,0 to look upside-down)
    );
    glm::vec3 var = posytion + direction;
}
