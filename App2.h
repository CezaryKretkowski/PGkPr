#ifndef APP2_H
#define APP2_H
#include "src/Scene/Scene.h"
#include "src/Camera/Camera.h"
#include "src/RenderableObject/RenderableObject.h"
#include "src/Engine/Frame.h"
#include "src/GameObject/GameObject.h"

class App2 : public Engine::Scene
{
private:
    glm::mat4 mat = glm::mat4(1.0);

    double lastTime;
    float speed = 3.0f; // 3 units / second
    float mouseSpeed = 0.0005f;
    GLuint programID;
    GLuint programID2;
    GLuint M;
    GLuint V;
    GLuint P;
    GLuint texture;
    GLuint texture2;
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 proejction;
    GLuint LightID;
    GameObject *obj3;
    float vv[3] = {5.0f, 3.0f, 0.0f};
    /* data */
public:
    App2(/* args */);
    ~App2();
    void upDateScene(Engine::Frame *super) override
    {
        camera.upDateView();
        super->clearColor(glm::vec4(0.8f, 0.8f, 0.8f, 0.1f));
        camera.control(super->getWindow(), super->getWidth(), super->getHeight());
        glUseProgram(programID);

        model = obj3->getModelMatrix();
        view = camera.getViewMatrix();
        proejction = camera.getProjectionMatrix();
        obj3->setProjectionMatrix(proejction);
        obj3->setViewMatrix(view);
        glUniform1i(texture, 0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture2);

        glUniformMatrix4fv(M, 1, GL_FALSE, &model[0][0]);
        glUniformMatrix4fv(V, 1, GL_FALSE, &view[0][0]);
        glUniformMatrix4fv(P, 1, GL_FALSE, &proejction[0][0]);
        //  glDrawArrays(GL_TRIANGLES, 0, 36);
        obj3->draw();
    }
    void initScene(Engine::Frame *super) override
    {
        glfwSetInputMode(super->getWindow(), GLFW_STICKY_KEYS, GL_TRUE);
        glfwPollEvents();
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        std::vector<glm::vec3> ver, normal;
        std::vector<glm::vec2> textCoard;
        OBJLoad("../../resources/cube1.obj", ver, normal, textCoard);

        obj3 = new GameObject(ver, normal, textCoard);
        programID = LoadShaders("../../shaders/GameObjectVert.glsl", "../../shaders/GameObjectFrag.glsl");
        programID2 = LoadShaders("../../shaders/GameObjectVert.glsl", "../../shaders/GameObjectFrag.glsl");
        M = glGetUniformLocation(programID, "M");
        V = glGetUniformLocation(programID, "V");
        P = glGetUniformLocation(programID, "P");
        texture = glGetUniformLocation(programID, "SamplerTexture");
        texture2 = obj3->loadTexture("../../resources/blank.png");
        camera.control(super->getWindow(), super->getWidth(), super->getHeight());
        camera.upDateView(); // Camera matrix
    }
    void cleanScene(Engine::Frame *super) override { puts("działa clean"); }
};

App2::App2(/* args */)
{
}

App2::~App2()
{
}

#endif;