#ifndef FRAME_H
#define FRAME_H

// Liberies
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stack>
#include "../RenderableObject/RenderableObject.h"
#include "../GameObject/GameObject.h"

#include <list>
#include "glm/glm.hpp"

#include "Component.h"

namespace Engine
{
    class Mesh
    {
    public:
        std::vector<glm::vec3> vert, normal;
        std::vector<glm::vec2> uvs;
    };
    class ParticleSystemOption
    {
    public:
        int mode = 0;
        bool reset = false;
        bool swich = true;
        int texture = 0;
        int effectNumber;
        int maxParticles = 100;
        glm::vec3 emiterPos = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 shapePos = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 garvity = glm::vec3(0.0f, -1.0f, 0.0f);
        glm::vec2 fadeTime = glm::vec2(1.0f, 5.0f);
    };

// macros
#define FULL_SCREEN true
#define WINDOW_MODE false
    class Frame
    {
    private:
        // Filds
        GLFWwindow *window;
        int width = 1024;
        int height = 768;
        std::string title = "PGKPR";
        bool endFlag = false;
        std::list<Component *> components;
        glm::vec2 mousePos;
        glm::vec3 clearColorRGB;
        // Private metods
        bool glfwInital();

        bool glewInital();

        void mainLoop();

    public:
        bool drawSkyBox = false;
        bool addObjectTriger = false;
        int objectIndex = 0;
        float deltaTime;
        LightProps lightProps;
        LightProps lightPropsSkybox;
        std::vector<Mesh> objects;
        std::vector<GameObject *> gameObjects;
        ParticleSystemOption op;

        // Constructor and desctructor
        Frame(/* args */) { endFlag = false; }
        ~Frame();

        // Public methods
        bool init(bool mode = false, int width = 1024, int height = 768, std::string title = "PGKPR");

        void reloadFrame();

        void closeFrame();

        void add(Component *c);

        // setters
        void setWidth(int width) { this->width = width; }

        void setHeight(int height) { this->height = height; }

        void setTitle(std::string title) { this->title = title; }

        // getters
        int getWidth() { return width; }

        int getHeight() { return height; }

        GLFWwindow *getWindow() { return window; }

        std::string getTitle() { return title; }

        glm::vec2 getMousePos() { return mousePos; }

        void clearColor(glm::vec4 color);
        glm::vec3 getClearColor() { return clearColorRGB; }

        bool addObjectToScene(int index, bool add);
        void setUpUi();
        void renderUi();
    };
}
#endif;
