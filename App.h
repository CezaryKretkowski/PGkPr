#ifndef APP_H
#define APP_H
#include "src/Scene/Scene.h"
#include "src/Camera/Camera.h"
#include "src/RenderableObject/RenderableObject.h"

std::vector<glm::vec3> floarVec1;
std::vector<glm::vec3> floarVec2;
std::vector<glm::vec2> floarVec3;

std::vector<glm::vec3> floarVec = {
    glm::vec3(-2.0f, 0.0f, 2.0f),
    glm::vec3(-2.0f, 0.0f, -2.0f),
    glm::vec3(2.0f, 0.0f, -2.0f),

    glm::vec3(2.0f, 0.0f, -2.0f),
    glm::vec3(2.0f, 0.0f, 2.0f),
    glm::vec3(-2.0f, 0.0f, 2.0f)};

std::vector<glm::vec3> floarNormal = {
    glm::vec3(0.0f, 1.0f, 0.0f),
    glm::vec3(0.0f, 1.0f, 0.0f),
    glm::vec3(0.0f, 1.0f, 0.0f),
    glm::vec3(0.0f, 1.0f, 0.0f),
    glm::vec3(0.0f, 1.0f, 0.0f),
    glm::vec3(0.0f, 1.0f, 0.0f)};

std::vector<glm::vec2> floarUV = {
    glm::vec2(0.0f, 1.0f),
    glm::vec2(0.0f, 0.0f),
    glm::vec2(1.0f, 0.0f),

    glm::vec2(1.0f, 0.0f),
    glm::vec2(1.0f, 1.0f),
    glm::vec2(0.0f, 1.0f)

};
class App : public Engine::Scene
{
private:
    glm::mat4 mat = glm::mat4(1.0);

    double lastTime;
    float speed = 3.0f; // 3 units / second
    float mouseSpeed = 0.0005f;
    GLuint programID;
    GLuint MatrixID;
    GLuint ViewMatrixID;
    GLuint ModelMatrixID;
    RenderableObject obj;
    RenderableObject malpa;
    RenderableObject floor;
    GLuint LightID;

    float vv[3] = {5.0f, 3.0f, 0.0f};
    /* data */
public:
    App(/* args */);
    ~App();
    void upDateScene(Engine::Frame *super) override
    {
        super->clearColor(glm::vec4(0.8f, 0.8f, 0.8f, 0.1f));
        glUseProgram(programID);
        camera.control(super->getWindow(), super->getWidth(), super->getHeight());
        camera.upDateView();
        obj.setProjectionMatrix(camera.getProjectionMatrix());
        obj.setViewMatrix(camera.getViewMatrix());
        floor.setProjectionMatrix(camera.getProjectionMatrix());
        floor.setViewMatrix(camera.getViewMatrix());
        malpa.setProjectionMatrix(camera.getProjectionMatrix());
        malpa.setViewMatrix(camera.getViewMatrix());
        // Set our "myTextureSampler" sampler to use Texture Unit 0

        glm::vec3 lightPos = glm::vec3(4, 4, 4);
        glUniform3f(LightID, lightPos.x, lightPos.y, lightPos.z);
        obj.draw(MatrixID, ViewMatrixID, ModelMatrixID);
        //  floor.draw(MatrixID, ViewMatrixID, ModelMatrixID);
        malpa.draw(MatrixID, ViewMatrixID, ModelMatrixID);

        glBindVertexArray(0);
        // control(super->getWindow());
    }
    void initScene(Engine::Frame *super) override
    {
        glfwSetInputMode(super->getWindow(), GLFW_STICKY_KEYS, GL_TRUE);
        // Hide the mouse and enable unlimited mouvement
        //   glfwSetInputMode(super->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        glfwPollEvents();
        //  glfwSetCursorPos(super->getWindow(), 1024 / 2, 768 / 2);
        // glfwSetCursorPos(window, 1024 / 2, 768 / 2);

        glEnable(GL_DEPTH_TEST);
        // Accept fragment if it closer to the camera than the former one
        glDepthFunc(GL_LESS);

        glEnable(GL_BLEND);

        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        programID = LoadShaders("../../shaders/StandardShading.vertexshader", "../../shaders/StandardShading.fragmentshader");

        MatrixID = glGetUniformLocation(programID, "MVP");
        ViewMatrixID = glGetUniformLocation(programID, "V");
        ModelMatrixID = glGetUniformLocation(programID, "M");

        obj.intFromFile("../../resources/cube1.obj");
        obj.loadTexture(programID, "../../resources/uvmap.png", "myTextureSampler");
        malpa.loadTexture(programID, "../../resources/uvmap.png", "myTextureSampler");
        malpa.intFromFile("../../resources/cube1.obj");
        obj.translate(glm::vec3(0.0f, -2.0f, 0.0f));

        obj.scale(glm::vec3(1.0f, -1.0f, 1.0f));
        malpa.translate(glm::vec3(0.0f, 2.0f, 0.0f));

        floor.loadTexture(programID, "../../resources/floor.png", "myTextureSampler");
        floor.initFromArrary(floarVec, floarNormal, floarUV);
        floor.scale(glm::vec3(50.0f, 2.0f, 50.0f));

        lastTime = glfwGetTime();
        glUseProgram(programID);
        LightID = glGetUniformLocation(programID, "LightPosition_worldspace");

        camera.upDateView(); // Camera matrix

        obj.setProjectionMatrix(camera.getProjectionMatrix());
        obj.setViewMatrix(camera.getViewMatrix());
        floor.setProjectionMatrix(camera.getProjectionMatrix());
        floor.setViewMatrix(camera.getViewMatrix());
        malpa.setProjectionMatrix(camera.getProjectionMatrix());
        malpa.setViewMatrix(camera.getViewMatrix());
    }
    void cleanScene(Engine::Frame *super) override { puts("działa clean"); }
};

App::App(/* args */)
{
}

App::~App()
{
}

#endif;
