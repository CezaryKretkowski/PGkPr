#ifndef PARTICLES_SYSTEM_H
#define PARTICLES_SYSTEM_H

#include "Particles.h"
#define POINT_EMITER 00
#define LINE_EMITER 01
#define SQUARED_EMITER 10
#define BOX_EMITER 11
class ParticleSystem
{
private:
    int MAX_PART;
    int SHAPE;
    glm::vec3 emiterPosytion;
    std::vector<Particles> particles;
    float ACTIVATE_TIME = 0.01f;
    float act_time = 0.0f;
    float lastTime;

public:
    ParticleSystem(int MAX_PART = 10, glm::vec3 emiterPos = glm::vec3(0.0f, 0.0f, 0.0f));
    void initEmiterShapr(int shape, glm::vec3 emiterPos, glm::vec3 emiterShape);
    void initEmiterShapr(int shape, glm::vec3 emiterPos, glm::vec2 emiterShape);
    void initEmiterShapr(int shape, glm::vec3 emiterPos);
    void upDateLastTime()
    {
        lastTime = glfwGetTime();
    }
    ~ParticleSystem();
};

ParticleSystem::ParticleSystem(int MAX_PART, glm::vec3 emiterPos)
{
    this->MAX_PART = MAX_PART;
    Particles p;
    for (int i = 0; i < MAX_PART; i++)
        particles.push_back(p);
    this->SHAPE = POINT_EMITER;
    this->emiterPosytion = emiterPos;
}

ParticleSystem::~ParticleSystem()
{
}

#endif;