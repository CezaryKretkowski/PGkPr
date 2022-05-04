#ifndef FRAME_H
#define FRAME_H

// Liberies
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stack>
#include <list>
#include "glm/glm.hpp"
#include "Component.h"

namespace Engine
{
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

        // Private metods
        bool glfwInital();

        bool glewInital();

        void mainLoop();

    public:
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

        void clearColor(glm::vec4 color);
    };
}
#endif;
