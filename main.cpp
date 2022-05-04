// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GL/glew.h>

// Include GLM
#include <glm/glm.hpp>
using namespace glm;

#include "shader.hpp"
#include "src/Engine/Frame.h"
#include "App.h"
#include "src/Scene/Scene.h"

#include <math.h>

int main(void)
{
    // printf("Wynik %f",  calculateDistance(glm::vec3(-4,0,1),glm::vec3(1,-3,2)));

    App *app = new App();
    Engine::Frame frame;
    frame.add(app);
    if (!frame.init())
    {
        puts("Somthing wnet wrong");
    }

    return 0;
}
