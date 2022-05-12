#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include "glfw/glfw3.h"
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
private:
    /* data */
    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;
    double lastTime;
    glm::vec3 posytion;
    glm::vec3 direction;
    glm::vec3 right;
    glm::vec3 up;

    float horizontalAngle;
    float verticalAngle;
    float intialFov;

public:
    glm::mat4 getViewMatrix() { return viewMatrix; }
    glm::mat4 getProjectionMatrix() { return projectionMatrix; }
    glm::vec3 getDirection() { return direction; }
    glm::vec3 getUp() { return up; }
    glm::vec3 getPosytion() { return posytion; }
    glm::vec3 getRight() { return right; }
    float getVerticalAngle() { return verticalAngle; }
    float getHorizontalAngle() { return horizontalAngle; }

    void setPosytion(glm::vec3 pos) { this->posytion = pos; }
    void setHorizontalAngle(float angle) { this->horizontalAngle = angle; }
    void setVerticalAngle(float angle) { this->verticalAngle = angle; }
    void upDateView();

    Camera(glm::vec3 pos = glm::vec3(0, 10, 19), float intialFov = 45.0f, float horizontalAngle = 3.14f, float verticalAngle = 0.0f);
    ~Camera(){};

    void control(GLFWwindow *w, int width, int hight);
    void dailogControl(GLFWwindow *w, int width, int hight, double xpos, double ypos, int mode);
};

#endif;
