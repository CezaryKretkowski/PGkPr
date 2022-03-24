#ifndef LAB02_H
#define LAB02_H

#include "../Engine/Component.h"
#include "../Laby/Particles.h"
#include "../Laby/ParticleSystem.h"
#include "../Camera/Camera.h"
#include "../Laby/DirectionStrategy.h"

#define M_PI 3.14

class FountainEffect : public DirectionStrategy {

    glm::vec3 calculateDirection() override{
        float fi = M_PI / 4; // 45 stopni w górę
        float psi = F_RAND(0.0f, 1.0f) * (M_PI * 2); // 0-360 stopni wokół osi Y
        float rr = F_RAND(0.0f, 1.0f) * 12 + 16;
        glm::vec3 direction(rr * cos(fi) * cos(psi), rr * sin(fi), rr * cos(fi) * sin(psi));
        return direction;
    }
};

class Lab02 : public Engine::Component {
private:
    Camera camera;
    std::vector<glm::vec3> vertices, normals;
    std::vector<glm::vec2> uvs;

    int MAX_PART = 1010;
    Particles particles[1010];
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

        camera.control(super->getWindow(), super->getWidth(), super->getHeight());
        glm::vec3 lightPos = glm::vec3(-4, 4, -4);
        glUniform3f(LightID, lightPos.x, lightPos.y, lightPos.z);


        glm::mat4 modelMat = glm::mat4(1.0);
        float nowTime = glfwGetTime();
        float times = (nowTime - lastTime);
        act_time += times;

        for (int i = 0; i < MAX_PART; i++) {

            if (particles[i].isActive()) {
                particles[i].live(times);
            } else {
                if (act_time >= ACTIVATE_TIME) {
                    act_time = 0.0f;
                    particles[i].color=glm::vec3 (1.0f,F_RAND(0.0f,1.0f),F_RAND(0.0f,1.0f));
                    particles[i].activate();
                    // puts("Aktywana");
                }
                break;
            }
        }
        for (int i = 0; i < MAX_PART; i++) {
            if (particles[i].isActive()) {
                glm::vec3 colors = particles[i].color;


                glUniform4f(colorID, colors[0], colors[1], colors[2], particles[i].getLive());
                particles[i].setModelMatrix(glm::mat4(1.0));
                particles[i].setViewMatrix(camera.getViewMatrix());
                particles[i].setModelMatrix(glm::mat4(1.0));
                particles[i].translate(particles[i].getPos());
                particles[i].draw(MatrixID, ViewMatrixID, ModelMatrixID);

            }
        }
        lastTime = nowTime;
        glBindVertexArray(0);
    }

    void setUp(Engine::Frame *super) {
        // Hide the mouse and enable unlimited mouvement
        glfwSetInputMode(super->getWindow(), GLFW_STICKY_KEYS, GL_TRUE);
        glfwSetInputMode(super->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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
        loadOBJ("resources/kula.obj", vertices, uvs, normals);
        GLint out[2];
        LoadTexture(programID, "resources/uvmap.png", "myTextureSampler", out);

        for (int i = 0; i < MAX_PART; i++) {
            particles[i].initFromArrary(vertices, normals, uvs);
            particles[i].color = glm::vec3(1.0f, 1.0f, 0.0f);
            particles[i].setTexture(out[0], out[1]);
        }
        FountainEffect *strategy=new FountainEffect();
        glUseProgram(programID);
        LightID = glGetUniformLocation(programID, "LightPosition_worldspace");
        colorID = glGetUniformLocation(programID, "ourColor");
        for (int i = 0; i < MAX_PART; i++) {
            particles[i].setEmitterPosition(glm::vec3(0.0f, 0.0f, 0.0f));
            particles[i].setMode(LINE);
            particles[i].speed=25.0;
            particles[i].setDirectionStrategy(strategy);
            particles[i].setDimension(glm::vec3(1, 1, 1));
            particles[i].setProjectionMatrix(camera.getProjectionMatrix());
            particles[i].setViewMatrix(camera.getViewMatrix());
        }

        lastTime = glfwGetTime();
    }

    void clean(Engine::Frame *super) {}

};

Lab02::Lab02(/* args */) {
}

Lab02::~Lab02() {
}

#endif;
