#ifndef RAIN_H
#define RAIN_H

#include "../Engine/Component.h"
#include "../Laby/Particles.h"
#include "../Laby/ParticleSystem.h"
#include "../Camera/Camera.h"
#include "App.h"

class Rain : public Engine::Component {
private:
    Camera camera;
    int MAX_PART = 110;
    Particles particles[110];
    float ACTIVATE_TIME = 0.01f;
    float act_time = 0.0f;
    float lastTime;
    GLuint programID;
    GLuint programID1;
    GLuint MatrixID;
    GLuint MatrixID1;
    glm::vec2 dimensions;
    GLuint ViewMatrixID;
    GLuint ModelMatrixID;
    GLuint ViewMatrixID1;
    GLuint ModelMatrixID1;
    GLuint LightID;
    GLuint colorID;
    RenderableObject floor;
    glm::vec4 color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
    /* data */
public:
    Rain(/* args */){};

    ~Rain(){};

    void run(Engine::Frame *super) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glm::vec3 lightPos = glm::vec3(-4, 4, -4);
        glUseProgram(programID1);
        glUniform3f(LightID, lightPos.x, lightPos.y, lightPos.z);
        floor.setProjectionMatrix(camera.getProjectionMatrix());
        floor.setViewMatrix(camera.getViewMatrix());
        floor.draw(MatrixID1, ViewMatrixID1, ModelMatrixID1);

        glUseProgram(programID);
        camera.control(super->getWindow(), super->getWidth(), super->getHeight());



        glUniform3f(LightID, lightPos.x, lightPos.y, lightPos.z);


        glm::mat4 modelMat = glm::mat4(1.0);
        float nowTime = glfwGetTime();
        float times = (nowTime - lastTime);
        act_time += times;

        for (int i = 0; i < MAX_PART; i++) {

            if (particles[i].isActive()) {

                glm::vec3 vec = particles[i].getPos();

                particles[i].live(times);
                particles[i].setDirection(glm::vec3(vec[1],-10,vec[2]));

            } else {
                if (act_time >= ACTIVATE_TIME) {
                    act_time = 0.0f;
                    particles[i].activate();
                    // puts("Aktywana");
                }
                break;
            }
        }
        for (int i = 0; i < MAX_PART; i++) {
            if (particles[i].isActive()) {
                glm::vec3 colors = particles[i].getColor();


                glUniform4f(colorID, 0.0f, 0.0f, 1.0f, 1.0f);
                particles[i].getObj()->setProjectionMatrix(camera.getProjectionMatrix());
                particles[i].getObj()->setViewMatrix(camera.getViewMatrix());
                particles[i].getObj()->setModelMatrix(glm::mat4(1.0));
                particles[i].getObj()->translate(particles[i].getPos());

                particles[i].getObj()->draw(MatrixID, ViewMatrixID, ModelMatrixID);


            }
        }


        lastTime = nowTime;
        glBindVertexArray(0);
    }

    void setUp(Engine::Frame *super) {
        // Hide the mouse and enable unlimited mouvement
        glfwSetInputMode(super->getWindow(), GLFW_STICKY_KEYS, GL_TRUE);
        // Hide the mouse and enable unlimited mouvement
        glfwSetInputMode(super->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        glfwPollEvents();
        glfwSetCursorPos(super->getWindow(), 1024 / 2, 768 / 2);
        // glfwSetCursorPos(window, 1024 / 2, 768 / 2);
        glClearColor(0.8f, 0.8f, 1.0f, 0.0f);
        glEnable(GL_DEPTH_TEST);
        // Accept fragment if it closer to the camera than the former one
        glDepthFunc(GL_LESS);

        glEnable(GL_BLEND);

        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        programID = LoadShaders("shaders/StandardShading.vertexshader", "shaders/MyShader.fragmentshader");
        programID1 = LoadShaders("shaders/StandardShading.vertexshader", "shaders/StandardShading.fragmentshader");

        MatrixID = glGetUniformLocation(programID, "MVP");
        ViewMatrixID = glGetUniformLocation(programID, "V");
        ModelMatrixID = glGetUniformLocation(programID, "M");

        MatrixID1 = glGetUniformLocation(programID1, "MVP");
        ViewMatrixID1 = glGetUniformLocation(programID1, "V");
        ModelMatrixID1 = glGetUniformLocation(programID1, "M");

        for (int i = 0; i < MAX_PART; i++)
            particles[i].getObj()->intFromFile("resources/a_to_jez_jak_kulka.obj", programID, "resources/uvmap.png",
                                               "myTextureSampler");

        glUseProgram(programID);
        LightID = glGetUniformLocation(programID, "LightPosition_worldspace");

        colorID = glGetUniformLocation(programID, "ourColor");



        floor.initFromArrary(floarVec, floarNormal, floarUV, programID, "resources/floor.png", "myTextureSampler");
        for (int i = 0; i < MAX_PART; i++) {
            particles[i].setEmiterPos(glm::vec3(0.0f, 10.0f, 0.0f));
            particles[i].setMode(SQUARE);
            particles[i].setSpeed(4.0);
            particles[i].setGravity(glm::vec3(-1.0f,-10.0f,1.0f));
            particles[i].setDimension(glm::vec3(2.0f,2.0f,2.0f));
            particles[i].getObj()->setProjectionMatrix(camera.getProjectionMatrix());
            particles[i].getObj()->setViewMatrix(camera.getViewMatrix());
        }
        glUseProgram(programID1);
        LightID = glGetUniformLocation(programID1, "LightPosition_worldspace");
        floor.translate(glm::vec3(0.0,-6.0,0.0));
        floor.setProjectionMatrix(camera.getProjectionMatrix());
        floor.setViewMatrix(camera.getViewMatrix());
        lastTime = glfwGetTime();
    }

    void clean(Engine::Frame *super) {}
    float F_RAND(float end)
    {
        return static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX / end);
    }
};



#endif;
