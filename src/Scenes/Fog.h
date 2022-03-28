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
#include <algorithm>
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
       // return direction;
       return glm::vec3(0.0f,0.0f,0.0f);
    }
};
class Fog:public Engine::Component{
    Camera camera;
    std::vector<glm::vec3> vertices, normals;
    std::vector<glm::vec2> uvs;

    int MAX_PART = 1;
    Particles particles[1];
    float deagree[500];
    float ACTIVATE_TIME = 0.0000001f;
    float act_time = 0.0f;
    float lastTime;

    GLuint programID;
    GLuint MatrixID;
    glm::vec2 dimensions;
    GLuint ViewMatrixID;
    GLuint ModelMatrixID;
    GLuint LightID;
    GLuint colorID;
    RenderableObject cube;
    glm::vec4 color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);

    std::vector<Node> particlesMap;

    glm::mat4 RemoveRotation(glm::mat4 &M) {

        glm::mat4 MX(1.0);

        MX[3] = M[3];
        return MX;
    }

public:
    Fog(/* args */){};

    ~Fog(){};
    void sortParticles(){
        particlesMap.clear();
        for (int i=0;i<MAX_PART;i++){

            Node n;
            n.id=i;
            n.distance=calculateDistance(camera.getPosytion(),particles[i].getPos());


            particlesMap.push_back(n);

        }
        std::sort(particlesMap.begin(),particlesMap.end());

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

        glUniform4f(colorID,1.0f,0.0f,1.0f,1.0f);
        cube.setProjectionMatrix(camera.getProjectionMatrix());
        cube.setViewMatrix(camera.getViewMatrix());
        cube.draw(MatrixID, ViewMatrixID, ModelMatrixID);
        sortParticles();
        for (std::vector<Node>::reverse_iterator i= particlesMap.rbegin(); i != particlesMap.rend(); i++) {
            if (particles[i->id].isActive()) {
                glm::vec3 colors = particles[i->id].color;

               std::cout<<"Direction"<<camera.getDirection()[0]<<"|"<<camera.getDirection()[1]<<"|"<<camera.getDirection()[2]<<std::endl;
               std::cout<<"UP"<<camera.getUp()[0]<<"|"<<camera.getUp()[1]<<"|"<<camera.getUp()[2]<<std::endl;
                //glUniform4f(colorID, 1.0-particles[i].getLive(), 1.0-particles[i].getLive(), 1.0-particles[i].getLive(), particles[i].getLive()/particles[i].speed);
                if(particles[i->id].getLive()>0.7)
                    glUniform4f(colorID,0.7f,0.7f,0.7f,1-particles[i->id].getLive()-0.3);
                else if(particles[i->id].getLive()<0.7&&particles[i->id].getLive()>0.4)
                    glUniform4f(colorID,0.7f,0.7f,0.7f,0.5f);
                else
                    glUniform4f(colorID,0.7f,0.7f,0.7f,particles[i->id].getLive());
                particles[i->id].setProjectionMatrix(camera.getProjectionMatrix());
                particles[i->id].setModelMatrix(glm::mat4(1.0));
                particles[i->id].setViewMatrix(camera.getViewMatrix());
                glm::mat4 mat=glm::lookAt(particles[i->id].getPos(),particles[i->id].getPos()+camera.getPosytion(),glm::vec3(0,1,0));

                particles[i->id].translate(particles[i->id].getPos());
                particles[i->id].rotate(glm::vec3(1,0,0),90.0f);
               // particles[i->id].rotate(glm::vec3(0,0,1),deagree[i->id]);


                particles[i->id].draw(MatrixID, ViewMatrixID, ModelMatrixID);
//                printf("%f \n",i->distance);
            }
;

        }
       // particlesMap.clear();
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
        cube.intFromFile("resources/cube1.obj",programID,"resources/uvmap.png","myTextureSampler");
        loadOBJ("resources/circle3.obj", vertices, uvs, normals);
        GLint out[2];
        LoadTexture(programID, "resources/ParticleCloudWhite.png", "myTextureSampler", out);

        for (int i = 0; i < MAX_PART; i++) {


            particles[i].initFromArrary(floarVec ,floarNormal, floarUV);
            particles[i].color = glm::vec3(0.3f, 0.3f, 0.3f);


            particles[i].setTexture(out[0], out[1]);
            particles[i].setGravity(glm::vec3(0.0f,0.0f,0.0f));
           // deagree[i]= F_RAND(0.0f,360.0f);


        }

        glUseProgram(programID);
        LightID = glGetUniformLocation(programID, "LightPosition_worldspace");
        colorID = glGetUniformLocation(programID, "ourColor");
        for (int i = 0; i < MAX_PART; i++) {
            particles[i].setEmitterPosition(glm::vec3(-15.0f, -2.0f, -15.0f));
            particles[i].setMode(CUBE);
            particles[i].speed=50.0;
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
