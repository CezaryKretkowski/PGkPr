//
// Created by Lothar on 25.03.2022.
//

#ifndef PGKPR_FOG_H
#define PGKPR_FOG_H

#include "../../dependeces/Common/objloader.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "../Engine/Component.h"
#include "../Laby/Particles.h"
#include "../Laby/ParticleSystem.h"
#include "../Camera/Camera.h"
#include "Lab02.h"
#include "App.h"
#include <set>
struct Node{
    int id;
    float distance;
};
bool operator <(const  Node & v,const  Node & w){
    return v.distance<w.distance;

}
class FogEffect:public DirectionStrategy{
    glm::vec3 calculateDirection() override{
        float fi = M_PI / 4; // 45 stopni w górę
        float psi = F_RAND(0.0f, 1.0f) * (M_PI * 2); // 0-360 stopni wokół osi Y
        float rr = F_RAND(0.0f, 1.0f) * 12 + 16;
        glm::vec3 direction(rr * cos(fi) * cos(psi), rr * sin(fi), rr * cos(fi) * sin(psi));
        return direction;
    }
};
class Fog:public Engine::Component{
    Camera camera;
    std::vector<glm::vec3> vertices, normals;
    std::vector<glm::vec2> uvs;

    int MAX_PART = 100;
    Particles particles[100];

    float ACTIVATE_TIME = 0.0000001f;
    float act_time = 0.0f;
    float lastTime;
    float deag[100];
    float MaxPart_per=1000;
    GLuint programID;
    GLuint MatrixID;
    glm::vec2 dimensions;
    GLuint ViewMatrixID;
    GLuint ModelMatrixID;
    GLuint LightID;
    GLuint colorID;
    RenderableObject floor;
    glm::vec4 color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);

    std::set<Node> particlesMap;
    /* data */
public:
    Fog(/* args */){};

    ~Fog(){};
    void sortParticles(){
        particlesMap.clear();
        for (int i=0;i<MAX_PART;i++){
            Node n;
            n.id=i;
            n.distance= calculateDistance(camera.getPosytion(),particles[i].getPos());
            particlesMap.insert(n);
        }
    }
    void run(Engine::Frame *super) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(programID);

        camera.control(super->getWindow(), super->getWidth(), super->getHeight());
        glm::vec3 lightPos = glm::vec3(-4, 4, -4);
        glUniform3f(LightID, lightPos.x, lightPos.y, lightPos.z);

        int i=0;
        glm::mat4 modelMat = glm::mat4(1.0);
        float nowTime = glfwGetTime();
        float times = (nowTime - lastTime);
        act_time += times;

        while(i<MAX_PART) {//(int i = 0; i < MAX_PART; i++) {

            if (particles[i].isActive()) {
                //   particles[i].direction=vec3(F_RAND(-1.0,1.0), 1.0, F_RAND(-1.0,1.0));
                //  particles[i].direction+=particles[i].getExternals();
                particles[i].live(times);
                //   particles[i].direction=particles[i].getGravity();
            } else {
                if (act_time >= ACTIVATE_TIME) {
                    act_time=0.0f;
                    // particles[i].color=glm::vec3 (1.0f,F_RAND(0.0f,1.0f),F_RAND(0.0f,1.0f));
                    particles[i].activate();

                    // puts("Aktywana");
                }
                //break;
            }
            i++;
        }
        sortParticles();
        for (std::set<Node>::reverse_iterator i= particlesMap.rbegin(); i != particlesMap.rend(); i++) {
            if (particles[i->id].isActive()) {
                glm::vec3 colors = particles[i->id].color;


                //glUniform4f(colorID, 1.0-particles[i].getLive(), 1.0-particles[i].getLive(), 1.0-particles[i].getLive(), particles[i].getLive()/particles[i].speed);
                glUniform1f(colorID,particles[i->id].getLive());
                particles[i->id].setModelMatrix(glm::mat4(1.0));
                particles[i->id].setViewMatrix(camera.getViewMatrix());

                particles[i->id].translate(particles[i->id].getPos());
                //particles[i].rotate(glm::vec3(1,0,0),90.0f);
               // particles[i].rotate(glm::vec3(0,0,1),this->deag[i]);


                particles[i->id].draw(MatrixID, ViewMatrixID, ModelMatrixID);
//                printf("%f \n",i->distance);
            }
;

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

        programID = LoadShaders("shaders/StandardShading.vertexshader", "shaders/myShader2.fragmentshader");
        MatrixID = glGetUniformLocation(programID, "MVP");
        ViewMatrixID = glGetUniformLocation(programID, "V");
        ModelMatrixID = glGetUniformLocation(programID, "M");
        loadOBJ("resources/sphere.obj", vertices, uvs, normals);
        GLint out[2];
        LoadTexture(programID, "resources/ParticleCloudWhite.png", "myTextureSampler", out);

        for (int i = 0; i < MAX_PART; i++) {


            particles[i].initFromArrary(vertices, normals, uvs);
            particles[i].color = glm::vec3(0.3f, 0.3f, 0.3f);


            particles[i].setTexture(out[0], out[1]);
            particles[i].setGravity(glm::vec3(0.0f,0.0f,0.0f));
            deag[i]= F_RAND(0.0f,360.0f);


        }

        glUseProgram(programID);
        LightID = glGetUniformLocation(programID, "LightPosition_worldspace");
        colorID = glGetUniformLocation(programID, "alpha");
        for (int i = 0; i < MAX_PART; i++) {
            particles[i].setEmitterPosition(glm::vec3(0.0f, 0.0f, 0.0f));
            particles[i].setMode(CUBE);
            particles[i].speed=700.0;
            particles[i].setDirectionStrategy(new FogEffect());
            particles[i].setDimension(glm::vec3(2.0f, 2.0f, 2.0f));
            particles[i].setProjectionMatrix(camera.getProjectionMatrix());
            particles[i].setViewMatrix(camera.getViewMatrix());

        }

        lastTime = glfwGetTime();
    }

    void clean(Engine::Frame *super) {}

};
#endif //PGKPR_FOG_H
