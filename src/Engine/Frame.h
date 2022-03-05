#ifndef FRAME_H
#define FRAME_H

// Liberies
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

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

        // Private metods
        bool glfwInital();

        bool glewInital();

        void mainLoop();

    public:
        // Constructor and desctructor
        Frame(/* args */) = default;
        ~Frame();

        // Public methods
        bool init(int width, int height, std::string title, bool mode);

        // setters
        void setWidth(int width) { this->width = width; }

        void setHeight(int height) { this->height = height; }

        void setTitle(std::string title) { this->title = title; }

        // getters
        int getWidth() { return width; }

        int getHeight() { return height; }

        std::string getTitle() { return title; }
    };
}
#endif;