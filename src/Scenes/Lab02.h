#ifndef LAB02_H
#define LAB02_H
#include "../Engine/Component.h"
#include "../Laby/Particles.h"
#include "../Laby/ParticleSystem.h"
#include "../Camera/Camera.h"
class Lab02 : public Engine::Component
{
private:
    Camera camera;
    int MAX_PART = 20;
    Particles particles[20];
    float ACTIVATE_TIME = 0.01f;
    float act_time = 0.0f;
    float lastTime;
    GLuint programID;
    GLuint MatrixID;

    GLuint ViewMatrixID;
    GLuint ModelMatrixID;
    GLuint LightID;
    GLuint colorID;
    RenderableObject obj;
    RenderableObject Particles[20];
    glm::vec4 color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
    /* data */
public:
    Lab02(/* args */);
    ~Lab02();

    void run(Engine::Frame *super)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(programID);

        // obj.setProjectionMatrix(camera.getProjectionMatrix());
        // obj.setViewMatrix(camera.getViewMatrix());

        glm::vec3 lightPos = glm::vec3(-4, 4, -4);
        glUniform3f(LightID, lightPos.x, lightPos.y, lightPos.z);

        // obj.drawColor(MatrixID, ViewMatrixID, ModelMatrixID);
        glm::mat4 modelMat = glm::mat4(1.0);
        float nowTime = glfwGetTime();
        float times = (nowTime - lastTime);
        act_time += times;

        for (int i = 0; i < MAX_PART; i++)
        {

            if (particles[i].isActive())
            {

                glm::vec3 vec = particles[i].getPos();

                particles[i].live(times);
            }
            else
            {
                if (act_time >= ACTIVATE_TIME)
                {
                    act_time = 0.0f;
                    particles[i].activate();
                    // puts("Aktywana");
                }
                break;
            }
        }
        for (int i = 0; i < MAX_PART; i++)
        {
            if (particles[i].isActive())
            {
                glm::vec3 colors = particles[i].getColor();
                // glm::vec3 pos = glm::vec3(float(i), 0.0f, 0.0f);
                // printf("live %f\n", particles[i].getLive());

                glUniform4f(colorID, colors[0], colors[1], colors[2], particles[i].getLive());
                particles[i].getObj()->setModelMatrix(glm::mat4(1.0));
                particles[i].getObj()->translate(particles[i].getPos());

                particles[i].getObj()->draw(MatrixID, ViewMatrixID, ModelMatrixID);
                // Particles[i].translate(glm::vec3(-float(i), 0.0f, 0.f));
            }
        }
        lastTime = nowTime;
        glBindVertexArray(0);
    }
    void setUp(Engine::Frame *super)
    {
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

        programID = LoadShaders("../../shaders/StandardShading.vertexshader", "../../shaders/MyShader.fragmentshader");

        MatrixID = glGetUniformLocation(programID, "MVP");
        ViewMatrixID = glGetUniformLocation(programID, "V");
        ModelMatrixID = glGetUniformLocation(programID, "M");
        for (int i = 0; i < MAX_PART; i++)
            particles[i].getObj()->intFromFile("../../resources/cube.obj", programID, "../../resources/uvmap.png", "myTextureSampler");

        glUseProgram(programID);
        LightID = glGetUniformLocation(programID, "LightPosition_worldspace");
        colorID = glGetUniformLocation(programID, "ourColor");
        for (int i = 0; i < MAX_PART; i++)
        {
            particles[i].setEmiterPos(glm::vec3(0.0f, 0.0f, 0.0f));
            particles[i].getObj()->setProjectionMatrix(camera.getProjectionMatrix());
            particles[i].getObj()->setViewMatrix(camera.getViewMatrix());
        }

        lastTime = glfwGetTime();
    }
    void clean(Engine::Frame *super) {}
};

Lab02::Lab02(/* args */)
{
}

Lab02::~Lab02()
{
}

#endif;
