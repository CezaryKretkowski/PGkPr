#ifndef LAB02_H
#define LAB02_H

#include "../Engine/Component.h"
#include "../Laby/Particles.h"
#include "../Laby/ParticleSystem.h"
#include "../Camera/Camera.h"

class Lab02 : public Engine::Component {
private:
    Camera camera;
    int MAX_PART = 110;
    Particles particles[110];
    float ACTIVATE_TIME = 0.01f;
    float act_time = 0.0f;
    float lastTime;
    GLuint programID;
    GLuint MatrixID;
    glm::vec2 dimensions;
    GLuint ViewMatrixID;
    GLuint ModelMatrixID;
    GLuint LightID;
    GLuint colorID;
    glm::vec4 color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
    /* data */
public:
    Lab02(/* args */);

    ~Lab02();

    void run(Engine::Frame *super) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(programID);


        glm::vec3 lightPos = glm::vec3(-4, 4, -4);
        glUniform3f(LightID, lightPos.x, lightPos.y, lightPos.z);


        glm::mat4 modelMat = glm::mat4(1.0);
        float nowTime = glfwGetTime();
        float times = (nowTime - lastTime);
        act_time += times;

        for (int i = 0; i < MAX_PART; i++) {

            if (particles[i].isActive()) {

                glm::vec3 vec = particles[i].getPos();

                particles[i].live(times);
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


                glUniform4f(colorID, colors[0], colors[1], colors[2], particles[i].getLive());
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
        glfwSetInputMode(super->getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);

        glfwPollEvents();
        glfwSetCursorPos(super->getWindow(), 1024 / 2, 768 / 2);
        // glfwSetCursorPos(window, 1024 / 2, 768 / 2);
        glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
        glEnable(GL_DEPTH_TEST);
        // Accept fragment if it closer to the camera than the former one
        glDepthFunc(GL_LESS);

        glEnable(GL_BLEND);

        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        programID = LoadShaders("shaders/StandardShading.vertexshader", "shaders/MyShader.fragmentshader");

        MatrixID = glGetUniformLocation(programID, "MVP");
        ViewMatrixID = glGetUniformLocation(programID, "V");
        ModelMatrixID = glGetUniformLocation(programID, "M");
        for (int i = 0; i < MAX_PART; i++)
            particles[i].getObj()->intFromFile("resources/a_to_jez_jak_kulka.obj", programID, "resources/uvmap.png",
                                               "myTextureSampler");

        glUseProgram(programID);
        LightID = glGetUniformLocation(programID, "LightPosition_worldspace");
        colorID = glGetUniformLocation(programID, "ourColor");
        for (int i = 0; i < MAX_PART; i++) {
            particles[i].setEmiterPos(glm::vec3(0.0f, 0.0f, 0.0f));
            particles[i].setMode(POINT);
            particles[i].setDimension(glm::vec3(1,1,1));
            particles[i].getObj()->setProjectionMatrix(camera.getProjectionMatrix());
            particles[i].getObj()->setViewMatrix(camera.getViewMatrix());
        }

        lastTime = glfwGetTime();
    }

    void clean(Engine::Frame *super) {}
    float F_RAND(float end)
    {
        return static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX / end);
    }
};

Lab02::Lab02(/* args */) {
}

Lab02::~Lab02() {
}

#endif;
