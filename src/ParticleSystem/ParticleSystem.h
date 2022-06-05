#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H
#include "Particle.h"
enum Mode
{
    POINT = 0,
    LINE = 1,
    SQUARE = 2,
    CUBE = 3
};
class ParticleSystem
{
private:
    int mode;

public:
    int maxParticle;
    glm::vec3 emiterPos;
    glm::vec3 emiterShape;
    glm::vec3 gravity;
    ParticleSystem(/* args */);
    ~ParticleSystem();
};

ParticleSystem::ParticleSystem(/* args */)
{
}

ParticleSystem::~ParticleSystem()
{
}

#endif;